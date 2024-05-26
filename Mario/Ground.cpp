#include "Ground.h"

void CGround::Render()
{
	if (this->lengthX <= 0 || this->lengthY <= 0) return;
	float xx = x;
	float yy = y;
	CSprites* s = CSprites::GetInstance();

	int lengthx = this->lengthX;
	int lengthy = this->lengthY;
	for (int i = 0; i < lengthy; i++) {
		for (int j = 0; j < lengthx; j++) {
			int x, y;
			x = (i == 0) ? 0 : 1;
			y = (j == 0) ? 0 : (j == lengthx - 1) ? 2 : 1;
			s->Get(this->spriteIdMap[x][y])->Draw(xx, yy);
			xx += this->cellWidth;
		}
		xx = x;
		yy += this->cellHeight;
	}
}

void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = x - cellWidth_div_2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth * this->lengthX;
	b = t + this->cellHeight * this->lengthY;
}