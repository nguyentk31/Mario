#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.0005f
#define GOOMBA_WALKING_SPEED 0.05f
#define GOOMBA_FLY_SPEED 0.15f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 16
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500
#define GOOMBA_FLY_TIMEOUT 1500

#define GOOMBA_STATE_WALKING 1
#define GOOMBA_STATE_DIE 2
#define GOOMBA_STATE_FLY 3

#define GOOMBA_LEVEL_NORMAL 1
#define GOOMBA_LEVEL_FLY 2

#define GOOMBA_COLOR_BROWN 1
#define GOOMBA_COLOR_RED 2

class CGoomba : public CGameObject
{
protected:			
	float ay;
	int level, color;
	ULONGLONG die_start, fly_start;
public: 	
	CGoomba(float x, float y, int cl, int lv): CGameObject(OBJECT_TYPE_GOOMBA, x, y) {
		level = lv;
		color = cl;
		vx = -GOOMBA_WALKING_SPEED;
		ay = GOOMBA_GRAVITY;
		die_start = -1;
		fly_start = -1;
		SetState(GOOMBA_STATE_WALKING);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void HitByTop();
	void HitBySide() {};
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(vector<LPCOLLISIONEVENT> events);
	void SetState(int state);
};