#include "Object-Goomba.h"

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;

	if ( (state==GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt)
{
	if (!e->obj->IsBlocking()) return; // Ignore if e->obj is not blocking

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Render()
{
	if (state == GOOMBA_STATE_DIE)
		CAnimations::GetInstance()->Get(ID_ANI_GOOMBA_DIE)->Render(x, y);
	else
		CAnimations::GetInstance()->Get(ID_ANI_GOOMBA_WALK)->Render(x,y);

}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
			break;
	}
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x - GOOMBA_BBOX_WIDTH/2;
	right = left + GOOMBA_BBOX_WIDTH;
	if (state == GOOMBA_STATE_DIE)
	{
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE - 2;
	}
	else
	{ 
		top = y - GOOMBA_BBOX_HEIGHT/2;
		bottom = top + GOOMBA_BBOX_HEIGHT - 2;
	}
}
