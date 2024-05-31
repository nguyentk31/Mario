#pragma once
#include "GameObject.h"

class CBackgrounds : public CGameObject
{
protected:
	int sprintId;
public:
	CBackgrounds(float x, float y, int sprintid) :CGameObject(OBJECT_TYPE_BACKGROUNDS, x, y)
	{
		this->sprintId = sprintid;
	}

	void Render() {  CSprites::GetInstance()->Get(this->sprintId)->Draw(this->x, this->y); };
	void GetBoundingBox(float& l, float& t, float& r, float& b) { l = t = r = b = 0; };
	int IsBackground() { return 1; }
};