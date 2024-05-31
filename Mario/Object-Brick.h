#pragma once
#include "GameObject.h"

class CBrick : public CGameObject
{
protected:
	int lengthX, lengthY;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdMap[3][3];

public:
	CBrick(float x, float y,
		float cell_width, float cell_height, int lengthx, int lengthy,
		int spriteId_map[3][3]) :CGameObject(OBJECT_TYPE_BRICK, x, y)
	{
		this->lengthX = lengthx;
		this->lengthY = lengthy;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				this->spriteIdMap[i][j] = spriteId_map[i][j];
	}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};