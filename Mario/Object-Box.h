#pragma once
#include "GameObject.h"

#define BOX_CELL_WIDTH 16.0f
#define BOX_CELL_HEIGHT 16.0f

class CBox : public CGameObject
{
protected:
	int lengthX, lengthY;				// Unit: cell 
	int spriteColorId;
	bool rightShadow, bottomShadow;

public:
	CBox(float x, float y,
		int lengthx, int lengthy,
		int spriteColorId,
		bool rightShadow, bool bottomShadow) :CGameObject(OBJECT_TYPE_BOX, x, y)
	{
		this->lengthX = lengthx;
		this->lengthY = lengthy;
		this->spriteColorId = spriteColorId;
		this->rightShadow = rightShadow;
		this->bottomShadow = bottomShadow;
	}

	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsDirectionColliable(float nx, float ny) { return nx == 0 && ny == -1; }
};
