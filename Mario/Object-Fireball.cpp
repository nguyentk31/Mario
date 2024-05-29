#include "Object-Fireball.h"
#include "Mario.h"


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

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFireball::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CMario*>(e->obj))
	{
		CMario* mario = dynamic_cast<CMario*>(e->obj);
		mario->Hit();
	}
}

void CFireball::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_FIREBALL)->Render(x,y);
}
