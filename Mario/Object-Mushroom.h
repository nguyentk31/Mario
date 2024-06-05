#pragma once
#include "GameObject.h"

#define	MUSHROOM_SIZE 16

#define MUSHROOM_SPEED_X 0.05f
#define MUSHROOM_SPEED_UP 0.01f
#define MUSHROOM_GRAVITY 0.002f

#define MUSHROOM_SPEED_BOUNCING 0.3f

#define MUSHROOM_STATE_UP 0
#define MUSHROOM_STATE_NORMAL 1
#define MUSHROOM_STATE_BOUNCING 2


class CMushroom : public CGameObject {
protected:
	int directionX;
	float originalY;
	float ay;
public:
	CMushroom(float x, float y, int directionX) : CGameObject(OBJECT_TYPE_MUSHROOM, x, y) {
		this->directionX = directionX;
		originalY = y;
		SetState(MUSHROOM_STATE_UP);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	int IsCollidable() { return 1; };
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(vector<LPCOLLISIONEVENT> events);
	int IsBlocking() { return 0; }
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};