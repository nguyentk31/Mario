#pragma once

#include "GameObject.h"

#define ITEM_WIDTH 16
#define ITEM_HEIGHT 16

class CBackgrounds : public CGameObject
{
protected:
	int sprintId;

public:
	CBackgrounds(float x, float y, int sprintid) :CGameObject(x, y)
	{
		this->sprintId = sprintid;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};

typedef CBackgrounds* LPBACKGROUND;