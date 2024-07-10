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
	for (size_t i = 0; i < objects_state.size(); i++) {
    		if (objects_state[i] != OBJECT_STATE_CREATED)
			CreateObject(objects_type[i], objects_properties[i]);
			objects_state[i] = OBJECT_STATE_CREATED;
	}

}

void CSponsor::CreateObject(int type, vector<double> properties) {
	LPGAMEOBJECT obj = NULL;
	switch (type)
	{
	case OBJECT_TYPE_GOOMBA: {
		obj = new CGoomba((float)properties[0], (float)properties[1], (int)properties[2], (int)properties[3]);
		break;
	}
	case OBJECT_TYPE_KOOPA_TROOPA: {
		obj = new CKoopaTroopa((float)properties[0], (float)properties[1], (int)properties[2], (int)properties[3]);
		break;
	}
	default:
		DebugOut(L"[ERROR] SPONSOR: Invalid object type: %d\n", type);
		return;
	}
	// General object setup
	obj->SetPosition((float)properties[0], (float)properties[1]);

	// Add object to the scene
	((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(obj);
}
