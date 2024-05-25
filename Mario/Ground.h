#pragma once

#include "GameObject.h"

class CGround : public CGameObject
{
protected:
	int lengthX, lengthY;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdMap[2][3];

public:
	CGround(float x, float y,
		float cell_width, float cell_height, int lengthx, int lengthy,
		int spriteId_map[2][3]) :CGameObject(x, y)
	{
		this->lengthX = lengthx;
		this->lengthY = lengthy;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 3; j++)
				this->spriteIdMap[i][j] = spriteId_map[i][j];
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

typedef CGround* LPGROUND;