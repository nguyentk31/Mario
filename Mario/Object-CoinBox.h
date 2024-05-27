#pragma once
#include "GameObject.h"

#define COIN_BOX_WIDTH 16
#define COIN_BOX_HEIGHT 16

#define ID_ANI_COIN_BOX_ALIVE 91000
#define ID_ANI_COIN_BOX_DEAD 92000

#define COIN_BOX_STATE_BOUNCING 2
#define COIN_BOX_STATE_ALIVE 1
#define COIN_BOX_STATE_DEAD 0

#define BOUCING_SPEED 0.1f
#define BOUCING_DISTANCE 10 // Pixels

class CCoinBox : public CGameObject
{
protected:
	float originalY;
public:
	CCoinBox(float x, float y) : CGameObject(x, y) {
		this->state = COIN_BOX_STATE_ALIVE;
		this->originalY = y;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsCollidable();
	void OnCollisionWith(LPCOLLISIONEVENT e) {};
	void OnNoCollision(DWORD dt);
	void SetState(int state);
};

typedef CCoinBox* LPCOINBOX;