#include "Object-KoopaTroopa.h"
#include "Object-QuestionBlock.h"
#include "Object-Goomba.h"
#include "Playscene.h"

void CKoopaTroopa::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x - KOOPA_TROOPA_BBOX_WIDTH/2;
	right = left + KOOPA_TROOPA_BBOX_WIDTH;
	if (state == KOOPA_TROOPA_STATE_WALKING) {
		top = y - KOOPA_TROOPA_BBOX_HEIGHT/2;
		bottom = top + KOOPA_TROOPA_BBOX_HEIGHT - 3;
	} else {
		top = y - KOOPA_TROOPA_SHELL_BBOX_HEIGHT/2;
		bottom = top + KOOPA_TROOPA_SHELL_BBOX_HEIGHT - 3;
	}
}

void CKoopaTroopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopaTroopa::OnCollisionWith(LPCOLLISIONEVENT e, DWORD dt)
{
	if (e->obj->IsBlocking()) {
		if (e->ny != 0 )
			vy = 0;
		else if (e->nx != 0)
			vx = -vx;

		if (dynamic_cast<CQuestionBlock*>(e->obj))
			e->obj->SetState(QUESTION_BLOCK_STATE_BOUNCING);
	} else {
		if (e->ny != 0 )
			y += vy * dt;
		else if (e->nx != 0)
			x += vx * dt;
		
		if (state == KOOPA_TROOPA_STATE_ROLLING) {
			if (dynamic_cast<CGoomba*>(e->obj) && e->obj->GetState() != GOOMBA_STATE_DIE)
				e->obj->SetState(GOOMBA_STATE_DIE);
		}
	}



}

void CKoopaTroopa::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;

	if (state == KOOPA_TROOPA_STATE_SHELL && GetTickCount64() - shell_start > KOOPA_TROOPA_STATE_SHELL_TIMEOUT)
		SetState(KOOPA_TROOPA_STATE_REVIVE);
	else if (state == KOOPA_TROOPA_STATE_REVIVE && GetTickCount64() - revive_start > KOOPA_TROOPA_STATE_REVIVE_TIMEOUT)
		SetState(KOOPA_TROOPA_STATE_WALKING);
	else if (state == KOOPA_TROOPA_STATE_WALKING) {
		DWORD forcast_period = static_cast<DWORD>(KOOPA_TROOPA_FORCAST_PIXEL / KOOPA_TROOPA_WALKING_SPEED);
		CKoopaTroopa *futureKoopaTroopa = new CKoopaTroopa(x+vx*forcast_period, y);
		futureKoopaTroopa->SetSpeed(vx, vy);
		CCollision::GetInstance()->Process(futureKoopaTroopa, dt, coObjects);
		float futureSpeedX, futureSpeedY;
		futureKoopaTroopa->GetSpeed(futureSpeedX, futureSpeedY);
		if (futureSpeedY > 0) {
			vx = -vx;
			return;
		}
		delete futureKoopaTroopa;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopaTroopa::Render()
{
	int ani = -1;
	switch (state)
	{
		case KOOPA_TROOPA_STATE_WALKING:
			if (vx > 0)
				ani = ID_ANI_KOOPA_TROOPA_WALKING_RIGHT;
			else
				ani = ID_ANI_KOOPA_TROOPA_WALKING_LEFT;
			break;
		case KOOPA_TROOPA_STATE_SHELL:
			ani = ID_ANI_KOOPA_TROOPA_SHELL;
			break;
		case KOOPA_TROOPA_STATE_ROLLING:
			ani = ID_ANI_KOOPA_TROOPA_ROLLING;
			break;
		case KOOPA_TROOPA_STATE_REVIVE:
			ani = ID_ANI_KOOPA_TROOPA_REVIVE;
			break;
	}
	if (ani != -1)
		CAnimations::GetInstance()->Get(ani)->Render(x, y);
}

void CKoopaTroopa::SetState(int state)
{
	switch (state)
	{
		case KOOPA_TROOPA_STATE_WALKING:
			if (this->state == KOOPA_TROOPA_STATE_REVIVE)
				y -= (2+KOOPA_TROOPA_BBOX_HEIGHT - KOOPA_TROOPA_SHELL_BBOX_HEIGHT)/2;
			vx = -KOOPA_TROOPA_WALKING_SPEED;
			vy = 0;
			break;
		case KOOPA_TROOPA_STATE_SHELL:
			if (this->state == KOOPA_TROOPA_STATE_WALKING) {
				y += (KOOPA_TROOPA_BBOX_HEIGHT - KOOPA_TROOPA_SHELL_BBOX_HEIGHT)/2;
			}
			shell_start = GetTickCount64();
			vx = 0;
			vy = 0;
			break;
		case KOOPA_TROOPA_STATE_ROLLING:
			float xpos, ypos;
			((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetPosition(xpos, ypos);
			if (x < xpos)
				vx = -KOOPA_TROOPA_ROLLING_SPEED;
			else
				vx = KOOPA_TROOPA_ROLLING_SPEED;
			vy = 0;
			break;
		case KOOPA_TROOPA_STATE_REVIVE:
			revive_start = GetTickCount64();
			break;
	}
	CGameObject::SetState(state);
}
