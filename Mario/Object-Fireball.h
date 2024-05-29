#pragma once
#include "GameObject.h"

#define FIREBALL_WIDTH 6
#define FIREBALL_HEIGHT 6

#define ID_ANI_FIREBALL 110000

#define FIREBALL_SPEED 0.05f

class CFireball : public CGameObject
{
public: 	
	CFireball(float x, float y, float vx, float vy): CGameObject(x, y) {
		this->vx = vx;
		this->vy = vy;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
};