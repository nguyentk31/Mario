#pragma once
#include "GameObject.h"

#define QUESTION_BLOCK_SIZE 16

#define QUESTION_BLOCK_STATE_BOUNCING 2
#define QUESTION_BLOCK_STATE_ALIVE 1
#define QUESTION_BLOCK_STATE_DEAD 0

#define QUESTION_BLOCK_TYPE_COIN 1
#define QUESTION_BLOCK_TYPE_LEVEL_ITEM 2

#define BOUCING_SPEED 0.2f
#define QUESTION_BLOCK_GRAVITY 0.002f

class CQuestionBlock : public CGameObject
{
protected:
	float originalY;
	float ay;
	int QBType;
	float hitX;
	LPGAMEOBJECT item = NULL;
	void generateCoin();
	void generateLvItem();
public:
	CQuestionBlock(float x, float y, int type) : CGameObject(OBJECT_TYPE_QUESTION_BLOCK, x, y) {
		ay = QUESTION_BLOCK_GRAVITY;
		vx = vy = 0;
		state = QUESTION_BLOCK_STATE_ALIVE;
		originalY = y;
		QBType = type;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsCollidable();
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(vector<LPCOLLISIONEVENT> events);
	void SetState(int state);
	int GetType() { return this->QBType; }
	void Hit(float x);
};