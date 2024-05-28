#include "Object-QuestionBlock.h"
#include "Object-Coin.h"
#include "Object-Mushroom.h"
#include "PlayScene.h"
#include "AssetIDs.h"

void CQuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if ( this->state != QUESTION_BLOCK_STATE_BOUNCING )
		return;

	if (this->y < this->originalY - BOUCING_DISTANCE) 
	{
		this->vy = BOUCING_SPEED;
	}
	else if (this->y > this->originalY)
	{
		this->y = this->originalY;
		SetState(QUESTION_BLOCK_STATE_DEAD);
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CQuestionBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (this->state == QUESTION_BLOCK_STATE_ALIVE) {
		animations->Get(ID_ANI_QUESTION_BLOCK_ALIVE)->Render(x, y);
	}
	else {
		animations->Get(ID_ANI_QUESTION_BLOCK_DEAD)->Render(x, y);
	}
}

void CQuestionBlock::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

int CQuestionBlock::IsCollidable()
{
	return (this->state == QUESTION_BLOCK_STATE_BOUNCING);
}

// Generate a coin or leaf or mushroom
void CQuestionBlock::generateLife(int directionX)
{
	CMushroom* mushroom = new CMushroom(this->x, this->y, directionX, QUESTION_BLOCK_HEIGHT);
	CPlayScene* current_scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	current_scene->AddObject(OBJECT_TYPE_MUSHROOM ,mushroom);
}

void CQuestionBlock::generateCoin()
{
	CCoin* coin = new CCoin(this->x-QUESTION_BLOCK_WIDTH/2+COIN_SIZE/2, this->y-QUESTION_BLOCK_HEIGHT/2-COIN_SIZE/2, COIN_STATE_BOUNDING);
	CPlayScene* current_scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	current_scene->AddObject(OBJECT_TYPE_COIN, coin);
}

void CQuestionBlock::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case QUESTION_BLOCK_STATE_BOUNCING:
			this->vy = -BOUCING_SPEED;
			if (this->type == QUESTION_BLOCK_TYPE_COIN)
				generateCoin();
			break;
		case QUESTION_BLOCK_STATE_DEAD: 
			this->vy = 0;
			if (this->type == QUESTION_BLOCK_TYPE_LIFE) {
				int directionX = (hitX>x ? -1 : 1);
				generateLife(directionX);
			}
			break;
	}
}

void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESTION_BLOCK_WIDTH / 2;
	t = y - QUESTION_BLOCK_HEIGHT / 2;
	r = l + QUESTION_BLOCK_WIDTH;
	b = t + QUESTION_BLOCK_HEIGHT;
}