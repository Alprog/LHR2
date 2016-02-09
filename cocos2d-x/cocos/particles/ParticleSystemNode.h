
#pragma once

#include "base/CCProtocols.h"
#include "2d/CCNode.h"
#include "base/CCValue.h"
#include "renderer/CCPrimitiveCommand.h"

#include "particles/Parameter.h"
#include "particles/ParameterType.h"
#include "particles/SystemSettings.h"

struct Particle;

NS_CC_BEGIN

class ParticleBatchNode;
class Texture2D;

class CC_DLL ParticleSystemNode : public Node, public TextureProtocol
{
	struct Vertex // 52 bytes
	{
		Tex2F texCoord;  // 8 bytes

		struct Shared
		{
			Vec3 position;   // 12 bytes
			Vec4 color;      // 16 bytes
			Vec4 texCoord2;  // 16 bytes
		}
		shared;
	};

	struct Quad // 204 bytes
	{
		Vertex tl;
		Vertex bl;
		Vertex tr;
		Vertex br;
	};

protected:
	ParticleSystemNode();
	virtual ~ParticleSystemNode();

public:
	static ParticleSystemNode* create(int numberOfParticles);

	void setParameterGraph(int index, std::vector<float>& times, std::vector<float>& values);
	void setParameterGraph(int index, std::vector<float>& times, std::vector<float>& v1, std::vector<float>& v2);
	void setParameterGraph(int index, std::vector<float>& times, std::vector<float>& v1, std::vector<float>& v2, std::vector<float>& v3);
	void setParameterGraph(int index, std::vector<float>& times, std::vector<float>& v1, std::vector<float>& v2, std::vector<float>& v3, std::vector<float>& v4);
	void setParameterGraph(int index, IParameter* parameter);

	void step(float dt);
	void updateSystem(float dt);
	void setUpdateTimeForParticles(float dt);
	void updateParticles();
	void updateGeometry();

	template <typename T>
	void updateParticleParameter(ParameterType type, T Particle::*member);

	template <typename T>
	T getCurrentValue(ParameterType parameterType);

	void defragmentation();
	SystemSettings getSettings(float time);

	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

	int getParticleCount() { return particleCount; }

	void reset();

protected:
	float currentTime;        // Внутреннее время самой системы
	float emissionTimeSaldo;  // Накопленое время на испукание патиклов

	int particleCount; // Текущее кол-во патиклов
	int particleLimit; // Максимально допустимое кол-во патиклов


	IParameter* parameters[ParameterCount];
	
	//-----------------------------------------------------------


public:
	void setTotalParticles(int tp);
	bool allocMemory();
	void initIndices();
	void initTexCoordsWithRect(const Rect& rect);
	void updateTexCoords();

	bool isFull();

    virtual bool isBlendAdditive() const;
    virtual void setBlendAdditive(bool value);

    inline void setOpacityModifyRGB(bool opacityModifyRGB) override { _opacityModifyRGB = opacityModifyRGB; };
    inline bool isOpacityModifyRGB() const override { return _opacityModifyRGB; };
    CC_DEPRECATED_ATTRIBUTE inline bool getOpacityModifyRGB() const { return isOpacityModifyRGB(); }
    
    virtual Texture2D* getTexture() const override;

	void setTextureWithRect(Texture2D *texture, const Rect& rect);
	virtual void setTexture(Texture2D* texture) override;

	virtual void setBlendFunc(const BlendFunc &blendFunc) override;
    virtual const BlendFunc &getBlendFunc() const override;
    
CC_CONSTRUCTOR_ACCESS:


    bool init() override;
    
    virtual bool initWithTotalParticles(int numberOfParticles);

protected:
    virtual void updateBlendFunc();

	Quad *_quads;
	GLushort            *_indices;
	Primitive* _primitive;
	PrimitiveCommand _command;


    bool _isBlendAdditive;
	
    Particle* _particles;
	
    int _allocatedParticles;

    Texture2D* _texture;
    BlendFunc _blendFunc;
    bool _opacityModifyRGB;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(ParticleSystemNode);
};

NS_CC_END
