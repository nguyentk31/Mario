#include "Object-Fireball.h"
#include "Mario.h"
#include "PlayScene.h"


void CFireball::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - FIREBALL_SIZE / 2;
	t = y - FIREBALL_SIZE / 2;
	r = l + FIREBALL_SIZE;
	b = t + FIREBALL_SIZE;
}

void CFireball::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Check if the fireball is out of the screen, then delete it
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

	x += vx * dt;
	y += vy * dt;
}
