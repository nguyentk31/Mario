#pragma once

#include "GameObject.h"

#define MUSHROOM_SPRITE_ID 11000

#define	MUSHROOM_SIZE 16
#define MUSHROOM_SPEED_X 0.05f
#define MUSHROOM_SPEED_UP 0.01f
#define MUSHROOM_GRAVITY 0.005f


class CMushroom : public CGameObject {
protected:
	int directionX;
	float upDistance;
	float originalY;
	float ay;
public:
	CMushroom(float x, float y, int directionX, float upDistance) : CGameObject(x, y) {
		this->directionX = directionX;
		this->upDistance = upDistance;
		originalY = y;
		vx = 0;
		vy = -MUSHROOM_SPEED_UP;
		ay = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	int IsCollidable() { return 1; };
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnNoCollision(DWORD dt);
	int IsBlocking() { return 0; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};