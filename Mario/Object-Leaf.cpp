#include "Object-Leaf.h"

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	float cam_x, cam_y;
	CGame *game = CGame::GetInstance();
	game->GetCamPos(cam_x, cam_y);
	float display_min_x = cam_x - 32;
	float display_min_y = cam_y - 32;
	float display_max_x = cam_x + game->GetBackBufferWidth() + 32;
	float display_max_y = cam_y + game->GetBackBufferHeight() + 32;
	if (x < display_min_x || x > display_max_x || y < display_min_y || y > display_max_y) {
		isDeleted = true;
		return;
	}

	vy += ay * dt;
	vx += ax * dt;

	if (state == LEAF_STATE_SPONSE && vy > 0)
	{
		SetState(LEAF_STATE_FALL);
	} else if (state == LEAF_STATE_FALL)
	{
		if (vx/ax > 0 && vy/ay > 0)
		{	
			ax = -ax;
			vx = (ax > 0) ? -LEAF_FALL_X_SPEED : LEAF_FALL_X_SPEED;
			vy = LEAF_FALL_Y_SPEED;
		} else if (vx/ax > 0) {
			vx = 0;
		} else if (vy/ay > 0) {
			vy = 0;
		}
	}

	x += vx * dt;
	y += vy * dt;
}

void CLeaf::SetState(int state)
{
	switch (state)
	{
	case LEAF_STATE_SPONSE:
		vy = -LEAF_SPEED_SPONSE;
		vx = 0;
		ax = 0;
		ay = LEAF_GRAVITY;
		break;
	case LEAF_STATE_FALL:
		vx = LEAF_FALL_X_SPEED;
		vy = LEAF_FALL_Y_SPEED;
		ay = -LEAF_BRACKING_Y_SPEED;
		ax = -LEAF_BRACKING_X_SPEED;
		break;
	}
	CGameObject::SetState(state);
}

void CLeaf::Render()
{
	CSprites::GetInstance()->Get(ID_SPRITE_LEAF)->Draw(x, y);
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_WIDTH / 2;
	t = y - LEAF_HEIGHT / 2;
	r = l + LEAF_WIDTH;
	b = t + LEAF_HEIGHT;
}