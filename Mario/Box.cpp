#include "Box.h"

void CBox::Render()
{
	CSprites* s = CSprites::GetInstance();
	int lengthx = this->lengthX;
	int lengthy = this->lengthY;
	float yy = y;

	s->Get(SPRITE_BOX_ID + this->spriteColorId+100)->Draw(x, yy);
	s->Get(SPRITE_BOX_ID + this->spriteColorId+300)->Draw(x+(1+lengthx)*this->cellWidth, yy);
	float xx = x + this->cellWidth;
	for (int i = 0; i < lengthx; i++) {
		s->Get(SPRITE_BOX_ID + this->spriteColorId+200)->Draw(xx, yy);
		xx += this->cellWidth;
	}
	if (this->rightShadow) {
		s->Get(SPRITE_BOX_ID + SPRITE_BOX_SHADOW_ID + 100)->Draw(x+(1.75f+lengthx)*this->cellWidth, yy+0.25f*this->cellHeight);
	}
	yy += this->cellHeight;

	for (int i = 0; i < lengthy; i++) {
		s->Get(SPRITE_BOX_ID + this->spriteColorId+400)->Draw(x, yy);
		s->Get(SPRITE_BOX_ID + this->spriteColorId+600)->Draw(x+(1+lengthx)*this->cellWidth, yy);
		if (this->rightShadow) {
			s->Get(SPRITE_BOX_ID + SPRITE_BOX_SHADOW_ID + 400)->Draw(x+(1.75f+lengthx)*this->cellWidth, yy-0.25f*this->cellHeight);
			s->Get(SPRITE_BOX_ID + SPRITE_BOX_SHADOW_ID + 400)->Draw(x+(1.75f+lengthx)*this->cellWidth, yy+0.25f*this->cellHeight);
		}
		xx = x + this->cellWidth;
		for (int j = 0; j < lengthx; j++) {
			s->Get(SPRITE_BOX_ID + this->spriteColorId+500)->Draw(xx, yy);
			xx += this->cellWidth;
		}
		yy += this->cellHeight;
	}

	s->Get(SPRITE_BOX_ID + this->spriteColorId+700)->Draw(x, yy);
	s->Get(SPRITE_BOX_ID + this->spriteColorId+900)->Draw(x+(1+lengthx)*this->cellWidth, yy);
	xx = x + this->cellWidth;
	for (int i = 0; i < lengthx; i++) {
		s->Get(SPRITE_BOX_ID + this->spriteColorId+800)->Draw(xx, yy);
		xx += this->cellWidth;
	}
	if (this->rightShadow) {
		s->Get(SPRITE_BOX_ID + SPRITE_BOX_SHADOW_ID + 400)->Draw(x+(1.75f+lengthx)*this->cellWidth, yy-0.25f*this->cellHeight);
		s->Get(SPRITE_BOX_ID + SPRITE_BOX_SHADOW_ID + 400)->Draw(x+(1.75f+lengthx)*this->cellWidth, yy+0.25f*this->cellHeight);
	}
	yy += this->cellHeight;

	if (this->bottomShadow) {
		yy -= 0.25f*this->cellHeight;
		s->Get(SPRITE_BOX_ID + SPRITE_BOX_SHADOW_ID + 200)->Draw(x+0.25f*this->cellWidth, yy);
		xx = x + this->cellWidth; 
		for (int i = 0; i < lengthx; i++) {
			s->Get(SPRITE_BOX_ID + SPRITE_BOX_SHADOW_ID + 400)->Draw(xx-0.25f*this->cellWidth, yy);
			s->Get(SPRITE_BOX_ID + SPRITE_BOX_SHADOW_ID + 400)->Draw(xx+0.25f*this->cellWidth, yy);
			xx += this->cellWidth;
		}
		s->Get(SPRITE_BOX_ID + SPRITE_BOX_SHADOW_ID + 400)->Draw(xx-0.25f*this->cellWidth, yy);
		s->Get(SPRITE_BOX_ID + SPRITE_BOX_SHADOW_ID + 400)->Draw(xx+0.25f*this->cellWidth, yy);
		s->Get(SPRITE_BOX_ID + SPRITE_BOX_SHADOW_ID + 300)->Draw(xx+0.75f*this->cellWidth, yy);
	}
}

int CBox::IsDirectionColliable(float nx, float ny)
{
	if (nx == 0 && ny == -1) return 1;
	else return 0;
}

void CBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = x - cellWidth_div_2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth * (this->lengthX+2);
	b = t + this->cellHeight * (this->lengthY+2);
}