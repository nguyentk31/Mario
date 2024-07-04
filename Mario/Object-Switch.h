#pragma once
#include "GameObject.h"

#define	SWITCH_SIZE 16

#define SWITCH_STATE_ACTIVE 1
#define SWITCH_STATE_INACTIVE 2

#define SWITCH_ANI_ACTIVE 151000
#define SWITCH_SPRITE_INACTIVE 152000

class CSwitch : public CGameObject {
public:
	CSwitch(float x, float y) : CGameObject(OBJECT_TYPE_SWITCH, x, y) {
		state = SWITCH_STATE_ACTIVE;
	}
	void Render();
	int IsBlocking() { return state == SWITCH_STATE_ACTIVE; }
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};