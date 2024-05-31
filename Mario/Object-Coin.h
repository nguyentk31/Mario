#pragma once
#include "GameObject.h"

#define	COIN_SIZE 15

#define COIN_STATE_IDLE 0
#define COIN_STATE_BOUNCING 1

#define COIN_FALLLING_PERIOD 200
#define COIN_GRAVITY 0.002f
#define COIN_SPEED_BOUNCING 0.5f


class CCoin : public CGameObject {
protected:
	float ay;
	int falling_period;
public:
	CCoin(float x, float y) : CGameObject(OBJECT_TYPE_COIN, x, y) {
		ay = COIN_GRAVITY;
		falling_period = COIN_FALLLING_PERIOD;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render() { CAnimations::GetInstance()->Get(ID_ANI_COIN)->Render(x, y); }
	int IsCollidable() { return vy != 0; }
	int IsBlocking() { return 0; }
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};