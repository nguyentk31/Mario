#pragma once
#include "GameObject.h"

#define	LEAF_WIDTH 16
#define LEAF_HEIGHT 14

#define LEAF_SPEED_SPONSE 0.5f
#define LEAF_GRAVITY 0.002f
#define LEAF_FALL_X_SPEED 0.05f
#define LEAF_FALL_Y_SPEED 0.05f
#define LEAF_BRACKING_X_SPEED 0.00005f
#define LEAF_BRACKING_Y_SPEED 0.0002f

#define LEAF_STATE_SPONSE 1
#define LEAF_STATE_FALL 2

class CLeaf : public CGameObject {
protected:
	float ay, ax;
public:
	CLeaf(float x, float y) : CGameObject(OBJECT_TYPE_LEAF, x, y) {
		SetState(LEAF_STATE_SPONSE);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};