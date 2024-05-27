#pragma once

#include "GameObject.h"

#define ID_ANI_COIN 40000

#define	COIN_SIZE 16

#define COIN_STATE_IDLE 0
#define COIN_STATE_BOUNDING 1

#define COIN_BOUCING_SPEED 0.2f
#define COIN_BOUCING_DISTANCE 48 // Pixels

class CCoin : public CGameObject {
protected:
	float originalY;
public:
	CCoin(float x, float y, int state = 0) : CGameObject(x, y) {
		this->state = state;
		if (state == COIN_STATE_BOUNDING) {
			this->originalY = y;
			vy = -COIN_BOUCING_SPEED;
		}
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable();
	int IsBlocking() { return 0; }
};