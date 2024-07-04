#pragma once
#include "GameObject.h"

#define PTOOIE_HEIGHT 32
#define PTOOIE_WIDTH 16

#define PTOOIE_UP_DOWN_SPEED 0.05f

#define PTOOIE_STATE_HIDE 1
#define PTOOIE_STATE_RISING 2
#define PTOOIE_STATE_HOLDING 3
#define PTOOIE_STATE_FALLING 4

#define PTOOIE_HIDE_TIME 1000
#define PTOOIE_HOLDING_TIME 1000

#define PTOOIE_ATTACT_ZONE_MIN 32
#define PTOOIE_ATTACT_ZONE_MAX 128

#define PTOOIE_COLOR_GREEN 1
#define PTOOIE_COLOR_RED 2

class CPtooie : public CGameObject
{
protected:
	float start_y;
	int color;
	float rising_distance;
	ULONGLONG last_hide, holding_start;
public:
	CPtooie(float x, float y, int cl, float rd) :CGameObject(OBJECT_TYPE_PTOOIE, x, y) {
		color = cl;
		rising_distance = rd;
		this->start_y = y;
		this->state = PTOOIE_STATE_HIDE;
		this->last_hide = GetTickCount();
		this->vy = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; };
	void SetState(int state);
};