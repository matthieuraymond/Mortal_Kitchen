#include "physics.h"
#include "entity.h"

#include <LibSL_gl.h>

//
// see http://www.iforce2d.net/b2dtut/ for a nice tutorial
//

// ------------------------------------------------------------------------

// The World
b2World *g_World = NULL;

// ------------------------------------------------------------------------

class ContactListener : public b2ContactListener
{
public:
  void BeginContact(b2Contact* contact)  { }
  void EndContact(b2Contact* contact)    { }
  void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
  {
    // get fixtures
    b2Fixture    *fA = contact->GetFixtureA();
    b2Fixture    *fB = contact->GetFixtureB();
    // get user data
    void *dA = fA->GetUserData();
    void *dB = fB->GetUserData();
    if (dA != NULL && dB != NULL) {
      entity_contact((Entity*)dA, (Entity*)dB);
      entity_contact((Entity*)dB, (Entity*)dA);
    }
    else if (dA != NULL) {
      entity_onfloor((Entity*)dA);
    }
    else {
      entity_onfloor((Entity*)dB);
    }
    // To disable contact: contact->SetEnabled(false);
  }
  void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) { }
};

ContactListener g_ContactListener;

// ------------------------------------------------------------------------

class DebugDraw : public b2DebugDraw
{
public:
  void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
  {
    glColor3f(color.r, color.b, color.b);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < vertexCount; i++) {
      glVertex2f(vertices[i].x, vertices[i].y);
    }
    glVertex2f(vertices[0].x, vertices[0].y);
    glEnd();
  }
  void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
  {
    glColor3f(color.r, color.b, color.b);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < vertexCount; i++) {
      glVertex2f(vertices[i].x, vertices[i].y);
    }
    glVertex2f(vertices[0].x, vertices[0].y);
    glEnd();
  }
  void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
  {
    glColor3f(color.r, color.b, color.b);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < 32; i++) {
      float a = i * 6.28 / 31.0f;
      glVertex2f(radius*cos(a) + center.x, radius*sin(a) + center.y);
    }
    glEnd();
  }
  void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
  {
    glColor3f(color.r, color.b, color.b);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < 32; i++) {
      float a = i * 6.28 / 31.0f;
      glVertex2f(radius*cos(a) + center.x, radius*sin(a) + center.y);
    }
    glEnd();
  }
  void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {}
  void DrawTransform(const b2Transform& xf) {}
};

DebugDraw g_DebugDraw;

// ------------------------------------------------------------------------

void phy_init()
{
  // gravity
  b2Vec2 gravity(0.0f, -3.0f);

  // let non-moving bodies sleep
  bool doSleep = true;

  // build the world!
  g_World = new b2World(gravity, doSleep);

  // define contact listener, keeping track of collisions/contacts
  g_World->SetContactListener(&g_ContactListener);

  // for debugging only
  g_World->SetDebugDraw(&g_DebugDraw);
  g_DebugDraw.SetFlags(b2DebugDraw::e_shapeBit);

}

// ------------------------------------------------------------------------

t_time g_tmLast = milliseconds();

void phy_step()
{
  t_time now = milliseconds();
  if (now - g_tmLast > 10) {
    // step the engine
    // NOTE: here we use a fixed step
    float timeStep = 0.25f;
    int velocityIterations = 10; // number of internal velocity iters.
    int positionIterations = 10; // number of internal position iters.
    g_World->Step(timeStep, velocityIterations, positionIterations);
    g_tmLast = now;
  }
}

// ------------------------------------------------------------------------

void phy_terminate()
{
  if (g_World != NULL) {
    delete (g_World);
  }
}

// ------------------------------------------------------------------------

extern int    c_ScreenW;
extern int    c_ScreenH;

void phy_debug_draw()
{
  Transform::ortho2D(LIBSL_PROJECTION_MATRIX, 0, c_ScreenW, 0, c_ScreenH);
  Transform::identity(LIBSL_MODELVIEW_MATRIX);
  g_World->DrawDebugData();
}

// ------------------------------------------------------------------------
