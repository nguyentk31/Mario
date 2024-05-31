#pragma once
#include "GameObject.h"

#define VFT_HEIGHT 32
#define VFT_WIDTH 16

#define VFT_UP_DOWN_SPEED 0.05f

#define VFT_STATE_HIDE 1
#define VFT_STATE_RISING 2
#define VFT_STATE_AIMING 3
#define VFT_STATE_SHOOTING 4
#define VFT_STATE_FALLING 5

#define VFT_HIDE_TIME 1000
#define VFT_AIMING_TIME 1000
#define VFT_SHOOTING_TIME 1000

#define ATTACT_ZONE_MIN 32
#define ATTACT_ZONE_MAX 128

class CVenusFireTrap : public CGameObject
{
protected:
	float start_y;
	ULONGLONG last_hide, aiming_start, shooting_start;

	int GetAnimationOrSprite(float mario_x, float mario_y);
	void ShootFireball(float mario_x, float mario_y);
	void GetFireballVxVy(float mario_x, float mario_y, float &vx, float &vy);
public: 
	CVenusFireTrap(float x, float y) :CGameObject(OBJECT_TYPE_VENUS_FIRE_TRAP, x, y) {
		this->start_y = y;
		this->state = VFT_STATE_HIDE;
		this->last_hide = GetTickCount();
		this->vy = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; };
	void SetState(int state);
};