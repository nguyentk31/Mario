#include "Object-Brick.h"
#include "debug.h"

void CBrick::Render()
{
	if (lengthX <= 0 || lengthY <= 0) return;
	float xx = x;
	float yy = y;
	CSprites* s = CSprites::GetInstance();
	DebugOut(L"Brick: %f %f %d %d\n", x, y, lengthX, lengthY);
	
	for (int i = 0; i < lengthY; i++) {
		for (int j = 0; j < lengthX; j++) {
			int x, y;
			x = (i == 0) ? 0 : (i == lengthY - 1) ? 2 : 1;
			y = (j == 0) ? 0 : (j == lengthX - 1) ? 2 : 1;
			s->Get(this->spriteIdMap[x][y])->Draw(xx, yy);
			xx += this->cellWidth;
		}
		xx = x;
		yy += this->cellHeight;
	}
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - this->cellWidth / 2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth * this->lengthX;
	b = t + this->cellHeight * this->lengthY;
}