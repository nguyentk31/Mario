#include "Object-QuestionBlock.h"
#include "Object-Coin.h"
#include "Object-Mushroom.h"
#include "Object-Brick.h"
#include "PlayScene.h"
#include "debug.h"

void CQuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Add the item to coObjects to check collision
	if (vy == -BOUCING_SPEED && item != NULL) {
		coObjects->push_back(item);
	}

	if (vy < 0 || y < originalY )
		CCollision::GetInstance()->Process(this, dt, coObjects);
	else
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
	vy += ay * dt;
}

void CQuestionBlock::OnCollisionWith(vector<LPCOLLISIONEVENT> events) {
	if (events.size() == 0)
		DebugOut(L"QuestionBlock has two collision events\n");
	LPCOLLISIONEVENT e = events[0];
	if (dynamic_cast<CMushroom*>(e->obj) && e->ny > 0)
		e->obj->SetState(MUSHROOM_STATE_BOUNCING);
	else if (dynamic_cast<CCoin*>(e->obj))
		e->obj->SetState(COIN_STATE_BOUNCING);
	else if (dynamic_cast<CBrick*>(e->obj))
		SetState(QUESTION_BLOCK_STATE_DEAD);
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
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(item);
}

void CQuestionBlock::generateCoin()
{
	item = new CCoin(x, y-(QUESTION_BLOCK_SIZE+COIN_SIZE+1)/2);
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(item);
}

void CQuestionBlock::Hit(float x)
{
	hitX = x;
	SetState(QUESTION_BLOCK_STATE_BOUNCING);
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
			if (QBType == QUESTION_BLOCK_TYPE_LEVEL_ITEM)
				generateLvItem();
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