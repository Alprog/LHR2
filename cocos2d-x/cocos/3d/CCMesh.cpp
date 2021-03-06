/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "3d/CCMesh.h"
#include "3d/CCMeshSkin.h"
#include "3d/CCSkeleton3D.h"
#include "3d/CCMeshVertexIndexData.h"
#include "2d/CCLight.h"
#include "2d/CCScene.h"
#include "base/CCEventDispatcher.h"
#include "base/CCDirector.h"
#include "base/CCConfiguration.h"
#include "renderer/CCTextureCache.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCMaterial.h"
#include "renderer/CCTechnique.h"
#include "renderer/CCPass.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCVertexAttribBinding.h"
#include "math/Mat4.h"
#include "2d/CCCamera.h"

using namespace std;

NS_CC_BEGIN

// Helpers

static const char          *s_dirLightUniformColorName = "u_DirLightSourceColor";
static std::vector<Vec3> s_dirLightUniformColorValues;
static const char          *s_dirLightUniformDirName = "u_DirLightSourceDirection";
static std::vector<Vec3> s_dirLightUniformDirValues;

static const char          *s_pointLightUniformColorName = "u_PointLightSourceColor";
static std::vector<Vec3> s_pointLightUniformColorValues;
static const char          *s_pointLightUniformPositionName = "u_PointLightSourcePosition";
static std::vector<Vec3> s_pointLightUniformPositionValues;
static const char          *s_pointLightUniformRangeInverseName = "u_PointLightSourceRangeInverse";
static std::vector<float> s_pointLightUniformRangeInverseValues;

static const char          *s_spotLightUniformColorName = "u_SpotLightSourceColor";
static std::vector<Vec3> s_spotLightUniformColorValues;
static const char          *s_spotLightUniformPositionName = "u_SpotLightSourcePosition";
static std::vector<Vec3> s_spotLightUniformPositionValues;
static const char          *s_spotLightUniformDirName = "u_SpotLightSourceDirection";
static std::vector<Vec3> s_spotLightUniformDirValues;
static const char          *s_spotLightUniformInnerAngleCosName = "u_SpotLightSourceInnerAngleCos";
static std::vector<float> s_spotLightUniformInnerAngleCosValues;
static const char          *s_spotLightUniformOuterAngleCosName = "u_SpotLightSourceOuterAngleCos";
static std::vector<float> s_spotLightUniformOuterAngleCosValues;
static const char          *s_spotLightUniformRangeInverseName = "u_SpotLightSourceRangeInverse";
static std::vector<float> s_spotLightUniformRangeInverseValues;

static const char          *s_ambientLightUniformColorName = "u_AmbientLightSourceColor";

// helpers
static void resetLightUniformValues()
{
    const auto& conf = Configuration::getInstance();
    int maxDirLight = conf->getMaxSupportDirLightInShader();
    int maxPointLight = conf->getMaxSupportPointLightInShader();
    int maxSpotLight = conf->getMaxSupportSpotLightInShader();

    s_dirLightUniformColorValues.assign(maxDirLight, Vec3::ZERO);
    s_dirLightUniformDirValues.assign(maxDirLight, Vec3::ZERO);

    s_pointLightUniformColorValues.assign(maxPointLight, Vec3::ZERO);
    s_pointLightUniformPositionValues.assign(maxPointLight, Vec3::ZERO);
    s_pointLightUniformRangeInverseValues.assign(maxPointLight, 0.0f);

    s_spotLightUniformColorValues.assign(maxSpotLight, Vec3::ZERO);
    s_spotLightUniformPositionValues.assign(maxSpotLight, Vec3::ZERO);
    s_spotLightUniformDirValues.assign(maxSpotLight, Vec3::ZERO);
    s_spotLightUniformInnerAngleCosValues.assign(maxSpotLight, 0.0f);
    s_spotLightUniformOuterAngleCosValues.assign(maxSpotLight, 0.0f);
    s_spotLightUniformRangeInverseValues.assign(maxSpotLight, 0.0f);
}

//Generate a dummy texture when the texture file is missing
static Texture2D * getDummyTexture()
{
    auto texture = Director::getInstance()->getTextureCache()->getTextureForKey("/dummyTexture");
    if(!texture)
    {
#ifdef NDEBUG
        unsigned char data[] ={0,0,0,0};//1*1 transparent picture
#else
        unsigned char data[] ={255,0,0,255};//1*1 red picture
#endif
        Image * image =new (std::nothrow) Image();
        image->initWithRawData(data,sizeof(data),1,1,sizeof(unsigned char));
        texture=Director::getInstance()->getTextureCache()->addImage(image,"/dummyTexture");
        image->release();
    }
    return texture;
}


Mesh::Mesh()
: _texture(nullptr)
, _skin(nullptr)
, _visible(true)
, _isTransparent(false)
, _meshIndexData(nullptr)
, _material(nullptr)
, _glProgramState(nullptr)
, _blend(BlendFunc::ALPHA_NON_PREMULTIPLIED)
, _visibleChanged(nullptr)
, _blendDirty(true)
, _force2DQueue(false)

, _prevFrame()
, _prevMVP()
, _prevMatrixPalette(nullptr)
{
    
}

Mesh::~Mesh()
{
    CC_SAFE_RELEASE(_texture);
    CC_SAFE_RELEASE(_skin);
    CC_SAFE_RELEASE(_meshIndexData);
    CC_SAFE_RELEASE(_material);
    CC_SAFE_RELEASE(_glProgramState);
	CC_SAFE_DELETE_ARRAY(_prevMatrixPalette);
}

GLuint Mesh::getVertexBuffer() const
{
    return _meshIndexData->getVertexBuffer()->getVBO();
}

bool Mesh::hasVertexAttrib(int attrib) const
{
    return _meshIndexData->getMeshVertexData()->hasVertexAttrib(attrib);
}

ssize_t Mesh::getMeshVertexAttribCount() const
{
    return _meshIndexData->getMeshVertexData()->getMeshVertexAttribCount();
}

const MeshVertexAttrib& Mesh::getMeshVertexAttribute(int idx)
{
    return _meshIndexData->getMeshVertexData()->getMeshVertexAttrib(idx);
}

int Mesh::getVertexSizeInBytes() const
{
    return _meshIndexData->getVertexBuffer()->getSizePerVertex();
}

struct CombineMeshInfo
{
	Mat4 transformMatrix;
	Vec2 texTranslate;
	Vec2 texScale;
	Vec4 color;
};

struct CombineMeshVertex
{
	Vec3 position;
	Vec3 normal;
	Vec3 tangent;
	Vec2 texCoord;
	Vec4 color;
};

Mesh* Mesh::combine(Vector<Mesh*>& meshes, std::vector<float>& data)
{
	std::vector<const MeshData*> meshDatas;
	meshDatas.resize(meshes.size());
	for (size_t i = 0; i < meshes.size(); i++)
	{
		meshDatas[i] = meshes.at(i)->getMeshIndexData()->getMeshVertexData()->getInitialMeshData();
	}

	auto vertexCount = 0;
	auto indexCount = 0;
	for (auto d : meshDatas)
	{
		auto vertexSizeInFloat = d->getVertexSize() / sizeof(float);
		vertexCount += d->vertex.size() / vertexSizeInFloat;
		for (auto& si : d->subMeshIndices)
		{
			indexCount += si.size();
		}
	}

	std::vector<MeshVertexAttrib> attribs =
	{
		{ 3, GL_FLOAT, GLProgram::VERTEX_ATTRIB_POSITION, 3 * sizeof(float) },
		{ 3, GL_FLOAT, GLProgram::VERTEX_ATTRIB_NORMAL, 3 * sizeof(float) },
		{ 3, GL_FLOAT, GLProgram::VERTEX_ATTRIB_TANGENT, 3 * sizeof(float) },
		{ 2, GL_FLOAT, GLProgram::VERTEX_ATTRIB_TEX_COORD, 2 * sizeof(float) },
		{ 4, GL_FLOAT, GLProgram::VERTEX_ATTRIB_COLOR, 4 * sizeof(float) }
	};
	auto vertexSizeInFloat = 0;
	for (auto& attrib : attribs)
	{
		vertexSizeInFloat += attrib.size;
	}

	std::vector<float> vertices;
	IndexArray indices;
	vertices.resize(vertexCount * vertexSizeInFloat);
	indices.resize(indexCount);

	auto ii = 0, vi = 0;
	auto pVertex = (CombineMeshVertex*)(&vertices[0]);
	auto pMeshInfo = (CombineMeshInfo*)(&data[0]);
	
	for (auto d : meshDatas)
	{
		// indices:
		for (auto& si : d->subMeshIndices)
		{
			for (size_t i = 0; i < si.size(); i++)
			{
				indices[ii++] = si[i] + vi;
			}
		} 

		// vertices:
		auto vertexSizeInFloat = d->getVertexSize() / sizeof(float);
		auto pShift = d->getAttribOffset(GLProgram::VERTEX_ATTRIB_POSITION) / sizeof(float);
		auto nShift = d->getAttribOffset(GLProgram::VERTEX_ATTRIB_NORMAL) / sizeof(float);
		auto tnShift = d->getAttribOffset(GLProgram::VERTEX_ATTRIB_TANGENT) / sizeof(float);
		auto tShift = d->getAttribOffset(GLProgram::VERTEX_ATTRIB_TEX_COORD) / sizeof(float);
		auto vCount = d->vertex.size();
		for (size_t i = 0; i < vCount; i += vertexSizeInFloat)
		{
			pVertex->position = *(Vec3*)(&d->vertex[i + pShift]);
			pMeshInfo->transformMatrix.transformPoint(&pVertex->position);

			auto texCoord = *(Vec2*)(&d->vertex[i + tShift]);
			pVertex->texCoord.x = texCoord.x * pMeshInfo->texScale.x + pMeshInfo->texTranslate.x;
			pVertex->texCoord.y = texCoord.y * pMeshInfo->texScale.y + pMeshInfo->texTranslate.y;
			
			pVertex->normal = *(Vec3*)(&d->vertex[i + nShift]);
			if (tnShift >= 0)
			{
				pVertex->tangent = *(Vec3*)(&d->vertex[i + tnShift]);
			}

			pVertex->color = pMeshInfo->color;
			
			pVertex++;
			vi++;
		}

		pMeshInfo++; 
	}

	return _create(vertices, vertexSizeInFloat, indices, attribs);
}

inline MeshVertexAttrib Attribute(int size, int vertexAttribute)
{
	return MeshVertexAttrib { size, GL_FLOAT, vertexAttribute, (int)(size * sizeof(float)) };
}

Mesh* Mesh::create(const std::vector<Vec3>& positions, const std::vector<Vec3>& normals, const std::vector<Vec3>& tangents, const std::vector<Vec2>& texs, const std::vector<Vec2>& texs2, const IndexArray& indices)
{
	int perVertexSizeInFloat = 0;
	std::vector<float> vertices;
	std::vector<MeshVertexAttrib> attribs;

	bool hasNormal = (normals.size() != 0);
	bool hasTangents = (tangents.size() != 0);
	bool hasTexCoord0 = (texs.size() != 0);
	bool hasTexCoord1 = (texs2.size() != 0);

	if (positions.size())
	{
		perVertexSizeInFloat += 3;
		attribs.push_back(Attribute(3, GLProgram::VERTEX_ATTRIB_POSITION));
	}
	if (hasNormal)
	{
		perVertexSizeInFloat += 3;
		attribs.push_back(Attribute(3, GLProgram::VERTEX_ATTRIB_NORMAL));
	}
	if (hasTangents)
	{
		perVertexSizeInFloat += 3;
		attribs.push_back(Attribute(3, GLProgram::VERTEX_ATTRIB_TANGENT));
	}
	if (hasTexCoord0)
	{
		perVertexSizeInFloat += 2;
		attribs.push_back(Attribute(2, GLProgram::VERTEX_ATTRIB_TEX_COORD));
	}
	if (hasTexCoord1)
	{
		perVertexSizeInFloat += 2;
		attribs.push_back(Attribute(2, GLProgram::VERTEX_ATTRIB_TEX_COORD1));
	}

	size_t vertexNum = positions.size();
	vertices.reserve(vertexNum * perVertexSizeInFloat);

	for (size_t i = 0; i < vertexNum; i++)
	{
		float* p = (float*)&positions[i];
		vertices.insert(std::end(vertices), p, p + 3);

		if (hasNormal)
		{
			p = (float*)&normals[i];
			vertices.insert(std::end(vertices), p, p + 3);
		}

		if (hasTangents)
		{
			p = (float*)&tangents[i];
			vertices.insert(std::end(vertices), p, p + 3);
		}

		if (hasTexCoord0)
		{
			p = (float*)&texs[i];
			vertices.insert(std::end(vertices), p, p + 2);
		}

		if (hasTexCoord1)
		{
			p = (float*)&texs2[i];
			vertices.insert(std::end(vertices), p, p + 2);
		}
	}
	return _create(vertices, perVertexSizeInFloat, indices, attribs);
}

Mesh* Mesh::create(const std::vector<float>& positions, const std::vector<float>& normals, const std::vector<float>& texs, const IndexArray& indices)
{
    int perVertexSizeInFloat = 0;
    std::vector<float> vertices;
    std::vector<MeshVertexAttrib> attribs;
    MeshVertexAttrib att;
    att.size = 3;
    att.type = GL_FLOAT;
    att.attribSizeBytes = att.size * sizeof(float);
    
    if (positions.size())
    {
        perVertexSizeInFloat += 3;
        att.vertexAttrib = GLProgram::VERTEX_ATTRIB_POSITION;
        attribs.push_back(att);
    }
    if (normals.size())
    {
        perVertexSizeInFloat += 3;
        att.vertexAttrib = GLProgram::VERTEX_ATTRIB_NORMAL;
        attribs.push_back(att);
    }
    if (texs.size())
    {
        perVertexSizeInFloat += 2;
        att.vertexAttrib = GLProgram::VERTEX_ATTRIB_TEX_COORD;
        att.size = 2;
        att.attribSizeBytes = att.size * sizeof(float);
        attribs.push_back(att);
    }
    
    bool hasNormal = (normals.size() != 0);
    bool hasTexCoord = (texs.size() != 0);
    //position, normal, texCoordinate into _vertexs
    size_t vertexNum = positions.size() / 3;
    for(size_t i = 0; i < vertexNum; i++)
    {
        vertices.push_back(positions[i * 3]);
        vertices.push_back(positions[i * 3 + 1]);
        vertices.push_back(positions[i * 3 + 2]);

        if (hasNormal)
        {
            vertices.push_back(normals[i * 3]);
            vertices.push_back(normals[i * 3 + 1]);
            vertices.push_back(normals[i * 3 + 2]);
        }
    
        if (hasTexCoord)
        {
            vertices.push_back(texs[i * 2]);
            vertices.push_back(texs[i * 2 + 1]);
        }
    }
    return _create(vertices, perVertexSizeInFloat, indices, attribs);
}

Mesh* Mesh::_create(const std::vector<float>& vertices, int perVertexSizeInFloat, const IndexArray& indices, const std::vector<MeshVertexAttrib>& attribs)
{
    MeshData meshdata;
    meshdata.attribs = attribs;
    meshdata.vertex = vertices;
    meshdata.subMeshIndices.push_back(indices);
    meshdata.subMeshIds.push_back("");
    auto meshvertexdata = MeshVertexData::create(meshdata);
    auto indexData = meshvertexdata->getMeshIndexDataByIndex(0);
    
    return create("", indexData);
}

Mesh* Mesh::create(const std::string& name, MeshIndexData* indexData, MeshSkin* skin)
{
    auto state = new (std::nothrow) Mesh();
    state->autorelease();
    state->bindMeshCommand();
    state->_name = name;
    state->setMeshIndexData(indexData);
    state->setSkin(skin);
    
    return state;
}

void Mesh::setVisible(bool visible)
{
    if (_visible != visible)
    {
        _visible = visible;
        if (_visibleChanged)
            _visibleChanged();
    }
}

bool Mesh::isVisible() const
{
    return _visible;
}

void Mesh::setTexture(const std::string& texPath)
{
    auto tex = Director::getInstance()->getTextureCache()->addImage(texPath);
    setTexture(tex);
}

void Mesh::setTexture(Texture2D* tex)
{
    // Texture must be saved for future use
    // it doesn't matter if the material is already set or not
    // This functionality is added for compatibility issues
    if (tex == nullptr)
        tex = getDummyTexture();
    
    if (tex != _texture)
    {
        CC_SAFE_RETAIN(tex);
        CC_SAFE_RELEASE(_texture);
        _texture = tex;
    }

    if (_material) {
        auto technique = _material->_currentTechnique;
        for(auto& pass: technique->_passes)
        {
            // FIXME: Ideally it should use glProgramState->setUniformTexture()
            // and set CC_Texture0 that way. But trying to it, will trigger
            // another bug
            pass->setTexture(tex);
        }
    }

    bindMeshCommand();
}

Texture2D* Mesh::getTexture() const
{
    return _texture;
}

void Mesh::setMaterial(Material* material)
{
    if (_material != material) {
        CC_SAFE_RELEASE(_material);
        _material = material;
        CC_SAFE_RETAIN(_material);
    }

    if (_material)
    {
        for (auto pair : _material->getTechniques())
        {
			auto technique = pair.second;
            for (auto pass : technique->getPasses())
            {
                auto vertexAttribBinding = VertexAttribBinding::create(_meshIndexData, pass->getGLProgramState());
                pass->setVertexAttribBinding(vertexAttribBinding);
            }
        }
    }
}

Material* Mesh::getMaterial() const
{
    return _material;
}

void Mesh::draw(Renderer* renderer, float globalZOrder, const Mat4& transform, uint32_t flags, unsigned int lightMask, const Vec4& color, bool forceDepthWrite)
{
	if (!isVisible())
	{
		return;
	}

	_material->selectTechnique(renderer->getRenderMode());
	if (_material->_currentTechnique == nullptr)
	{
		return;
	}

	bool isTransparent = (_isTransparent || color.w < 1.f);
	float globalZ = isTransparent ? 0 : globalZOrder;
	if (isTransparent)
		flags |= Node::FLAGS_RENDER_AS_3D;

	_material->getStateBlock()->setDepthWrite(true);

	_meshCommand.init(globalZ,
		_material,
		getVertexBuffer(),
		getIndexBuffer(),
		getPrimitiveType(),
		getIndexFormat(),
		getIndexCount(),
		transform,
		flags);



	_meshCommand.setSkipBatching(isTransparent);
	_meshCommand.setTransparent(isTransparent);
	_meshCommand.set3D(!_force2DQueue);
	_material->getStateBlock()->setBlend(_force2DQueue || isTransparent);

	// set default uniforms for Mesh
	// 'u_color' and others

	auto director = Director::getInstance();

	auto frame = director->getTotalFrames();
	auto MVP = director->getVPMat().viewProjection * transform;
	auto deltaTime = director->getDeltaTime();

	auto isSame = (frame - _prevFrame) == 0;
	auto isPrevValid = (frame - _prevFrame) == 1;
	
	auto technique = _material->_currentTechnique;
	for (const auto pass : technique->_passes)
	{
		auto programState = pass->getGLProgramState();
		programState->setUniformMat4("prevMVP", isPrevValid ? _prevMVP : MVP);
	}

	if (_skin)
	{
		auto matrixPalette = _skin->getMatrixPalette();
		auto paletteSize = (GLsizei)_skin->getMatrixPaletteSize();

		auto s0 = (frame % 2) * paletteSize;
		auto s1 = (1 - frame % 2) * paletteSize;

		auto technique = _material->_currentTechnique;
		for (const auto pass : technique->_passes)
		{
			auto programState = pass->getGLProgramState();

			programState->setUniformVec4v("u_matrixPalette", paletteSize, matrixPalette);
			programState->setUniformVec4v("u_prevMatrixPalette", paletteSize, isPrevValid ? _prevMatrixPalette + s0 : matrixPalette);
		}

		if (!isSame)
		{
			if (_prevMatrixPalette == nullptr)
			{
				_prevMatrixPalette = new (std::nothrow) Vec4[paletteSize * 2];
			}
			memcpy(_prevMatrixPalette + s1, matrixPalette, paletteSize * sizeof(Vec4));
		}
	}

	if (!isSame)
	{
		_prevMVP = MVP;
	}
	_prevFrame = frame;
	
    renderer->addCommand(&_meshCommand);
}

void Mesh::setSkin(MeshSkin* skin)
{
    if (_skin != skin)
    {
        CC_SAFE_RETAIN(skin);
        CC_SAFE_RELEASE(_skin);
        _skin = skin;
        calculateAABB();
    }
}

void Mesh::setMeshIndexData(MeshIndexData* subMesh)
{
    if (_meshIndexData != subMesh)
    {
        CC_SAFE_RETAIN(subMesh);
        CC_SAFE_RELEASE(_meshIndexData);
        _meshIndexData = subMesh;
        calculateAABB();
        bindMeshCommand();
    }
}

void Mesh::setGLProgramState(GLProgramState* glProgramState)
{
    // XXX create dummy texture
    auto material = Material::createWithGLStateProgram(glProgramState);
    setMaterial(material);

    // Was the texture set before teh GLProgramState ? Set it
    if (_texture)
        setTexture(_texture);

    if (_blendDirty)
        setBlendFunc(_blend);

    bindMeshCommand();
}

GLProgramState* Mesh::getGLProgramState() const
{
    return _material ?
                _material->_currentTechnique->_passes.at(0)->getGLProgramState()
                : nullptr;
}

void Mesh::calculateAABB()
{
    if (_meshIndexData)
    {
        _aabb = _meshIndexData->getAABB();
        if (_skin)
        {
            //get skin root
            Bone3D* root = nullptr;
            Mat4 invBindPose;
            if (_skin->_skinBones.size())
            {
                root = _skin->_skinBones.at(0);
                while (root) {
                    auto parent = root->getParentBone();
                    bool parentInSkinBone = false;
                    for (const auto& bone : _skin->_skinBones) {
                        if (bone == parent)
                        {
                            parentInSkinBone = true;
                            break;
                        }
                    }
                    if (!parentInSkinBone)
                        break;
                    root = parent;
                }
            }
            
            if (root)
            {
                _aabb.transform(root->getWorldMat() * _skin->getInvBindPose(root));
            }
        }
    }
}

void Mesh::bindMeshCommand()
{
    if (_material && _meshIndexData)
    {
        auto pass = _material->_currentTechnique->_passes.at(0);
        auto glprogramstate = pass->getGLProgramState();
        auto texture = pass->getTexture();
        auto textureid = texture ? texture->getName() : 0;
        // XXX
//        auto blend = pass->getStateBlock()->getBlendFunc();
        auto blend = BlendFunc::ALPHA_PREMULTIPLIED;

        _meshCommand.genMaterialID(textureid, glprogramstate, _meshIndexData->getVertexBuffer()->getVBO(), _meshIndexData->getIndexBuffer()->getVBO(), blend);
        _material->getStateBlock()->setCullFace(true);
        _material->getStateBlock()->setDepthTest(true);
    }
}

void Mesh::setLightUniforms(Pass* pass, const Node* lightNode, const Vec4& color, unsigned int lightmask)
{
    CCASSERT(pass, "Invalid Pass");
    CCASSERT(lightNode, "Invalid scene");

    const auto& conf = Configuration::getInstance();
    int maxDirLight = conf->getMaxSupportDirLightInShader();
    int maxPointLight = conf->getMaxSupportPointLightInShader();
    int maxSpotLight = conf->getMaxSupportSpotLightInShader();
	
    auto glProgramState = pass->getGLProgramState();
    auto attributes = pass->getVertexAttributeBinding()->getVertexAttribsFlags();

    if (attributes & (1 << GLProgram::VERTEX_ATTRIB_NORMAL))
    {
        resetLightUniformValues();

        GLint enabledDirLightNum = 0;
        GLint enabledPointLightNum = 0;
        GLint enabledSpotLightNum = 0;
        Vec3 ambientColor;
        for (const auto& node : lightNode->getChildren())
        {
			auto light = static_cast<BaseLight*>(node);

	        bool useLight = light->isEnabled() && ((unsigned int)light->getLightFlag() & lightmask);
            if (useLight)
            {
                float intensity = light->getIntensity();
                switch (light->getLightType())
                {
                    case LightType::DIRECTIONAL:
                    {
                        if(enabledDirLightNum < maxDirLight)
                        {
                            auto dirLight = static_cast<DirectionLight *>(light);
                            Vec3 dir = dirLight->getDirectionInWorld();
                            dir.normalize();
                            const Color3B &col = dirLight->getDisplayedColor();
                            s_dirLightUniformColorValues[enabledDirLightNum].set(col.r / 255.0f * intensity, col.g / 255.0f * intensity, col.b / 255.0f * intensity);
                            s_dirLightUniformDirValues[enabledDirLightNum] = dir;
                            ++enabledDirLightNum;
                        }

                    }
                        break;
                    case LightType::POINT:
                    {
                        if(enabledPointLightNum < maxPointLight)
                        {
                            auto pointLight = static_cast<PointLight *>(light);
                            Mat4 mat= pointLight->getNodeToWorldTransform();
                            const Color3B &col = pointLight->getDisplayedColor();
                            s_pointLightUniformColorValues[enabledPointLightNum].set(col.r / 255.0f * intensity, col.g / 255.0f * intensity, col.b / 255.0f * intensity);
                            s_pointLightUniformPositionValues[enabledPointLightNum].set(mat.m[12], mat.m[13], mat.m[14]);
                            s_pointLightUniformRangeInverseValues[enabledPointLightNum] = 1.0f / pointLight->getRange();
                            ++enabledPointLightNum;
                        }
                    }
                        break;
                    case LightType::SPOT:
                    {
                        if(enabledSpotLightNum < maxSpotLight)
                        {
                            auto spotLight = static_cast<SpotLight *>(light);
                            Vec3 dir = spotLight->getDirectionInWorld();
                            dir.normalize();
                            Mat4 mat= light->getNodeToWorldTransform();
                            const Color3B &col = spotLight->getDisplayedColor();
                            s_spotLightUniformColorValues[enabledSpotLightNum].set(col.r / 255.0f * intensity, col.g / 255.0f * intensity, col.b / 255.0f * intensity);
                            s_spotLightUniformPositionValues[enabledSpotLightNum].set(mat.m[12], mat.m[13], mat.m[14]);
                            s_spotLightUniformDirValues[enabledSpotLightNum] = dir;
                            s_spotLightUniformInnerAngleCosValues[enabledSpotLightNum] = spotLight->getCosInnerAngle();
                            s_spotLightUniformOuterAngleCosValues[enabledSpotLightNum] = spotLight->getCosOuterAngle();
                            s_spotLightUniformRangeInverseValues[enabledSpotLightNum] = 1.0f / spotLight->getRange();
                            ++enabledSpotLightNum;
                        }
                    }
                        break;
                    case LightType::AMBIENT:
                    {
                        auto ambLight = static_cast<AmbientLight *>(light);
                        const Color3B &col = ambLight->getDisplayedColor();
                        ambientColor.add(col.r / 255.0f * intensity, col.g / 255.0f * intensity, col.b / 255.0f * intensity);
                    }
                        break;
                    default:
                        break;
                }
            }
        }

        if (0 < maxDirLight)
        {
            glProgramState->setUniformVec3v(s_dirLightUniformColorName, s_dirLightUniformColorValues.size(), &s_dirLightUniformColorValues[0]);
            glProgramState->setUniformVec3v(s_dirLightUniformDirName, s_dirLightUniformDirValues.size(), &s_dirLightUniformDirValues[0]);
        }

        if (0 < maxPointLight)
        {
            glProgramState->setUniformVec3v(s_pointLightUniformColorName, s_pointLightUniformColorValues.size(), &s_pointLightUniformColorValues[0]);
            glProgramState->setUniformVec3v(s_pointLightUniformPositionName, s_pointLightUniformPositionValues.size(), &s_pointLightUniformPositionValues[0]);
            glProgramState->setUniformFloatv(s_pointLightUniformRangeInverseName, s_pointLightUniformRangeInverseValues.size(), &s_pointLightUniformRangeInverseValues[0]);
        }

        if (0 < maxSpotLight)
        {
            glProgramState->setUniformVec3v(s_spotLightUniformColorName, s_spotLightUniformColorValues.size(), &s_spotLightUniformColorValues[0]);
            glProgramState->setUniformVec3v(s_spotLightUniformPositionName, s_spotLightUniformPositionValues.size(), &s_spotLightUniformPositionValues[0]);
            glProgramState->setUniformVec3v(s_spotLightUniformDirName, s_spotLightUniformDirValues.size(), &s_spotLightUniformDirValues[0]);
            glProgramState->setUniformFloatv(s_spotLightUniformInnerAngleCosName, s_spotLightUniformInnerAngleCosValues.size(), &s_spotLightUniformInnerAngleCosValues[0]);
            glProgramState->setUniformFloatv(s_spotLightUniformOuterAngleCosName, s_spotLightUniformOuterAngleCosValues.size(), &s_spotLightUniformOuterAngleCosValues[0]);
            glProgramState->setUniformFloatv(s_spotLightUniformRangeInverseName, s_spotLightUniformRangeInverseValues.size(), &s_spotLightUniformRangeInverseValues[0]);
        }

        glProgramState->setUniformVec3(s_ambientLightUniformColorName, Vec3(ambientColor.x, ambientColor.y, ambientColor.z));
    }
    else // normal does not exist
    {
        Vec3 ambient(0.0f, 0.0f, 0.0f);
        bool hasAmbient = false;
		for (const auto& node : lightNode->getChildren())
		{
			auto light = static_cast<BaseLight*>(node);
            if (light->getLightType() == LightType::AMBIENT)
            {
                bool useLight = light->isEnabled() && ((unsigned int)light->getLightFlag() & lightmask);
                if (useLight)
                {
                    hasAmbient = true;
                    const Color3B &col = light->getDisplayedColor();
                    ambient.x += col.r * light->getIntensity();
                    ambient.y += col.g * light->getIntensity();
                    ambient.z += col.b * light->getIntensity();
                }
            }
        }
        if (hasAmbient)
        {
            ambient.x /= 255.f; ambient.y /= 255.f; ambient.z /= 255.f;
            //override the uniform value of u_color using the calculated color 
            glProgramState->setUniformVec4("u_color", Vec4(color.x * ambient.x, color.y * ambient.y, color.z * ambient.z, color.w));
        }
    }
}

void Mesh::setBlendFunc(const BlendFunc &blendFunc)
{
    // Blend must be saved for future use
    // it doesn't matter if the material is already set or not
    // This functionality is added for compatibility issues
    if(_blend != blendFunc)
    {
        _blendDirty = true;
        _blend = blendFunc;
    }

    if (_material) {
        _material->getStateBlock()->setBlendFunc(blendFunc);
        bindMeshCommand();
    }
}

const BlendFunc& Mesh::getBlendFunc() const
{
// return _material->_currentTechnique->_passes.at(0)->getBlendFunc();
    return _blend;
}

GLenum Mesh::getPrimitiveType() const
{
    return _meshIndexData->getPrimitiveType();
}

ssize_t Mesh::getIndexCount() const
{
    return _meshIndexData->getIndexBuffer()->getIndexNumber();
}

GLenum Mesh::getIndexFormat() const
{
    return GL_UNSIGNED_SHORT;
}

GLuint Mesh::getIndexBuffer() const
{
    return _meshIndexData->getIndexBuffer()->getVBO();
}
NS_CC_END
