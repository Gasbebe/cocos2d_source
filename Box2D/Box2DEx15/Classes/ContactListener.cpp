#include "ContactListener.h"

ConstactListener::ConstactListener() {
	
}
ConstactListener::~ConstactListener() {

}

void ConstactListener::BeginContact(b2Contact *contact) {
	log("Contact Began");
}
void ConstactListener::EndContact(b2Contact *contact) {
	log("Contact End");
}
void ConstactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {
	log("Contact PreSolve");
}
void ConstactListener::PostSolve(b2Contact *contact, const b2ContactImpulse * impulse) {
	log("Contact PostSolve....1");

	b2Fixture *fixA = contact->GetFixtureA();
	b2Fixture *fixB = contact->GetFixtureB();

	b2Body *bodyA = fixA->GetBody();
	b2Body *bodyB = fixB->GetBody();

	if (bodyA->GetType() == b2_dynamicBody || bodyB->GetType() == b2_dynamicBody) {
		log("Contact: impulse ...%f ", impulse->normalImpulses[0]);
	}
}
