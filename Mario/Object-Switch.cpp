#include "Object-Switch.h"
#include "PlayScene.h"
#include "Object-BreakableBrick.h"

void CSwitch::Render() {
	if (state == SWITCH_STATE_ACTIVE)
		CAnimations::GetInstance()->Get(SWITCH_ANI_ACTIVE)->Render(x, y);
	else if (state == SWITCH_STATE_INACTIVE)
		CSprites::GetInstance()->Get(SWITCH_SPRITE_INACTIVE)->Draw(x, y);
}

void CSwitch::SetState(int state) {
	if (state == SWITCH_STATE_INACTIVE) {
		CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		vector<LPGAMEOBJECT> objects = scene->getObjects();
		for (auto& obj : objects) {
			// Attempt to cast the object to BreakableBrick type
			CBreakableBrick* brick = dynamic_cast<CBreakableBrick*>(obj);

			if (brick != nullptr && brick->GetState() == BB_STATE_NORMAL) {
				brick->SetState(BB_STATE_COIN);
			}
		}
	}
	CGameObject::SetState(state);
}

void CSwitch::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x - SWITCH_SIZE / 2;
	t = y - SWITCH_SIZE / 2;
	r = l + SWITCH_SIZE;
	b = t + SWITCH_SIZE;
}