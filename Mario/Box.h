#pragma once

#include "GameObject.h"

#define SPRITE_BOX_ID 80000
#define SPRITE_BOX_SHADOW_ID 5000

class CBox : public CGameObject
{
protected:
	int lengthX, lengthY;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteColorId;
	bool rightShadow, bottomShadow;

public:
	CBox(float x, float y,
		float cell_width, float cell_height, int lengthx, int lengthy,
		int spriteColorId, bool rightShadow, bool bottomShadow) :CGameObject(x, y)
	{
		this->lengthX = lengthx;
		this->lengthY = lengthy;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteColorId = spriteColorId;
		this->rightShadow = rightShadow;
		this->bottomShadow = bottomShadow;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

typedef CBox* LPBox;
