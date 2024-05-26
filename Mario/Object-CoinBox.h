#pragma once
#include "GameObject.h"
#include "AssetIDs.h"

#define COIN_BOX_WIDTH 16
#define COIN_BOX_HEIGHT 16

#define ID_ANI_COIN_BOX_ALIVE 0

#define COIN_BOX_STATE_ALIVE 1
#define COIN_BOX_STATE_DEAD 0

class CCoinBox : public CGameObject
{
public:
	CCoinBox(float x, float y) : CGameObject(x, y) {}
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

typedef CCoinBox* LPCOINBOX;