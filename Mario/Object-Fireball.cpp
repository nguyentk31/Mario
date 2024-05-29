#include "Object-Fireball.h"

void CFireball::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FIREBALL_WIDTH / 2;
	t = y - FIREBALL_HEIGHT / 2;
	r = l + FIREBALL_WIDTH;
	b = t + FIREBALL_HEIGHT;
}

void CFireball::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	x += vx * dt;
	y += vy * dt;
}

void CFireball::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_FIREBALL)->Render(x,y);
}
