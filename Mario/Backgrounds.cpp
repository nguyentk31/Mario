#include "Backgrounds.h"

#include "Sprites.h"

void CBackgrounds::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(this->sprintId)->Draw(this->x, this->y);
}

void CBackgrounds::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - ITEM_WIDTH / 2;
	t = y - ITEM_HEIGHT / 2;
	r = l + ITEM_WIDTH;
	b = t + ITEM_HEIGHT;
}