#include "Object-KoopaTroopa.h"

void CKoopaTroopa::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x - KOOPA_TROOPA_BBOX_WIDTH/2;
	right = left + KOOPA_TROOPA_BBOX_WIDTH;
	if (state == KOOPA_TROOPA_STATE_WALKING)
	{
		top = y - KOOPA_TROOPA_BBOX_HEIGHT/2;
		bottom = top + KOOPA_TROOPA_BBOX_HEIGHT - 3;
	}
}

void CKoopaTroopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopaTroopa::OnCollisionWith(LPCOLLISIONEVENT e)
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

void CKoopaTroopa::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;

	if (state == KOOPA_TROOPA_STATE_WALKING) {
		DWORD forcast_period = static_cast<DWORD>(KOOPA_TROOPA_FORCAST_PIXEL / KOOPA_TROOPA_WALKING_SPEED);
		CKoopaTroopa *futureKoopaTroopa = new CKoopaTroopa(x+vx*forcast_period, y);
		futureKoopaTroopa->SetSpeed(vx, vy);
		CCollision::GetInstance()->Process(futureKoopaTroopa, dt, coObjects);
		float futureSpeedX, futureSpeedY;
		futureKoopaTroopa->GetSpeed(futureSpeedX, futureSpeedY);
		if (futureSpeedY > 0) {
			vx = -vx;
		} else {
			CCollision::GetInstance()->Process(this, dt, coObjects);
		}
		delete futureKoopaTroopa;
		return;
	}
}


void CKoopaTroopa::Render()
{
	int ani = -1;
	switch (state)
	{
		case KOOPA_TROOPA_STATE_WALKING:
			if (vx > 0) {
				ani = ID_ANI_KOOPA_TROOPA_WALKING_RIGHT;
			}
			else {
				ani = ID_ANI_KOOPA_TROOPA_WALKING_LEFT;
			}
			break;
	}
	if (ani != -1)
	{
		CAnimations::GetInstance()->Get(ani)->Render(x, y);
	}
}

void CKoopaTroopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case KOOPA_TROOPA_STATE_WALKING:
			break;
	}
}
