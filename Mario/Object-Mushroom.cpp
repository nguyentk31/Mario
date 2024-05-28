#include "Object-Mushroom.h"
#include "debug.h"

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

	if ( this->vx == 0 && this->originalY - this->y >= this->upDistance )
	{
		ay = MUSHROOM_GRAVITY;
		vx = MUSHROOM_SPEED_X*directionX;
	} else if ( this-> vx == 0 ) {
		vy = -MUSHROOM_SPEED_UP;
		y += vy * dt;
		return;
	}

	vy += ay * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CMushroom::Render()
{
	CSprites::GetInstance()->Get(MUSHROOM_SPRITE_ID)->Draw(x, y);
}

void CMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MUSHROOM_SIZE / 2;
	t = y - MUSHROOM_SIZE / 2;
	r = l + MUSHROOM_SIZE;
	b = t + MUSHROOM_SIZE-1;
}