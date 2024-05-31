#include "Object-QuestionBlock.h"
#include "Object-Coin.h"
#include "Object-Mushroom.h"
#include "PlayScene.h"
#include "debug.h"

void CQuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Add the item to coObjects to check collision
	if (vy == -BOUCING_SPEED && item != NULL) {
		coObjects->push_back(item);
	}

	if (vy < 0 || y < originalY) {
		vy += ay * dt;
		CCollision::GetInstance()->Process(this, dt, coObjects);
	} else
		SetState(QUESTION_BLOCK_STATE_DEAD);
}

void CQuestionBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (this->state == QUESTION_BLOCK_STATE_ALIVE)
		animations->Get(ID_ANI_QUESTION_BLOCK_ALIVE)->Render(x, y);
	else
		animations->Get(ID_ANI_QUESTION_BLOCK_DEAD)->Render(x, y);
}


void CQuestionBlock::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void CQuestionBlock::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (dynamic_cast<CMushroom*>(e->obj)) {
		if (e->ny > 0) {
			e->obj->SetState(MUSHROOM_STATE_BOUNCING);
		}
	}
	if (dynamic_cast<CCoin*>(e->obj)) {
		if (e->ny > 0) {
			e->obj->SetState(COIN_STATE_BOUNCING);
		}
	}
}

int CQuestionBlock::IsCollidable()
{
	return (this->state == QUESTION_BLOCK_STATE_BOUNCING);
}

// Generate a coin or leaf or mushroom
void CQuestionBlock::generateLvItem()
{
	int directionX = hitX>x ? -1 : 1;
	item = new CMushroom(x, y, directionX);
	CPlayScene* current_scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	current_scene->AddObject(item);
}

void CQuestionBlock::generateCoin()
{
	item = new CCoin(x, y-(QUESTION_BLOCK_SIZE+COIN_SIZE+1)/2);
	CPlayScene* current_scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	current_scene->AddObject(item);
}

void CQuestionBlock::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case QUESTION_BLOCK_STATE_BOUNCING:
			vy = -BOUCING_SPEED;
			if (QBType == QUESTION_BLOCK_TYPE_COIN)
				generateCoin();
			break;
		case QUESTION_BLOCK_STATE_DEAD: 
			vy = 0;
			y = originalY;
			item = NULL;
			if (QBType == QUESTION_BLOCK_TYPE_LEVEL_ITEM)
				generateLvItem();
			CPlayScene* current_scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
			current_scene->QBLockStateChanged();
			break;
	}
}

void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESTION_BLOCK_SIZE / 2;
	t = y - QUESTION_BLOCK_SIZE / 2;
	r = l + QUESTION_BLOCK_SIZE;
	b = t + QUESTION_BLOCK_SIZE;
}