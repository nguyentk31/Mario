#include "Object-Mushroom.h"

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if ( state == MUSHROOM_STATE_UP && originalY - y >= MUSHROOM_SIZE )
	{
		SetState(MUSHROOM_STATE_NORMAL);
		vy += ay * dt;
	} else if (state != MUSHROOM_STATE_UP)
	{
		vy += ay * dt;
	}

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

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_UP:
		vy = -MUSHROOM_SPEED_UP;
		vx = 0;
		ay = 0;
		break;
	case MUSHROOM_STATE_NORMAL:
		ay = MUSHROOM_GRAVITY;
		vx = MUSHROOM_SPEED_X*directionX;
		break;
	case MUSHROOM_STATE_BOUNCING:
		vy = -MUSHROOM_SPEED_BOUNCING;
		break;
	}
}

void CMushroom::Render()
{
	CSprites::GetInstance()->Get(ID_SPRITE_MUSHROOM)->Draw(x, y);
}

void CMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MUSHROOM_SIZE / 2;
	t = y - MUSHROOM_SIZE / 2;
	r = l + MUSHROOM_SIZE;
	b = t + MUSHROOM_SIZE-1;
}