#include "Object-CoinBox.h"

void CCoinBox::Render()
{
	CSprites* s = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();
	state = COIN_BOX_STATE_ALIVE;
	// state = COIN_BOX_STATE_DEAD;
	if (state == COIN_BOX_STATE_ALIVE) {
		animations->Get(ID_SPRITE_COIN_BOX_ALIVE + ID_ANI_COIN_BOX_ALIVE)->Render(x, y);
	}
	else {
		s->Get(ID_SPRITE_COIN_BOX_DEAD)->Draw(x, y);
	}
}

void CCoinBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BOX_WIDTH / 2;
	t = y - COIN_BOX_HEIGHT / 2;
	r = l + COIN_BOX_WIDTH;
	b = t + COIN_BOX_HEIGHT;
}