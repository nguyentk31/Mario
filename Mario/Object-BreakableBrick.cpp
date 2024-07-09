#include "Object-BreakableBrick.h"
#include "Object-Switch.h"
#include "PlayScene.h"

void CBreakableBrick::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (state == BB_STATE_BOUCING) {
		y += vy * dt;
		vy += ay * dt;
		if (vy > 0 && y >= originalY)
			SetState(BB_STATE_UNBROKEN);
	} else if (state == BB_STATE_BROKING) {
		brokingX += BB_BROKING_SPEED * dt;
		brokingY += BB_BROKING_SPEED * dt;
		if (GetTickCount64() - brokingStart > BB_TIMEOUT_BROKING)
			SetState(BB_STATE_BROKEN);
	} else if (state == BB_STATE_COIN) {
		if (GetTickCount64() - coinStart > BB_TIMEOUT_COIN)
			SetState(BB_STATE_NORMAL);
	}
	
}

void CBreakableBrick::Render()
{
	switch (state)
	{
	case BB_STATE_NORMAL:
		CAnimations::GetInstance()->Get(BB_ANI_NORMAL)->Render(x, y);
		break;
	case BB_STATE_BOUCING:
	case BB_STATE_UNBROKEN:
		CSprites::GetInstance()->Get(BB_SPRITE_UNBROKEN)->Draw(x, y);
		break;
	case BB_STATE_BROKING:
		CSprites::GetInstance()->Get(BB_SPRITE_BROKEN_PIECE)->Draw(x-brokingX, y-brokingY);
		CSprites::GetInstance()->Get(BB_SPRITE_BROKEN_PIECE)->Draw(x-brokingX, y+brokingY);
		CSprites::GetInstance()->Get(BB_SPRITE_BROKEN_PIECE)->Draw(x+brokingX, y+brokingY);
		CSprites::GetInstance()->Get(BB_SPRITE_BROKEN_PIECE)->Draw(x+brokingX, y-brokingY);
		break;
	case BB_STATE_COIN:
		CSprites::GetInstance()->Get(BB_SPRITE_COIN)->Draw(x, y);
		break;
	}
}

int CBreakableBrick::IsBlocking()
{
	return (this->state == BB_STATE_NORMAL || this->state == BB_STATE_UNBROKEN || this->state == BB_STATE_BOUCING);
}

int CBreakableBrick::IsCollidable()
{
	return (this->state == BB_STATE_BOUCING || this->state == BB_STATE_BROKING || this->state == BB_STATE_COIN);
}

void CBreakableBrick::Hit(float x)
{
	hitX = x;
	switch (state)
	{
	case BB_STATE_NORMAL:
		if (BBType == BB_TYPE_COIN)
			SetState(BB_STATE_BROKING);
		else
			SetState(BB_STATE_BOUCING);
		break;
	case BB_STATE_COIN:
		isDeleted = true;
		break;
	}
}

void CBreakableBrick::SetState(int state)
{
	switch (state)
	{
		case BB_STATE_NORMAL:
			vy = 0;
			y = originalY;
			break;
		case BB_STATE_BOUCING:
			vy = -BB_BOUCING_SPEED;
			break;
		case BB_STATE_UNBROKEN: 
			vy = 0;
			y = originalY;
			if (BBType == BB_TYPE_SWITCH)
				((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(new CSwitch(x, y-SWITCH_SIZE));
			else {
				int directionX = hitX>x ? -1 : 1;
				((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(new CMushroom(x, y, directionX));
			}
			break;
		case BB_STATE_BROKING:
			brokingX = BB_SIZE;
			brokingY = BB_SIZE;
			brokingStart = GetTickCount64();
			break;
		case BB_STATE_BROKEN:
			isDeleted = true;
			break;
		case BB_STATE_COIN:
			coinStart = GetTickCount64();
	}
	CGameObject::SetState(state);
}

void CBreakableBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BB_SIZE / 2;
	t = y - BB_SIZE / 2;
	r = l + BB_SIZE;
	b = t + BB_SIZE;
}