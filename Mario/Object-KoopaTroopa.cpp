#include "Object-KoopaTroopa.h"
#include "Object-QuestionBlock.h"
#include "Object-Goomba.h"
#include "Object-VenusFireTrap.h"
#include "Mario.h"
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
}

void CKoopaTroopa::OnOverlapseWith(vector<LPCOLLISIONEVENT> evnets) {
	if (state == KOOPA_TROOPA_STATE_WALKING && evnets[0]->obj->IsBlocking())
		SetState(KOOPA_TROOPA_STATE_DIE);
}

void CKoopaTroopa::OnCollisionWith(vector<LPCOLLISIONEVENT> events)
{
	LPCOLLISIONEVENT e = events[0];
	if (e->obj->IsBlocking()) {
		if (e->ny != 0 )
			vy = 0;
		else if (e->nx != 0)
			vx = -vx;

		if (state == KOOPA_TROOPA_STATE_ROLLING && dynamic_cast<CQuestionBlock*>(e->obj))
			e->obj->SetState(QUESTION_BLOCK_STATE_BOUNCING);
		else if (state == KOOPA_TROOPA_STATE_JUMPING && e->ny < 0)
			vy = -KOOPA_TROPPA_JUMPING_SPEED;
	} else {
		if (state == KOOPA_TROOPA_STATE_ROLLING) {
			if (dynamic_cast<CGoomba*>(e->obj) && e->obj->GetState() != GOOMBA_STATE_DIE)
				e->obj->SetState(GOOMBA_STATE_DIE);
			else if (dynamic_cast<CVenusFireTrap*>(e->obj))
				e->obj->Delete();
		} else if (state == KOOPA_TROOPA_STATE_SHELL || state == KOOPA_TROOPA_STATE_REVIVE) {
			if (dynamic_cast<CGoomba*>(e->obj) && e->obj->GetState() != GOOMBA_STATE_DIE) {
				e->obj->SetState(GOOMBA_STATE_DIE);
				SetState(KOOPA_TROOPA_STATE_DIE);
			} else if (dynamic_cast<CVenusFireTrap*>(e->obj)) {
				e->obj->Delete();
				SetState(KOOPA_TROOPA_STATE_DIE);
			}
		}
	}
}

void CKoopaTroopa::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (state == KOOPA_TROOPA_STATE_DIE && GetTickCount64() - die_start > KOOPA_TROOPA_STATE_DIE_TIMEOUT) {
		isDeleted = true;
		return;
	} else if (state == KOOPA_TROOPA_STATE_SHELL && GetTickCount64() - shell_start > KOOPA_TROOPA_STATE_SHELL_TIMEOUT)
		SetState(KOOPA_TROOPA_STATE_REVIVE);
	else if (state == KOOPA_TROOPA_STATE_REVIVE && GetTickCount64() - revive_start > KOOPA_TROOPA_STATE_REVIVE_TIMEOUT)
		SetState(KOOPA_TROOPA_STATE_WALKING);
	else if (state == KOOPA_TROOPA_STATE_ROLLING || state == KOOPA_TROOPA_STATE_WALKING || state == KOOPA_TROOPA_STATE_JUMPING || state == KOOPA_TROOPA_STATE_DIE) {
		vy += ay * dt;
		
		if (state == KOOPA_TROOPA_STATE_WALKING) {
			// Check whether present Koopa Troopa will falling or not
			CKoopaTroopa *presentKoopaTroopa = new CKoopaTroopa(x, y);
			presentKoopaTroopa->SetSpeed(vx, vy);
			CCollision::GetInstance()->Process(presentKoopaTroopa, dt, coObjects);
			float presentSpeedX, presentSpeedY;
			presentKoopaTroopa->GetSpeed(presentSpeedX, presentSpeedY);
			// if present Koopa Troopa is not falling then check whether future Koopa Troopa will falling or not
			if (presentSpeedY == 0)
			{
				DWORD forcast_period = static_cast<DWORD>(KOOPA_TROOPA_FORCAST_PIXEL / KOOPA_TROOPA_WALKING_SPEED);
				CKoopaTroopa *futureKoopaTroopa = new CKoopaTroopa(x+vx*forcast_period, y);
				futureKoopaTroopa->SetSpeed(vx, vy);
				CCollision::GetInstance()->Process(futureKoopaTroopa, dt, coObjects);
				float futureSpeedX, futureSpeedY;
				futureKoopaTroopa->GetSpeed(futureSpeedX, futureSpeedY);
				// if future Koopa Troopa is falling then turn back
				if (futureSpeedY > 0) {
					vx = -vx;
					
					delete presentKoopaTroopa;
					delete futureKoopaTroopa;
					return;
				}
				delete futureKoopaTroopa;
			}
			// If present Koopa Troopa is falling then let it fall
			// Or if future Koopa Troopa is not falling then let it walk
			presentKoopaTroopa->GetPosition(this->x, this->y);
			presentKoopaTroopa->GetSpeed(this->vx, this->vy);
			
			delete presentKoopaTroopa;
			int i = 0;
			return;
		}
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopaTroopa::Render()
{
	int ani = -1;
	switch (state)
	{
		case KOOPA_TROOPA_STATE_JUMPING:
			if (vx > 0)
				CAnimations::GetInstance()->Get(ID_ANI_GOOMBA_FLY_WING_LEFT)->Render(x-6, y-8);
			else
				CAnimations::GetInstance()->Get(ID_ANI_GOOMBA_FLY_WING_RIGHT)->Render(x+6, y-8);
		case KOOPA_TROOPA_STATE_WALKING:
			if (vx > 0)
				ani = ID_ANI_KOOPA_TROOPA_WALKING_RIGHT;
			else
				ani = ID_ANI_KOOPA_TROOPA_WALKING_LEFT;
			break;
		case KOOPA_TROOPA_STATE_DIE:
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
		case KOOPA_TROOPA_STATE_JUMPING:
			vx = -KOOPA_TROOPA_WALKING_SPEED;
			vy = 0;
			break;
		case KOOPA_TROOPA_STATE_WALKING:
			// if Mario is holding shell then Koopa Troopa will only change state then Mario will update the state later
			if (isOnHold)
				break;
			else if (this->state == KOOPA_TROOPA_STATE_REVIVE){
				y -= (2+KOOPA_TROOPA_BBOX_HEIGHT - KOOPA_TROOPA_SHELL_BBOX_HEIGHT)/2;
			}
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
			break;
		case KOOPA_TROOPA_STATE_REVIVE:
			revive_start = GetTickCount64();
			break;
		case KOOPA_TROOPA_STATE_DIE:
			vy = -KOOPA_TROOPA_DEFLECT_SPEED;
			die_start = GetTickCount64();
			break;
	}
	CGameObject::SetState(state);
}
