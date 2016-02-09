
#include "ParticleSystemNodeQuad.h"

#include <algorithm>

#include "2d/CCSpriteFrame.h"
#include "2d/CCParticleBatchNode.h"
#include "renderer/CCTextureAtlas.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCRenderer.h"
#include "base/CCDirector.h"
#include "base/CCEventType.h"
#include "base/CCConfiguration.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCEventDispatcher.h"
#include "renderer/CCVertexIndexBuffer.h"
#include "deprecated/CCString.h"

#include "particles/Particle.h"

NS_CC_BEGIN

ParticleSystemNodeQuad::ParticleSystemNodeQuad()
{
}

ParticleSystemNodeQuad * ParticleSystemNodeQuad::createWithTotalParticles(int numberOfParticles) {

}





void ParticleSystemNodeQuad::setDisplayFrame(SpriteFrame *spriteFrame)
{
    CCASSERT(spriteFrame->getOffsetInPixels().isZero(), 
             "QuadParticle only supports SpriteFrames with no offsets");

    // update texture before updating texture rect
    if ( !_texture || spriteFrame->getTexture()->getName() != _texture->getName())
    {
        this->setTexture(spriteFrame->getTexture());
    }
}


ParticleSystemNodeQuad * ParticleSystemNodeQuad::create() {
	ParticleSystemNodeQuad *particleSystemQuad = new (std::nothrow) ParticleSystemNodeQuad();
    if (particleSystemQuad && particleSystemQuad->init())
    {
        particleSystemQuad->autorelease();
        return particleSystemQuad;
    }
    CC_SAFE_DELETE(particleSystemQuad);
    return nullptr;
}

std::string ParticleSystemNodeQuad::getDescription() const
{
    return StringUtils::format("<ParticleSystemQuad | Tag = %d, Total Particles = %d>", _tag, _totalParticles);
}

NS_CC_END
