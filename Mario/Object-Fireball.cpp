#include "Object-Fireball.h"
#include "Mario.h"


void CFireball::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FIREBALL_SIZE / 2;
	t = y - FIREBALL_SIZE / 2;
	r = l + FIREBALL_SIZE;
	b = t + FIREBALL_SIZE;
}

void CFireball::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	x += vx * dt;
	y += vy * dt;
}
