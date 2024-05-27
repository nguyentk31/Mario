#include "Object-QuestionBlock.h"

void CQuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if ( this->state != COIN_BOX_STATE_BOUNCING )
		return;

	if (this->y < this->originalY - BOUCING_DISTANCE) 
	{
		this->vy = BOUCING_SPEED;
	}
	else if (this->y > this->originalY)
	{
		this->y = this->originalY;
		SetState(COIN_BOX_STATE_DEAD);
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CQuestionBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (this->state == COIN_BOX_STATE_ALIVE) {
		animations->Get(ID_ANI_COIN_BOX_ALIVE)->Render(x, y);
	}
	else {
		animations->Get(ID_ANI_COIN_BOX_DEAD)->Render(x, y);
	}
}

void CQuestionBlock::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

int CQuestionBlock::IsCollidable()
{
	return (this->state == COIN_BOX_STATE_BOUNCING);
}

void CQuestionBlock::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case COIN_BOX_STATE_BOUNCING:
			this->vy = -BOUCING_SPEED;
			break;
		case COIN_BOX_STATE_DEAD: 
			this->vy = 0;
			break;
	}
}

void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BOX_WIDTH / 2;
	t = y - COIN_BOX_HEIGHT / 2;
	r = l + COIN_BOX_WIDTH;
	b = t + COIN_BOX_HEIGHT;
}