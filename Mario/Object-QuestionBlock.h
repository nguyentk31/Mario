#pragma once
#include "GameObject.h"

#define QUESTION_BLOCK_WIDTH 16
#define QUESTION_BLOCK_HEIGHT 16

#define ID_ANI_QUESTION_BLOCK_ALIVE 91000
#define ID_ANI_QUESTION_BLOCK_DEAD 92000

#define QUESTION_BLOCK_STATE_BOUNCING 2
#define QUESTION_BLOCK_STATE_ALIVE 1
#define QUESTION_BLOCK_STATE_DEAD 0

#define QUESTION_BLOCK_TYPE_COIN 1
#define QUESTION_BLOCK_TYPE_LIFE 2

#define BOUCING_SPEED 0.1f
#define BOUCING_DISTANCE 10 // Pixels

class CQuestionBlock : public CGameObject
{
protected:
	float originalY;
	int type;
	float hitX;
	void generateCoin();
	void generateLife(int directionX);
public:
	CQuestionBlock(float x, float y, int type) : CGameObject(x, y) {
		this->state = QUESTION_BLOCK_STATE_ALIVE;
		this->originalY = y;
		this->type = type;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsCollidable();
	void OnNoCollision(DWORD dt);
	void SetState(int state);
	int GetState() { return this->state; }
	int GetType() { return this->type; }
	void SetHitX(float x) { this->hitX = x; }
};

typedef CQuestionBlock* LPQUESTIONBLOCK;