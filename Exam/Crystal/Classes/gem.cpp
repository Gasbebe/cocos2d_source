#include "GameScene.h"
#include "gem.h"
USING_NS_CC;

Gem::Gem() {

}
void Gem::SetTag(int num) {
	tagNum = num;
}
int Gem::GetTag() {
	return tagNum;
}
void Gem::createBox2D() {
	
	//바디데프를 만들고 속성을 저장한다
	Vec2 pos = GetPos();
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(pos.x / PTM_RATIO, pos.y / PTM_RATIO);
	//유저데이터에 스프라이트를 붙인다
	bodyDef.userData = gemSprite;
	b2Body* body = _world->CreateBody(&bodyDef);


	// 박스 모양의 객체 생성
	Size size = GetSize();
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(size.width / 2 / PTM_RATIO, size.height / 2 / PTM_RATIO);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 2.0f;
	fixtureDef.friction = 0.2f;
	fixtureDef.restitution = 0.1f;
	body->CreateFixture(&fixtureDef);
	
}
void Gem::onEnter() {
	createBox2D();
	Sprite::onEnter();
}
void Gem::onExit(){
	Sprite::onExit();
}

Vec2 Gem::GetPos() {
	return gemPos;
}
void Gem::SetPos(Vec2 pos) {
	gemPos = pos;
}

Size Gem::GetSize() {
	return gemSize;
}

void Gem::SetSize(Size size) {
	gemSize = size;
}