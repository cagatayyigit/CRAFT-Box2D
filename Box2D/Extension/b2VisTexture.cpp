//
//  b2VisTexture.cpp
//  Box2D
//
//  Created by Tayfun Ateş on 6.10.2019.
//

#include "b2VisTexture.hpp"
#if defined(__APPLE_CC__)
#define GLFW_INCLUDE_GLCOREARB
#include <OpenGL/gl3.h>
#else
#include "Testbed/glad/glad.h"
#endif

b2VisTexture::b2VisTexture(const unsigned int& texId, const int& atlasWidth, const int& atlasHeight, const b2Vec2& upperLeftRatio, const b2Vec2& lowerRightRatio)
{
    m_bOwner = false;
    m_nTexId = texId;
    m_nAtlasHeight = atlasWidth;
    m_nAtlasHeight = atlasHeight;
    m_vUpperLeftCornerCoord = upperLeftRatio;
    m_vLowerRightCornerCoord = lowerRightRatio;
    
    const b2Vec2 upperLeftInPixels = b2Vec2(upperLeftRatio.x * atlasWidth, upperLeftRatio.y * atlasHeight);
    const b2Vec2 lowerRightInPixels = b2Vec2(lowerRightRatio.x * atlasWidth, lowerRightRatio.y * atlasHeight);
    
    m_nWidth = (lowerRightInPixels.x - upperLeftInPixels.x);
    m_nHeight = (lowerRightInPixels.y - upperLeftInPixels.y);
}

b2VisTexture::~b2VisTexture()
{
    if(m_bOwner && m_nTexId>0) {
        glDeleteTextures(1, &m_nTexId);
    }
}

unsigned int b2VisTexture::getTextureId() const
{
    return m_nTexId;
}

int b2VisTexture::getWidth() const
{
    return m_nWidth;
}

int b2VisTexture::getHeight() const
{
    return m_nHeight;
}

int b2VisTexture::getAtlasWidth() const
{
    return m_nAtlasWidth;
}

int b2VisTexture::getAtlasHeight() const
{
    return m_nAtlasHeight;
}

b2Vec2 b2VisTexture::getUpperLeftCornerCoord() const
{
    return m_vUpperLeftCornerCoord;
}

b2Vec2 b2VisTexture::getLowerRightCornerCoord() const
{
    return m_vLowerRightCornerCoord;
}
