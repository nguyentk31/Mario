#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "Portal.h"
#include "Object-Coin.h"
#include "Object-BreakableBrick.h"
#include "Object-Brick.h"
#include "Object-Fireball.h"
#include "Object-Goomba.h"
#include "Object-KoopaTroopa.h"
#include "Object-Leaf.h"
#include "Object-Mushroom.h"
#include "Object-Ptooie.h"
#include "Object-QuestionBlock.h"
#include "Object-VenusFireTrap.h"
#include "Object-Sponsor.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.3f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_KICK			700

#define MARIO_STATE_SKILL			800
#define MARIO_STATE_RELEASE_SKILL	801

#define MARIO_STATE_HOLD_SHELL		900
#define MARIO_STATE_RELEASE_SHELL	901

#pragma region ANIMATION_ID

// BIG MARIO
#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_KICK_RIGHT 1100
#define ID_ANI_MARIO_KICK_LEFT 1101

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_KICK_RIGHT 1700
#define ID_ANI_MARIO_SMALL_KICK_LEFT 1701

// RACCOON MARIO
#define ID_ANI_MARIO_RACCOON_IDLE_RIGHT 2100
#define ID_ANI_MARIO_RACCOON_IDLE_LEFT 2101

#define ID_ANI_MARIO_RACCOON_WALKING_RIGHT 2200
#define ID_ANI_MARIO_RACCOON_WALKING_LEFT 2201

#define ID_ANI_MARIO_RACCOON_RUNNING_RIGHT 2300
#define ID_ANI_MARIO_RACCOON_RUNNING_LEFT 2301

#define ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT 2400
#define ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT 2401

#define ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT 2500
#define ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT 2501

#define ID_ANI_MARIO_RACCOON_SIT_RIGHT 2600
#define ID_ANI_MARIO_RACCOON_SIT_LEFT 2601

#define ID_ANI_MARIO_RACCOON_BRACE_RIGHT 2700
#define ID_ANI_MARIO_RACCOON_BRACE_LEFT 2701

#define ID_ANI_MARIO_RACCOON_KICK_RIGHT 2800
#define ID_ANI_MARIO_RACCOON_KICK_LEFT 2801

#define ID_ANI_MARIO_RACCOON_FLY_RIGHT 2900
#define ID_ANI_MARIO_RACCOON_FLY_LEFT 2901

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACCOON	3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_KICKING_TIME 500

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	int coin;
	bool usingSkill;
	bool holdingShell;
	LPKOOPATROOPA shell;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBlock(vector<LPCOLLISIONEVENT> events);
	void OnCollisionWithLevelItems(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopaTroopa(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRaccoon();
	void LevelDown();
	void HoldShell();

public:
	CMario(float x, float y) : CGameObject(OBJECT_TYPE_MARIO, x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
		usingSkill = false;
		holdingShell = false;
		shell = NULL;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void Hit();
	void LevelUp();
	int GetLevel() { return level; }

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(vector<LPCOLLISIONEVENT> events);
	void OnOverlapseWith(vector<LPCOLLISIONEVENT> events) {};

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};