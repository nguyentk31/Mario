#pragma once
#include "GameObject.h"

#define SPONSOR_WIDTH 4

#define OBJECTS_STATE_OUT_DISPLAY 1
#define OBJECTS_STATE_IN_DISPLAY 2
#define OBJECTS_STATE_DEAD 3
#define OBJECT_STATE_CREATED 4

#define RANGE_IN_DISPLAY 50 // 50px

class CSponsor : public CGameObject
{
protected:
	vector<int> objects_type;
	vector<vector<float>> objects_position;
	vector<int> objects_state;

	void CreateObject(int type, float x, float y);
public: 	
	CSponsor(float x, float y, vector<int> objects_type, vector<vector<float>> objects_position): CGameObject(OBJECT_TYPE_SPONSOR, x, y) {
		this->objects_type = objects_type;
		this->objects_position = objects_position;
		objects_state = vector<int>(objects_type.size(), -1);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render() {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void SponseObject();
};