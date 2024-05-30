#pragma once
#include "GameObject.h"

#define KOOPA_TROOPA_GRAVITY 0.002f
#define KOOPA_TROOPA_WALKING_SPEED 0.03f

#define KOOPA_TROOPA_FORCAST_PIXEL 8

#define KOOPA_TROOPA_BBOX_WIDTH 16
#define KOOPA_TROOPA_BBOX_HEIGHT 27

#define KOOPA_TROOPA_STATE_WALKING 1

#define ID_ANI_KOOPA_TROOPA_WALKING_RIGHT 120100
#define ID_ANI_KOOPA_TROOPA_WALKING_LEFT 120200
#define ID_ANI_KOOPA_TROOPA_SHELL 120300
#define ID_ANI_KOOPA_TROOPA_REVIVE 120400

class CKoopaTroopa : public CGameObject
{
protected:
	float ay; 
public: 	
	CKoopaTroopa(float x, float y): CGameObject(x, y) {
		this->ay = KOOPA_TROOPA_GRAVITY;
		this->vx = -KOOPA_TROOPA_WALKING_SPEED;
		this->vy = 0;
		SetState(KOOPA_TROOPA_STATE_WALKING);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void SetState(int state);
};