#include "Object-Box.h"

void CBox::Render()
{
	if (lengthX <= 0 || lengthY <= 0) return;
	CSprites* s = CSprites::GetInstance();
	float xx, yy;
	xx = x;
	yy = y;
	for (int i = 0; i < lengthY; i++) {
		for (int j = 0; j < lengthX; j++) {
			int y = (i == 0) ? 0 : (i == lengthY - 1) ? 2 : 1;
			int x = (j == 0) ? 0 : (j == lengthX - 1) ? 2 : 1;
			// DebugOut(L"spriteColorId: %d\n", spriteColorId + x + y * 100);
			s->Get(spriteColorId + ((x+1)+(3*y)) * 100)->Draw(xx, yy);
			xx += BOX_CELL_WIDTH;
		}
		// Draw right shadow
		if (rightShadow) {
			float sx = xx - 0.25f * BOX_CELL_WIDTH;
			float sty = yy - 0.25f * BOX_CELL_HEIGHT;
			float sby = yy + 0.25f * BOX_CELL_HEIGHT;
			if (i == 0)
				s->Get(ID_SPRITE_BOX_SHADOW + 100)->Draw(sx, sby);
			else {
				s->Get(ID_SPRITE_BOX_SHADOW + 400)->Draw(sx, sty);
				s->Get(ID_SPRITE_BOX_SHADOW + 400)->Draw(sx, sby);
			}
		}
		xx = x;
		yy += BOX_CELL_HEIGHT;
	}

	// Draw bottom shadow
	if (bottomShadow) {
		yy -= 0.25f * BOX_CELL_HEIGHT;
		xx += 0.25f * BOX_CELL_WIDTH;
		s->Get(ID_SPRITE_BOX_SHADOW + 200)->Draw(xx, yy);
		xx += BOX_CELL_WIDTH/2;
		for (int i = 0; i < lengthX*2-2; i++) {
			s->Get(ID_SPRITE_BOX_SHADOW + 400)->Draw(xx, yy);
			xx += BOX_CELL_WIDTH/2;
		}
		s->Get(ID_SPRITE_BOX_SHADOW + 300)->Draw(xx, yy);
	}
}

void CBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BOX_CELL_WIDTH / 2;
	t = y - BOX_CELL_HEIGHT / 2;
	r = l + BOX_CELL_WIDTH * lengthX;
	b = t + BOX_CELL_HEIGHT * lengthY;
}