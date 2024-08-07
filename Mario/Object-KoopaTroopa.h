#pragma once
#include "GameObject.h"

#define KOOPA_TROOPA_GRAVITY 0.001f
#define KOOPA_TROOPA_WALKING_SPEED 0.03f
#define KOOPA_TROOPA_ROLLING_SPEED 0.25f
#define KOOPA_TROOPA_DEFLECT_SPEED 0.3f
#define KOOPA_TROPPA_JUMPING_SPEED 0.35f

#define KOOPA_TROOPA_FORCAST_PIXEL 8

#define KOOPA_TROOPA_BBOX_WIDTH 14
#define KOOPA_TROOPA_BBOX_HEIGHT 27
#define KOOPA_TROOPA_SHELL_BBOX_HEIGHT 16

#define KOOPA_TROOPA_STATE_WALKING 1
#define KOOPA_TROOPA_STATE_SHELL 2
#define KOOPA_TROOPA_STATE_ROLLING 3
#define KOOPA_TROOPA_STATE_REVIVE 4
#define KOOPA_TROOPA_STATE_DIE 5
#define KOOPA_TROOPA_STATE_JUMPING 6

#define KOOPA_TROOPA_STATE_DIE_TIMEOUT 500
#define KOOPA_TROOPA_STATE_SHELL_TIMEOUT 5000
#define KOOPA_TROOPA_STATE_REVIVE_TIMEOUT 2000

#define KOOPA_TROOPA_LEVEL_NORMAL 1
#define KOOPA_TROOPA_LEVEL_FLY 2

#define KOOPA_TROOPA_COLOR_BROWN 1
#define KOOPA_TROOPA_COLOR_GREEN 2

class CKoopaTroopa : public CGameObject
{
protected:
	float ay;
	int color;
	ULONGLONG shell_start, revive_start, die_start;
	bool isOnHold;
public: 	
	CKoopaTroopa(float x, float y, int cl = 1, int lv = 1): CGameObject(OBJECT_TYPE_KOOPA_TROOPA, x, y) {
		color = cl;
		ay = KOOPA_TROOPA_GRAVITY;
		isOnHold = false;
		if (lv == KOOPA_TROOPA_LEVEL_NORMAL)
			SetState(KOOPA_TROOPA_STATE_WALKING);
		else
			SetState(KOOPA_TROOPA_STATE_JUMPING);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void OnHold(bool x) { isOnHold = x; }

	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(vector<LPCOLLISIONEVENT> events);
	void OnOverlapseWith(vector<LPCOLLISIONEVENT> events);
	void SetState(int state);
};

typedef CKoopaTroopa* LPKOOPATROOPA;