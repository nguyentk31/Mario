#include "Object-Sponsor.h"
#include "Mario.h"
#include "Game.h"
#include "PlayScene.h"

void CSponsor::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SPONSOR_WIDTH / 2;
	t = 0;
	r = l + SPONSOR_WIDTH;
	b = 1000;
}

void CSponsor::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {}

void CSponsor::SponseObject() {
	// CGame *game = CGame::GetInstance();
	// CMario *mario = game->GetPlayer();
	// float mario_x, mario_y;
	// mario->GetPosition(mario_x, mario_y);
	// float display_min_x = mario_x - game->GetScreenWidth() / 2;
	// float display_max_x = mario_x + game->GetScreenWidth() / 2;
	for (size_t i = 0; i < objects_state.size(); i++) {
    		if (objects_state[i] != OBJECT_STATE_CREATED)
			CreateObject(objects_type[i], objects_position[i][0], objects_position[i][1]);
			objects_state[i] = OBJECT_STATE_CREATED;
		// if (objects_position[i][0] < display_min_x - RANGE_IN_DISPLAY || objects_position[i][0] > display_max_x + RANGE_IN_DISPLAY) {
		// 	CreateObject(objects_type[i], objects_position[i][0], objects_position[i][1]);
		// 	objects_state[i] = OBJECTS_STATE_OUT_DISPLAY;
		// }
	}

}

void CSponsor::CreateObject(int type, float x, float y) {
	LPGAMEOBJECT obj = NULL;
	switch (type)
	{
	case OBJECT_TYPE_GOOMBA: {
		obj = new CGoomba(x,y); break;
		break;
	}
	case OBJECT_TYPE_KOOPA_TROOPA: {
		obj = new CKoopaTroopa(x, y);
		break;
	}
	default:
		DebugOut(L"[ERROR] SPONSOR: Invalid object type: %d\n", type);
		return;
	}
	// General object setup
	obj->SetPosition(x, y);

	// Add object to the scene
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
}
