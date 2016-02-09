
#include "ParticleSystemNode.h"

#include <string>

#include "2d/CCParticleBatchNode.h"
#include "renderer/CCTextureAtlas.h"
#include "base/base64.h"
#include "base/ZipUtils.h"
#include "base/CCDirector.h"
#include "renderer/CCTextureCache.h"
#include "deprecated/CCString.h"
#include "platform/CCFileUtils.h"
#include "particles/Particle.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCVertexIndexBuffer.h"
#include "renderer/CCRenderer.h"

#include "particles/LinearParameter.h"
#include "particles/SampledParameter.h"

using namespace std;

NS_CC_BEGIN

const int sampleCount = 100;

ParticleSystemNode::ParticleSystemNode()
: currentTime(0)
, emissionTimeSaldo(0)
, particleCount(0)
, particleLimit(0)

, _quads(nullptr)
, _indices(nullptr)
, _primitive(nullptr)

, _isBlendAdditive(false)
, _particles(nullptr)
, _allocatedParticles(0)
, _texture(nullptr)
, _blendFunc(BlendFunc::ALPHA_PREMULTIPLIED)
, _opacityModifyRGB(false)
{
	for (int i = 0; i < ParameterCount; i++)
	{
		parameters[i] = 0;
	}
}

ParticleSystemNode::~ParticleSystemNode()
{
	for (int i = 0; i < ParameterCount; i++)
	{
		CC_SAFE_DELETE(parameters[i]);
	}

	CC_SAFE_RELEASE(_primitive);

	CC_SAFE_FREE(_particles);
	CC_SAFE_RELEASE(_texture);
}

ParticleSystemNode* ParticleSystemNode::create(int numberOfParticles)
{
	ParticleSystemNode *ret = new (std::nothrow) ParticleSystemNode();
	if (ret && ret->initWithTotalParticles(numberOfParticles))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return ret;
}

void ParticleSystemNode::setParameterGraph(int index, std::vector<float>& times, std::vector<float>& values)
{
	setParameterGraph(index, new LinearParameter<float>(times, values));
}

void ParticleSystemNode::setParameterGraph(int index, std::vector<float>& times, std::vector<float>& v1, std::vector<float>& v2)
{
	std::vector<Vec2> values;
	values.resize(times.size());
	for (size_t i = 0; i < times.size(); i++)
	{
		values[i] = Vec2(v1[i], v2[i]);
	}
	setParameterGraph(index, new LinearParameter<Vec2>(times, values));
}

void ParticleSystemNode::setParameterGraph(int index, std::vector<float>& times, std::vector<float>& v1, std::vector<float>& v2, std::vector<float>& v3)
{
	std::vector<Vec3> values;
	values.resize(times.size());
	for (size_t i = 0; i < times.size(); i++)
	{
		values[i] = Vec3(v1[i], v2[i], v3[i]);
	}
	setParameterGraph(index, new LinearParameter<Vec3>(times, values));
}

void ParticleSystemNode::setParameterGraph(int index, std::vector<float>& times, std::vector<float>& v1, std::vector<float>& v2, std::vector<float>& v3, std::vector<float>& v4)
{
	std::vector<Vec4> values;
	values.resize(times.size());
	for (size_t i = 0; i < times.size(); i++)
	{
		values[i] = Vec4(v1[i], v2[i], v3[i], v4[i]);
	}
	setParameterGraph(index, new LinearParameter<Vec4>(times, values));
}

void ParticleSystemNode::setParameterGraph(int index, IParameter* parameter)
{
	CCASSERT(index >= 0 && index < ParameterCount, "invalid parameter index");
	CC_SAFE_DELETE(parameters[index]);

	switch ((ParameterType)index)
	{
	case ParameterType::OverLifeSize:
	case ParameterType::OverLifeSpeed:
	case ParameterType::OverLifeColor:
		auto tmp = parameter;
		parameter = parameter->Sampling(sampleCount);
		delete tmp;
	}

	parameters[index] = parameter;
}

void ParticleSystemNode::step(float dt)
{
	updateSystem(dt);
	updateParticles();
	updateGeometry();
}

void ParticleSystemNode::setUpdateTimeForParticles(float deltaTime)
{
	for (int i = 0; i < particleCount; i++)
	{
		_particles[i].updateTime = deltaTime;
	}
}

void ParticleSystemNode::updateSystem(float deltaTime)
{
	setUpdateTimeForParticles(deltaTime);

	auto prevSettings = getSettings(currentTime);
	currentTime += deltaTime;
	auto currentSettings = getSettings(currentTime);

	// average frequency during frame
	auto emissionFrequency = (prevSettings.emissionFrequency + currentSettings.emissionFrequency) / 2;
	if (emissionFrequency <= 0)
	{
		emissionTimeSaldo = 0;
		return;
	}

	emissionTimeSaldo += deltaTime;

	auto emissionInterval = 1.0f / emissionFrequency;
	while (emissionTimeSaldo > emissionInterval)
	{
		emissionTimeSaldo -= emissionInterval;
				
		if (particleCount < particleLimit)
		{
			float k = emissionTimeSaldo / deltaTime; // 0 - current moment, 1 - prev frame, > 1 - older
			auto emitterSettings = EmitterSettings::lerp(currentSettings.emitter, prevSettings.emitter, k);

			auto& particle = _particles[particleCount];
			particle = emitterSettings.emit();
			particle.updateTime = emissionTimeSaldo; // первый апдейт патикла должен учитывать время его появления на свет

			if (particle.updateTime >= particle.lifeTime)
				continue;
			
			particleCount++;
		}
	}
}

void ParticleSystemNode::updateParticles()
{
	// update time
	for (int i = 0; i < particleCount; i++)
	{
		auto& p = _particles[i];
		p.curTime += p.updateTime;
		if (p.curTime < p.lifeTime)
		{
			float k = p.curTime / p.lifeTime * sampleCount;
			p.sampleIndex = k;
			p.sampleLerpPart = k - p.sampleIndex;
		}
	}

	// remove dead particles
	defragmentation();

	if (particleCount == 0)
		return;

	updateParticleParameter(ParameterType::OverLifeSize, &Particle::size);
	updateParticleParameter(ParameterType::OverLifeSpeed, &Particle::speed);
	updateParticleParameter(ParameterType::OverLifeColor, &Particle::color);
	
	for (int i = 0; i < particleCount; i++)
	{
		auto& p = _particles[i];

		auto accSpeedVector = p.accSpeedVector;
		p.accSpeedVector += Vec3(0, -4, 0) * p.updateTime;
		accSpeedVector = (accSpeedVector + p.accSpeedVector) / 2; // estimated accSpeedVector over frame

		p.position += (p.direction * p.speed + accSpeedVector) * p.updateTime;

	}
}

template <typename T>
void ParticleSystemNode::updateParticleParameter(ParameterType type, T Particle::*member)
{
	auto parameter = static_cast<SampledParameter<T>*>(parameters[(int)type]);
	if (parameter)
	{
		for (int i = 0; i < particleCount; i++)
		{
			auto& p = _particles[i];
			p.*member = parameter->getValueBySample(p.sampleIndex, p.sampleLerpPart);
		}
	}
}

void ParticleSystemNode::defragmentation()
{
	int index = 0;
	int holeSize = 0;
	int wallSize = 0;

	auto flushWall = [&]() 
	{
		if (holeSize > 0)
		{
			void* dst = &_particles[index - wallSize - holeSize];
			void* src = &_particles[index - wallSize];
			memcpy(dst, src, wallSize * sizeof(Particle));
		}
		wallSize = 0;
	};

	for (index = 0; index < particleCount; index++)
	{
		if (_particles[index].isAlive())
		{
			wallSize++;
		}
		else
		{
			if (wallSize)
			{
				flushWall();
			}
			holeSize++;
		}
	}
	if (wallSize)
	{
		flushWall();
	}

	particleCount -= holeSize;
}

void ParticleSystemNode::updateGeometry()
{
	for (int i = 0; i < particleCount; i++)
	{
		auto& particle = _particles[i];
		auto& quad = _quads[i];

		Vertex::Shared shared;
		
		shared.color = particle.color;
		shared.position = particle.position;
		shared.texCoord2.x = particle.size;

		quad.bl.shared = shared;
		quad.br.shared = shared;
		quad.tl.shared = shared;
		quad.tr.shared = shared;
	}
}

template <typename T>
T ParticleSystemNode::getCurrentValue(ParameterType parameterType)
{
	auto parameter = static_cast<Parameter<T>*>(parameters[(int)parameterType]);
	if (parameter)
	{
		return parameter->getValue(currentTime);
	}
	else
	{
		return T();
	}
}

SystemSettings ParticleSystemNode::getSettings(float time)
{
	SystemSettings s;

	s.emissionFrequency = getCurrentValue<float>(ParameterType::EmissionFrequency);
	s.emitter.particleLifetime = getCurrentValue<float>(ParameterType::ParticleLifetime);
	
	return s;
}

void ParticleSystemNode::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	if (particleCount > 0)
	{
		_primitive->setStart(0);
		_primitive->setCount(particleCount * 6);

		auto vdata = _primitive->getVertexData();
		auto vb = vdata->getStreamBuffer(GLProgram::VERTEX_ATTRIB_POSITION);
		vb->updateVertices(_quads, particleCount * 4, 0);

		_command.init(_globalZOrder, _texture->getName(), getGLProgramState(), _blendFunc, _primitive, transform, flags);
		_command.set3D(true);
		renderer->addCommand(&_command);
	}
}

void ParticleSystemNode::reset()
{
	currentTime = 0;
	emissionTimeSaldo = 0;
	particleCount = 0;
}

//------------------------------------------------------------------

bool ParticleSystemNode::init()
{
    return initWithTotalParticles(150);
}

bool ParticleSystemNode::initWithTotalParticles(int numberOfParticles)
{
	particleLimit = numberOfParticles;

    CC_SAFE_FREE(_particles);
    
    _particles = (Particle*)calloc(particleLimit, sizeof(Particle));

    if( ! _particles )
    {
        CCLOG("Particle system: not enough memory");
        this->release();
        return false;
    }
    _allocatedParticles = numberOfParticles;

    _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
	
	if (!this->allocMemory()) {
		this->release();
		return false;
	}

	initIndices();

	return true;
}

bool ParticleSystemNode::isFull()
{
    return (particleCount == particleLimit);
}

void ParticleSystemNode::updateBlendFunc()
{
    if(_texture)
    {
        bool premultiplied = _texture->hasPremultipliedAlpha();
        
        _opacityModifyRGB = false;
        
        if( _texture && ( _blendFunc.src == CC_BLEND_SRC && _blendFunc.dst == CC_BLEND_DST ) )
        {
            if( premultiplied )
            {
                _opacityModifyRGB = true;
            }
            else
            {
                _blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;
            }
        }
    }
}

Texture2D * ParticleSystemNode::getTexture() const
{
    return _texture;
}

// ParticleSystem - Additive Blending
void ParticleSystemNode::setBlendAdditive(bool additive)
{
    if( additive )
    {
        _blendFunc = BlendFunc::ADDITIVE;
    }
    else
    {
        if( _texture && ! _texture->hasPremultipliedAlpha() )
            _blendFunc = BlendFunc::ALPHA_NON_PREMULTIPLIED;
        else 
            _blendFunc = BlendFunc::ALPHA_PREMULTIPLIED;
    }
}

bool ParticleSystemNode::isBlendAdditive() const
{
    return(_blendFunc.src == GL_SRC_ALPHA && _blendFunc.dst == GL_ONE);
}

const BlendFunc& ParticleSystemNode::getBlendFunc() const
{
    return _blendFunc;
}

void ParticleSystemNode::setBlendFunc(const BlendFunc &blendFunc)
{
    if( _blendFunc.src != blendFunc.src || _blendFunc.dst != blendFunc.dst ) {
        _blendFunc = blendFunc;
        this->updateBlendFunc();
    }
}

void ParticleSystemNode::setTotalParticles(int tp)
{
	// If we are setting the total number of particles to a number higher
	// than what is allocated, we need to allocate new arrays
	if (tp > _allocatedParticles)
	{
		// Allocate new memory
		size_t particlesSize = tp * sizeof(Particle);
		size_t quadsSize = sizeof(_quads[0]) * tp * 1;
		size_t indicesSize = sizeof(_indices[0]) * tp * 6 * 1;

		Particle* particlesNew = (Particle*)realloc(_particles, particlesSize);
		Quad* quadsNew = (Quad*)realloc(_quads, quadsSize);
		GLushort* indicesNew = (GLushort*)realloc(_indices, indicesSize);

		if (particlesNew && quadsNew && indicesNew)
		{
			// Assign pointers
			_particles = particlesNew;
			_quads = quadsNew;
			_indices = indicesNew;

			// Clear the memory
			memset(_particles, 0, particlesSize);
			memset(_quads, 0, quadsSize);
			memset(_indices, 0, indicesSize);

			_allocatedParticles = tp;
		}
		else
		{
			// Out of memory, failed to resize some array
			if (particlesNew) _particles = particlesNew;
			if (quadsNew) _quads = quadsNew;
			if (indicesNew) _indices = indicesNew;

			CCLOG("Particle system: out of memory");
			return;
		}

		particleLimit = tp;

		initIndices();


		updateTexCoords();
	}
	else
	{
		particleLimit = tp;
	}

}

void ParticleSystemNode::initIndices()
{
	for (int i = 0; i < particleLimit; ++i)
	{
		const unsigned int i6 = i * 6;
		const unsigned int i4 = i * 4;
		_indices[i6 + 0] = (GLushort)i4 + 0;
		_indices[i6 + 1] = (GLushort)i4 + 1;
		_indices[i6 + 2] = (GLushort)i4 + 2;

		_indices[i6 + 5] = (GLushort)i4 + 1;
		_indices[i6 + 4] = (GLushort)i4 + 2;
		_indices[i6 + 3] = (GLushort)i4 + 3;
	}

	auto ib = const_cast<IndexBuffer*>(_primitive->getIndexData());
	ib->updateIndices(_indices, ib->getIndexNumber(), 0);
}

void ParticleSystemNode::setTextureWithRect(Texture2D *texture, const Rect& rect)
{
	// Only update the texture if is different from the current one
	if (!_texture || texture->getName() != _texture->getName())
	{
		if (_texture != texture)
		{
			CC_SAFE_RETAIN(texture);
			CC_SAFE_RELEASE(_texture);
			_texture = texture;
			updateBlendFunc();
		}
	}

	this->initTexCoordsWithRect(rect);
}

void ParticleSystemNode::setTexture(Texture2D* texture)
{
	const Size& s = texture->getContentSize();
	this->setTextureWithRect(texture, Rect(0, 0, s.width, s.height));
}

void ParticleSystemNode::initTexCoordsWithRect(const Rect& pointRect)
{
	// convert to Tex coords

	Rect rect = Rect(
		pointRect.origin.x * CC_CONTENT_SCALE_FACTOR(),
		pointRect.origin.y * CC_CONTENT_SCALE_FACTOR(),
		pointRect.size.width * CC_CONTENT_SCALE_FACTOR(),
		pointRect.size.height * CC_CONTENT_SCALE_FACTOR());

	GLfloat wide = (GLfloat)pointRect.size.width;
	GLfloat high = (GLfloat)pointRect.size.height;

	if (_texture)
	{
		wide = (GLfloat)_texture->getPixelsWide();
		high = (GLfloat)_texture->getPixelsHigh();
	}

#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
	GLfloat left = (rect.origin.x * 2 + 1) / (wide * 2);
	GLfloat bottom = (rect.origin.y * 2 + 1) / (high * 2);
	GLfloat right = left + (rect.size.width * 2 - 2) / (wide * 2);
	GLfloat top = bottom + (rect.size.height * 2 - 2) / (high * 2);
#else
	GLfloat left = rect.origin.x / wide;
	GLfloat bottom = rect.origin.y / high;
	GLfloat right = left + rect.size.width / wide;
	GLfloat top = bottom + rect.size.height / high;
#endif // ! CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL

	// Important. Texture in cocos2d are inverted, so the Y component should be inverted
	std::swap(top, bottom);

	Quad *quads = nullptr;
	unsigned int start = 0, end = 0;

	quads = _quads;
	start = 0;
	end = particleLimit;

	for (unsigned int i = start; i<end; i++)
	{
		// bottom-left vertex:
		quads[i].bl.texCoord.u = left;
		quads[i].bl.texCoord.v = bottom;
		// bottom-right vertex:
		quads[i].br.texCoord.u = right;
		quads[i].br.texCoord.v = bottom;
		// top-left vertex:
		quads[i].tl.texCoord.u = left;
		quads[i].tl.texCoord.v = top;
		// top-right vertex:
		quads[i].tr.texCoord.u = right;
		quads[i].tr.texCoord.v = top;
	}
}

void ParticleSystemNode::updateTexCoords()
{
	if (_texture)
	{
		const Size& s = _texture->getContentSize();
		initTexCoordsWithRect(Rect(0, 0, s.width, s.height));
	}
}

bool ParticleSystemNode::allocMemory()
{
	CC_SAFE_FREE(_quads);
	CC_SAFE_FREE(_indices);

	_quads = (Quad*)malloc(particleLimit * sizeof(Quad));
	_indices = (GLushort*)malloc(particleLimit * 6 * sizeof(GLushort));

	if (!_quads || !_indices)
	{
		CCLOG("cocos2d: Particle system: not enough memory");
		CC_SAFE_FREE(_quads);
		CC_SAFE_FREE(_indices);

		return false;
	}

	memset(_quads, 0, particleLimit * sizeof(Quad));
	memset(_indices, 0, particleLimit * 6 * sizeof(GLushort));

	if (_primitive != nullptr)
	{
		_primitive->release();
		_primitive = nullptr;
	}

	auto verts = VertexData::create();

	auto vertexSize = sizeof(Vertex);
	auto vertexCount = particleLimit * 4;
	auto vb = VertexBuffer::create(vertexSize, vertexCount, GL_DYNAMIC_DRAW);

	verts->setStream(vb, VertexStreamAttribute(0, GLProgram::VERTEX_ATTRIB_TEX_COORD, GL_FLOAT, 2));
	verts->setStream(vb, VertexStreamAttribute(8, GLProgram::VERTEX_ATTRIB_POSITION, GL_FLOAT, 3));
	verts->setStream(vb, VertexStreamAttribute(20, GLProgram::VERTEX_ATTRIB_COLOR, GL_FLOAT, 4));
	verts->setStream(vb, VertexStreamAttribute(36, GLProgram::VERTEX_ATTRIB_TEX_COORD2, GL_FLOAT, 4));

	auto indices = IndexBuffer::create(IndexBuffer::IndexType::INDEX_TYPE_SHORT_16, particleLimit * 6);

	_primitive = Primitive::create(verts, indices, GL_TRIANGLES);
	_primitive->retain();

	return true;
}

NS_CC_END
