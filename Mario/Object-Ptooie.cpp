#include "Object-Ptooie.h"
#include "Mario.h"
#include "PlayScene.h"

void CPtooie::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float mario_x, mario_y;
	mario->GetPosition(mario_x, mario_y);
	float distance = abs(x - mario_x);
	bool is_in_attack_zone = distance >= PTOOIE_ATTACT_ZONE_MIN && distance <= PTOOIE_ATTACT_ZONE_MAX;
	ULONGLONG now = GetTickCount();
	y += vy * dt;

	if ( state == PTOOIE_STATE_HIDE )
	{
		if ( now - last_hide < PTOOIE_HIDE_TIME)
			return;

		// rise only when mario is in attack zone
		if ( now - last_hide > PTOOIE_HIDE_TIME && is_in_attack_zone ) {
			SetState(PTOOIE_STATE_RISING);
		}
	}
	else if ( state == PTOOIE_STATE_RISING )
	{
		if ( y > start_y - rising_distance )
			return;

		// if mario is out of attack zone, falling immediately, else aiming
		if ( y <= start_y - rising_distance ) {
			if ( is_in_attack_zone ) {
				SetState(PTOOIE_STATE_HOLDING);
			}
			else {
				SetState(PTOOIE_STATE_FALLING);
			}
		}
	}
	else if ( state == PTOOIE_STATE_HOLDING )
	{
		if ( GetTickCount() - holding_start > PTOOIE_HOLDING_TIME ) {
			SetState(PTOOIE_STATE_FALLING);
		}
		else {
			return;
		}
	}
	else if ( state == PTOOIE_STATE_FALLING )
	{
		if ( y < start_y )
			return;

		if ( y >= start_y ) {
			// if mario is out of attack zone, restart the hide cycle
			// so when mario is in attack zone, the plant will rise immediately
			if ( !is_in_attack_zone )
				last_hide = GetTickCount() - PTOOIE_HIDE_TIME;
			else 
				last_hide = GetTickCount();
			SetState(PTOOIE_STATE_HIDE);
		}

	}
}

void CPtooie::SetState(int state)
{
	switch (state)
	{
		case PTOOIE_STATE_HIDE:
			y = start_y;
			vy = 0;
			break;
		case PTOOIE_STATE_RISING:
			vy = -PTOOIE_UP_DOWN_SPEED;
			break;
		case PTOOIE_STATE_HOLDING:
			holding_start = GetTickCount();
			y = start_y - rising_distance;
			vy = 0;
			break;
		case PTOOIE_STATE_FALLING:
			vy = PTOOIE_UP_DOWN_SPEED;
			break;
	}
	CGameObject::SetState(state);
}

void CPtooie::Render()
{
	int ani_id = PTOOIE_ANI_GREEN;
	CAnimations::GetInstance()->Get(ani_id)->Render(x,y);
}

void CPtooie::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x - PTOOIE_WIDTH/2;
	top = y - PTOOIE_HEIGHT/2;
	right = left + PTOOIE_WIDTH;
	bottom = top + PTOOIE_HEIGHT;
}
