#ifndef __Box2dEx18_ContactListener__
#define __Box2dEx18_ContactListener__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

using namespace cocos2d;

class ConstactListener : public b2ContactListener
{
public:
	ConstactListener();
	~ConstactListener();

	virtual void BeginContact(b2Contact *contact);
	virtual void EndContact(b2Contact *contact);
	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
	virtual void PostSolve(b2Contact *contact, const b2ContactImpulse * impulse);

};

#endif // __HELLOWORLD_SCENE_H__
