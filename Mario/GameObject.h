#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>
#include "debug.h"
#include "AssetIDs.h"
#include "Animation.h"
#include "Animations.h"
#include "Sprites.h"
#include "Collision.h"

using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define BBOX_ALPHA 0.25f		// Bounding box transparency

class CGameObject
{
protected:

	float x; 
	float y;

	float vx;
	float vy;

	int nx;	 

	int state;

	bool isDeleted;

	int objectTypeID;

public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	float GetX() { return x; }
	void SetX(float x) { this->x = x; }
	float GetY() { return y; }
	void SetY(float y) { this->y = y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	float GetVx() { return vx; }
	void SetVx(float vx) { this->vx = vx; }
	float GetVy() { return vy; }
	void SetVy(float vy) { this->vy = vy; }

	int GetObjectTypeID() { return objectTypeID; }

	int GetState() { return this->state; }
	virtual void Delete() { isDeleted = true;  }
	bool IsDeleted() { return isDeleted; }

	void RenderBoundingBox();

	CGameObject();
	CGameObject(int objectTypeId, float x, float y) :CGameObject() { this->objectTypeID = objectTypeId; this->x = x; this->y = y; }


	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }
	// Whether background or not
	virtual int IsBackground() { return 0; }

	//
	// Collision ON or OFF ? This can change depending on object's state. For example: die
	//
	virtual int IsCollidable() { return 0; };

	// When no collision has been detected (triggered by CCollision::Process)
	virtual void OnNoCollision(DWORD dt) {};

	// When collision with an object has been detected (triggered by CCollision::Process)
	virtual void OnCollisionWith(vector<LPCOLLISIONEVENT> events) {};
	
	// When overlapse with other objects
	virtual void OnOverlapseWith(vector<LPCOLLISIONEVENT> events) {};

	// Is this object blocking other object? If YES, collision framework will automatically push the other object
	virtual int IsBlocking() { return 1; }

	// Is this object collide with other object at certain direction ( like ColorBox )
	virtual int IsDirectionColliable(float nx, float ny) { return 1; }

	~CGameObject();

	static bool IsDeleted(const LPGAMEOBJECT &o) { return o->isDeleted; }
};
