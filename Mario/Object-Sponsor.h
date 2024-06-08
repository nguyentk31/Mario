#pragma once
#include "GameObject.h"

#define SPONSOR_WIDTH 4

#define OBJECT_STATE_CREATED 1

#define RANGE_IN_DISPLAY 50 // 50px

class CSponsor : public CGameObject
{
protected:
	vector<int> objects_type;
	vector<vector<double>> objects_properties;
	vector<int> objects_state;

	void CreateObject(int type, vector<double> properties);
public: 	
	CSponsor(float x, float y, vector<int> objects_type, vector<vector<double>> objects_properties): CGameObject(OBJECT_TYPE_SPONSOR, x, y) {
		this->objects_type = objects_type;
		this->objects_properties = objects_properties;
		objects_state = vector<int>(objects_type.size(), -1);
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render() {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 1; };
	int IsBlocking() { return 0; }
	void SponseObject();
};