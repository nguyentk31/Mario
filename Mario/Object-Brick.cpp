#include "Object-Brick.h"

void CBrick::Render()
{
	if (lengthX <= 0 || lengthY <= 0) return;
	float xx = x;
	float yy = y;
	CSprites* s = CSprites::GetInstance();
	
	for (int i = 0; i < lengthY; i++) {
		for (int j = 0; j < lengthX; j++) {
			int x, y;
			x = (i == 0) ? 0 : (i == lengthY - 1) ? 2 : 1;
			y = (j == 0) ? 0 : (j == lengthX - 1) ? 2 : 1;
			s->Get(spriteIdMap[x][y])->Draw(xx, yy);
			xx += cellWidth;
		}
		xx = x;
		yy += cellHeight;
	}
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - cellWidth / 2 + 2;
	t = y - cellHeight / 2;
	r = l + cellWidth * lengthX - 2;
	b = t + cellHeight * lengthY;
}