#pragma once
#include "GameObject.h"

#define BB_SIZE 16

#define BB_STATE_NORMAL 1
#define BB_STATE_BOUCING 2
#define BB_STATE_BROKING 3
#define BB_STATE_UNBROKEN 4
#define BB_STATE_BROKEN 5
#define BB_STATE_COIN 6

#define BB_TIMEOUT_COIN 5000
#define BB_TIMEOUT_BROKING 150

#define BB_TYPE_COIN 1
#define BB_TYPE_SWITCH 2

#define BB_BROKING_SPEED 0.1f
#define BB_BOUCING_SPEED 0.2f
#define BB_GRAVITY 0.002f

#define BB_ANI_NORMAL 141000
#define BB_SPRITE_UNBROKEN 141500
#define BB_SPRITE_COIN 142100
#define BB_SPRITE_BROKEN_PIECE 143100

class CBreakableBrick : public CGameObject
{
protected:
	float brokingX, brokingY;
	ULONGLONG brokingStart, coinStart;
	float originalY;
	float ay;
	int BBType;
public:
	CBreakableBrick(float x, float y, int type) : CGameObject(OBJECT_TYPE_BREAKABLE_BRICK, x, y) {
		ay = BB_GRAVITY;
		vy = 0;
		state = BB_STATE_NORMAL;
		originalY = y;
		BBType = type;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsBlocking();
	int IsCollidable();
	void SetState(int state);
	void Hit();
};