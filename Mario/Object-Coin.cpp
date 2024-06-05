#include "Object-Coin.h"

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (vy > 0)
		falling_period -= dt;
	
	if (falling_period <= 0)
		isDeleted = true;
	else {
		y += vy * dt;
		vy += ay * dt;
	}
}

void CCoin::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case COIN_STATE_IDLE:
		vy = 0;
		break;
	case COIN_STATE_BOUNCING:
		vy = -COIN_SPEED_BOUNCING;
		break;
	}
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_SIZE / 2;
	t = y - COIN_SIZE / 2;
	r = l + COIN_SIZE;
	b = t + COIN_SIZE;
}