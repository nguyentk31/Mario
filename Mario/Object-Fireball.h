#pragma once
#include "GameObject.h"

#define FIREBALL_SIZE 6

#define FIREBALL_SPEED 0.05f

class CFireball : public CGameObject
{
public: 	
	CFireball(float x, float y, float vx, float vy): CGameObject(OBJECT_TYPE_FIREBALL, x, y) {
		this->vx = vx;
		this->vy = vy;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render() { CAnimations::GetInstance()->Get(ID_ANI_FIREBALL)->Render(x,y); }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
};