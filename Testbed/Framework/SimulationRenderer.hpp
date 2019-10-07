//
//  SimulationRenderer.hpp
//  Testbed
//
//  Created by Tayfun Ateş on 5.10.2019.
//

#ifndef SimulationRenderer_hpp
#define SimulationRenderer_hpp

#include "SimulationDefines.h"
#include "Box2D/Box2D.h"

struct b2AABB;
struct GLRenderPoints;
struct GLRenderLines;
struct GLRenderTriangles;


// This class implements debug drawing callbacks that are invoked
// inside b2World::Step.
class SimulationRenderer : public b2Draw
{
public:
    SimulationRenderer();
    virtual ~SimulationRenderer();

    void Create();
    void Destroy();

    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;

    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
    
    void DrawTexturedSolidPolygon(const b2Vec2* vertices, const b2Vec2* textureCoordinates, uint32 texId, int32 vertexCount, const b2Color& color) override;

    void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;

    void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;

    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;

    void DrawTransform(const b2Transform& xf) override;

    void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override;

    void DrawString(int x, int y, const char* string, ...);

    void DrawString(const b2Vec2& p, const char* string, ...);

    void DrawAABB(b2AABB* aabb, const b2Color& color);

    void Flush();
    
    //Setters and getters
    void setIsDebugMode(const bool& isDebug);
    bool getIsDebugMode() const;
    
private:
    GLRenderPoints* m_points;
    GLRenderLines* m_lines;
    GLRenderTriangles* m_triangles;
    
    bool m_bIsDebugMode;
};

#if USE_DEBUG_DRAW
#else
extern SimulationRenderer g_debugDraw;
#endif

#endif /* SimulationRenderer_hpp */
