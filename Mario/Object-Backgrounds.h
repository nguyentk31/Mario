#pragma once
#include "GameObject.h"

class CBackgrounds : public CGameObject
{
protected:
	int sprintId;
	int width, height; // Block
public:
	CBackgrounds(float x, float y, int sprintid, int width, int height) :CGameObject(OBJECT_TYPE_BACKGROUNDS, x, y)
	{
		this->sprintId = sprintid;
		this->width = width;
		this->height = height;
	}

	void Render() {
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				CSprites::GetInstance()->Get(this->sprintId)->Draw(this->x + i * 16, this->y + j * 16);
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) { l = t = r = b = 0; };
	int IsBackground() { return 1; }
};