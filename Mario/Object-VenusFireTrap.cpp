#include "Object-VenusFireTrap.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Object-Fireball.h"

void CVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float mario_x, mario_y;
	mario->GetPosition(mario_x, mario_y);
	float distance = abs(x - mario_x);
	bool is_in_attack_zone = distance >= ATTACT_ZONE_MIN && distance <= ATTACT_ZONE_MAX;
	ULONGLONG now = GetTickCount();
	y += vy * dt;

	if ( state == VFT_STATE_HIDE )
	{
		if ( now - last_hide < VFT_HIDE_TIME)
			return;

		// rise only when mario is in attack zone
		if ( now - last_hide > VFT_HIDE_TIME && is_in_attack_zone ) {
			SetState(VFT_STATE_RISING);
		}
	}
	else if ( state == VFT_STATE_RISING )
	{
		if ( y > start_y - VFT_HEIGHT )
			return;

		// if mario is out of attack zone, falling immediately, else aiming
		if ( y <= start_y - VFT_HEIGHT ) {
			if ( is_in_attack_zone ) {
				SetState(VFT_STATE_AIMING);
			}
			else {
				SetState(VFT_STATE_FALLING);
			}
		}
	}
	else if ( state == VFT_STATE_AIMING )
	{
		if ( GetTickCount() - aiming_start > VFT_AIMING_TIME ) {
			ShootFireball(mario_x, mario_y);
			SetState(VFT_STATE_SHOOTING);
		}
		else {
			return;
		}
	}
	else if ( state == VFT_STATE_SHOOTING )
	{
		if ( GetTickCount() - shooting_start > VFT_SHOOTING_TIME ) {
			SetState(VFT_STATE_FALLING);
		}
		else {
			return;
		}
	}
	else if ( state == VFT_STATE_FALLING )
	{
		if ( y < start_y )
			return;

		if ( y >= start_y ) {
			// if mario is out of attack zone, restart the hide cycle
			// so when mario is in attack zone, the plant will rise immediately
			if ( !is_in_attack_zone )
				last_hide = GetTickCount() - VFT_HIDE_TIME;
			else 
				last_hide = GetTickCount();
			SetState(VFT_STATE_HIDE);
		}

	}
}

void CVenusFireTrap::SetState(int state)
{
	switch (state)
	{
		case VFT_STATE_HIDE:
			y = start_y;
			vy = 0;
			break;
		case VFT_STATE_RISING:
			vy = -VFT_UP_DOWN_SPEED;
			break;
		case VFT_STATE_AIMING:
			aiming_start = GetTickCount();
			y = start_y - VFT_HEIGHT;
			vy = 0;
			break;
		case VFT_STATE_SHOOTING:
			shooting_start = GetTickCount();
			break;
		case VFT_STATE_FALLING:
			vy = VFT_UP_DOWN_SPEED;
			break;
	}
	CGameObject::SetState(state);
}

void CVenusFireTrap::ShootFireball(float mario_x, float mario_y) {
	float fireball_vx, fireball_vy;
	GetFireballVxVy(mario_x, mario_y, fireball_vx, fireball_vy);
	CFireball* fireball = new CFireball(x, y-VFT_HEIGHT/4, fireball_vx, fireball_vy);
	CPlayScene* current_scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	current_scene->AddObject(fireball);
}

void CVenusFireTrap::GetFireballVxVy(float mario_x, float mario_y, float &vx, float &vy)
{
	// calculate the angle between the plant and mario
	float dx = mario_x - x;
	float dy = mario_y - y;
	float angle = atan2(dx, dy);

	// Define allowed angles (8 directions, 4 left and 4 right)
	const float allowed_angles[] = {
		+ M_PI / 4.0f,
		+ 2 * M_PI / 4.0f,
		+ 3 * M_PI / 4.0f,
		+ 4 * M_PI / 4.0f,
		- M_PI / 4.0f,
		- 2 * M_PI / 4.0f,
		- 3 * M_PI / 4.0f,
		- 4 * M_PI / 4.0f
	};

	// Find the closest angle in the allowed angles
	float closest_angle = *min_element(allowed_angles, allowed_angles + sizeof(allowed_angles) / sizeof(allowed_angles[0]),
		[angle](float a1, float a2) { return abs(a1 - angle) < abs(a2 - angle); });

	// Calculate vx and vy using the closest angle
	vx = FIREBALL_SPEED * sin(closest_angle);
	vy = FIREBALL_SPEED * cos(closest_angle);
}

void CVenusFireTrap::Render()
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	float mario_x, mario_y;
	mario->GetPosition(mario_x, mario_y);
	int ani_spr_id = GetAnimationOrSprite(mario_x, mario_y);
	switch (state)
	{
		case VFT_STATE_RISING:
		case VFT_STATE_FALLING:
			CAnimations::GetInstance()->Get(ani_spr_id)->Render(x,y);
			break;
		case VFT_STATE_AIMING:
		case VFT_STATE_SHOOTING:
			CSprites::GetInstance()->Get(ani_spr_id)->Draw(x, y);
			break;
		default:
			break;
	}
}

int CVenusFireTrap::GetAnimationOrSprite(float mario_x, float mario_y)
{
	if ( x < mario_x )
	{
		if ( y < mario_y )
			return VFT_ANI_SPR_DOWN_RIGHT;
		else
			return VFT_ANI_SPR_UP_RIGHT;
	}
	else
	{
		if ( y < mario_y )
			return VFT_ANI_SPR_DOWN_LEFT;
		else
			return VFT_ANI_SPR_UP_LEFT;
	}
}

void CVenusFireTrap::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x - VFT_WIDTH/2;
	top = y - VFT_HEIGHT/2;
	right = left + VFT_WIDTH;
	bottom = top + VFT_HEIGHT;
}
