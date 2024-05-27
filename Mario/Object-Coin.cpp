#include "Object-Coin.h"

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if ( this->state != COIN_STATE_BOUNDING )
		return;

	if (this->y < this->originalY - COIN_BOUCING_DISTANCE && this->vy < 0) 
	{
		this->vy = COIN_BOUCING_SPEED;
	}
	else if (this->y > this->originalY - COIN_BOUCING_DISTANCE / 2 && this->vy > 0)
	{
		this->Delete();
	}

	y += vy * dt;
}

void CCoin::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_COIN)->Render(x, y);
}

int CCoin::IsCollidable()
{
	return (this->state == COIN_STATE_BOUNDING);
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_SIZE / 2;
	t = y - COIN_SIZE / 2;
	r = l + COIN_SIZE;
	b = t + COIN_SIZE;
}