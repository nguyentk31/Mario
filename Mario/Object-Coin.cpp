#include "Object-Coin.h"

void CCoin::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_COIN)->Render(x, y);
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_SIZE / 2;
	t = y - COIN_SIZE / 2;
	r = l + COIN_SIZE;
	b = t + COIN_SIZE;
}