#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	
	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (holdingShell)
		HoldShell();
}

void CMario::HoldShell()
{
	if (shell == NULL) return;

	float shellX, shellY;

	if (shell->GetState() == KOOPA_TROOPA_STATE_DIE) {
		shell = NULL;
		holdingShell = false;
		return;
	}

	if (shell->GetState() != KOOPA_TROOPA_STATE_WALKING) {
		if (!usingSkill) {
			shell->OnHold(false);
			shell->SetState(KOOPA_TROOPA_STATE_ROLLING);
			holdingShell = false;
		}
		shellX = x + (nx > 0 ? 1 : -1) * (MARIO_BIG_BBOX_WIDTH+KOOPA_TROOPA_BBOX_WIDTH-8)/2;
		shellY = y;
		shell->SetPosition(shellX, shellY);
	} else {
		if (level == MARIO_LEVEL_SMALL) {
			shellX = x + (nx > 0 ? 1 : -1) * (MARIO_SMALL_BBOX_WIDTH+KOOPA_TROOPA_BBOX_WIDTH+4)/2;
			shellY = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		} else {
			shellX = x + (nx > 0 ? 1 : -1) * (MARIO_BIG_BBOX_WIDTH+KOOPA_TROOPA_BBOX_WIDTH+4)/2;
			shellY = y - MARIO_BIG_BBOX_HEIGHT / 2;
		}
		shell->SetPosition(shellX, shellY);
		shell->OnHold(false);
		shell->SetState(KOOPA_TROOPA_STATE_WALKING);
		holdingShell = false;
	}
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(vector<LPCOLLISIONEVENT> events)
{
	LPCOLLISIONEVENT e = events[0];
	if (e->obj->IsBlocking()) {
		if (e->ny != 0 && e->obj->IsBlocking())
		{
			vy = 0;
			if (e->ny < 0) isOnPlatform = true;
		}
		else if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = 0;
		}

		if (e->obj->GetObjectTypeID() == OBJECT_TYPE_QUESTION_BLOCK && e->ny > 0)
			OnCollisionWithQuestionBlock(events);
		else if (e->obj->GetObjectTypeID() == OBJECT_TYPE_BREAKABLE_BRICK && e->ny > 0)
			OnCollisionWithBreakableBrick(events);
		else if (e->obj->GetObjectTypeID() == OBJECT_TYPE_SWITCH && e->ny < 0)
			e->obj->SetState(SWITCH_STATE_INACTIVE);
	} else {
		if (dynamic_cast<CGoomba*>(e->obj))
			OnCollisionWithGoomba(e);
		else if (dynamic_cast<CCoin*>(e->obj))
			OnCollisionWithCoin(e);
		else if (dynamic_cast<CPortal*>(e->obj))
			OnCollisionWithPortal(e);
		else if (dynamic_cast<CMushroom*>(e->obj) || dynamic_cast<CLeaf*>(e->obj))
			OnCollisionWithLevelItems(e);
		else if (dynamic_cast<CVenusFireTrap*>(e->obj) || dynamic_cast<CFireball*>(e->obj) || dynamic_cast<CPtooie*>(e->obj))
			Hit();
		else if (dynamic_cast<CKoopaTroopa*>(e->obj))
			OnCollisionWithKoopaTroopa(e);
		else if (dynamic_cast<CSponsor*>(e->obj))
			dynamic_cast<CSponsor*>(e->obj)->SponseObject();
		else if (e->obj->GetObjectTypeID() == OBJECT_TYPE_BREAKABLE_BRICK)
			OnCollisionWithBreakableBrick(events);
	}
	
}

void CMario::OnCollisionWithKoopaTroopa(LPCOLLISIONEVENT e) {
	CKoopaTroopa* koopaTroopa = dynamic_cast<CKoopaTroopa*>(e->obj);
	int koopaTroopaState = koopaTroopa->GetState();
	switch (koopaTroopaState)
	{
	case KOOPA_TROOPA_STATE_DIE:
		break;
	case KOOPA_TROOPA_STATE_JUMPING:
		if (e->ny < 0) {
			koopaTroopa->SetState(KOOPA_TROOPA_STATE_WALKING);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else
			Hit();
		break;
	case KOOPA_TROOPA_STATE_WALKING:
		if (e->ny < 0) {
			koopaTroopa->SetState(KOOPA_TROOPA_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else
			Hit();
		break;
	case KOOPA_TROOPA_STATE_SHELL:
	case KOOPA_TROOPA_STATE_REVIVE:
		if (usingSkill) {
			shell = koopaTroopa;
			shell->OnHold(true);
			holdingShell = true;
		} else
			koopaTroopa->SetState(KOOPA_TROOPA_STATE_ROLLING);
		break;
	case KOOPA_TROOPA_STATE_ROLLING:
		if (e->ny < 0) {
			koopaTroopa->SetState(KOOPA_TROOPA_STATE_SHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else
			Hit();
		break;
	}
}

void CMario::OnCollisionWithBreakableBrick(vector<LPCOLLISIONEVENT> events) {
	if (events[0]->obj->IsBlocking()) {
		// Find the closest BreakableBrick to hit
		float closestHitX = 9999999;
		CBreakableBrick* brickHit = NULL;
		for (int i = 0; i < events.size(); i++)
		{
			float xDistance = abs(x - events[i]->obj->GetX());
			if (xDistance < closestHitX) {
				brickHit = dynamic_cast<CBreakableBrick*>(events[i]->obj);
				closestHitX = xDistance;
			}
		}

		if (brickHit == NULL) return;
		brickHit->Hit();
	} else {
		for (auto& event : events) {
			if (event->obj->GetState() == BB_STATE_COIN)
				coin++;
			dynamic_cast<CBreakableBrick*>(event->obj)->Hit();
		}	
	}
}


void CMario::OnCollisionWithLevelItems(LPCOLLISIONEVENT e)
{
	LevelUp();
	e->obj->Delete();
}

void CMario::OnCollisionWithQuestionBlock(vector<LPCOLLISIONEVENT> events)
{
	LPCOLLISIONEVENT e = events[0];
	
	// Find the closest QuestionBlock to hit
	float closestHitX = 9999999;
	CQuestionBlock* QuestionBlockHit = NULL;
	for (int i = 0; i < events.size(); i++)
	{
		float xDistance = abs(x - events[i]->obj->GetX());
		if (xDistance < closestHitX && dynamic_cast<CQuestionBlock*>(events[i]->obj)->GetState() == QUESTION_BLOCK_STATE_ALIVE) {
			QuestionBlockHit = dynamic_cast<CQuestionBlock*>(events[i]->obj);
			closestHitX = xDistance;
		}
	}

	if (QuestionBlockHit == NULL) return;
	QuestionBlockHit->Hit(x);

	if (QuestionBlockHit->GetType() == QUESTION_BLOCK_TYPE_COIN)
		coin++;
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->HitByTop();
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			Hit();
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::Hit()
{
	if (untouchable == 0)
	{
		LevelDown();
	}
}

void CMario::LevelUp()
{
	switch (level)
	{
	case MARIO_LEVEL_SMALL:
		SetLevel(MARIO_LEVEL_BIG);
		break;
	case MARIO_LEVEL_BIG:
		SetLevel(MARIO_LEVEL_RACCOON);
		break;
	}
}

void CMario::LevelDown()
{
	switch (level)
	{
	case MARIO_LEVEL_RACCOON:
		SetLevel(MARIO_LEVEL_BIG);
		break;
	case MARIO_LEVEL_BIG:
		SetLevel(MARIO_LEVEL_SMALL);
		break;
	case MARIO_LEVEL_SMALL:
		SetState(MARIO_STATE_DIE);
		return;
	}
	StartUntouchable();
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdRaccoon()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_RACCOON_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_RACCOON)
		aniId = GetAniIdRaccoon();

	animations->Get(aniId)->Render(x, y);

	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL && !holdingShell)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		DebugOut(L"[INFO] Mario died!\n");
		if (holdingShell) {
			shell->OnHold(false);
			holdingShell = false;
		}
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;

	case MARIO_STATE_SKILL:
		usingSkill = true;
		SetState(this->state);
		return;
	case MARIO_STATE_RELEASE_SKILL:
		usingSkill = false;
		SetState(this->state);
		return;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG || level==MARIO_LEVEL_RACCOON)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	switch (l)
	{
	case MARIO_LEVEL_RACCOON:
		break;
	case MARIO_LEVEL_BIG:
		if (level == MARIO_LEVEL_SMALL)
			y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
		break;
	case MARIO_LEVEL_SMALL:
		y += (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
		break;
	}
	level = l;
}

