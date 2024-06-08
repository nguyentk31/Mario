#include "Object-Goomba.h"

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	if (level == GOOMBA_LEVEL_FLY) {
		if (state == GOOMBA_STATE_WALKING && GetTickCount64() - fly_start > GOOMBA_FLY_TIMEOUT)
		{
			SetState(GOOMBA_STATE_FLY);
		} else if (state == GOOMBA_STATE_FLY && vy > 0)
		{
			SetState(GOOMBA_STATE_WALKING);
		}
	}
	
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

void CGoomba::OnCollisionWith(vector<LPCOLLISIONEVENT> events)
{
	LPCOLLISIONEVENT e = events[0];
	if (e->obj->IsBlocking()) {
		if (e->ny != 0 )
			vy = 0;
		else if (e->nx != 0)
			vx = -vx;

	} else {
		if (dynamic_cast<CGoomba*>(e->obj) && e->nx != 0) {
			e->obj->SetVx(-e->obj->GetVx());
			vx = -vx;
		}
	}

}

void CGoomba::Render()
{
	int ani = -1;
	switch (color)
	{
		case GOOMBA_COLOR_RED:
			if (state == GOOMBA_STATE_DIE)
				ani = ID_ANI_RED_GOOMBA_DIE;
			else
				ani = ID_ANI_RED_GOOMBA_WALK;
			break;
		default:
			if (state == GOOMBA_STATE_DIE)
				ani = ID_ANI_BROWN_GOOMBA_DIE;
			else
				ani = ID_ANI_BROWN_GOOMBA_WALK;
			break;
	}
	CAnimations *animations = CAnimations::GetInstance();
	animations->Get(ani)->Render(x, y);
	if (level == GOOMBA_LEVEL_FLY) {
		if (state == GOOMBA_STATE_FLY || (state == GOOMBA_STATE_WALKING && GetTickCount64() - fly_start > GOOMBA_FLY_TIMEOUT - 500)) {
			animations->Get(ID_ANI_GOOMBA_FLY_WING_LEFT)->Render(x-6, y-7);
			animations->Get(ID_ANI_GOOMBA_FLY_WING_RIGHT)->Render(x+6, y-7);
		} else {
			animations->Get(ID_ANI_GOOMBA_WING_LEFT)->Render(x-6, y-7);
			animations->Get(ID_ANI_GOOMBA_WING_RIGHT)->Render(x+6, y-7);
		}
	}
}

void CGoomba::HitByTop()
{
	if (level == GOOMBA_LEVEL_FLY) {
		level = GOOMBA_LEVEL_NORMAL;
	} else {
		SetState(GOOMBA_STATE_DIE);
	}
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
			break;
		case GOOMBA_STATE_FLY:
			vy = -GOOMBA_FLY_SPEED;
			fly_start = GetTickCount64();
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
