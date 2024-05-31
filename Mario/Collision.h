#pragma once

#include <Windows.h>
#include <vector>
#include <algorithm>

using namespace std;

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;

struct CCollisionEvent 
{
	LPGAMEOBJECT src_obj;		// source object : the object from which to calculate collision
	LPGAMEOBJECT obj;			// the target object
	
	float t, nx, ny;

	float dx, dy;				// *RELATIVE* movement distance between this object and obj
	bool isDeleted;		

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, 
		LPGAMEOBJECT obj = NULL, LPGAMEOBJECT src_obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
		this->src_obj = src_obj;
		this->isDeleted = false;
	}

	int WasCollided(); 

	// sort collision events by time
	// if t is the same, sort by obj's blocking property (blocking object comes first)
	static bool compare(const LPCOLLISIONEVENT& a,const LPCOLLISIONEVENT& b);
};

class CCollision
{
	static CCollision* __instance;
public: 
	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st,
		float sr,
		float sb,
		float& t,
		float& nx,
		float& ny);

	LPCOLLISIONEVENT SweptAABB(
		LPGAMEOBJECT objSrc, 
		DWORD dt,
		LPGAMEOBJECT objDest); 

	void Scan(
		LPGAMEOBJECT objSrc, 
		DWORD dt, 
		vector<LPGAMEOBJECT>* objDests,
		vector<bool>& processedFlags, 
		LPCOLLISIONEVENT& firstColEvent,
		int& colEventIndex);
	// void Scan(
	// 	LPGAMEOBJECT objSrc, 
	// 	DWORD dt, 
	// 	vector<LPGAMEOBJECT>* objDests, 
	// 	vector<LPCOLLISIONEVENT>& coEvents);

	// void Filter(
	// 	LPGAMEOBJECT objSrc,
	// 	vector<LPCOLLISIONEVENT>& coEvents,
	// 	LPCOLLISIONEVENT &colX,
	// 	LPCOLLISIONEVENT &colY, 
	// 	int filterBlock,		
	// 	int filterX,
	// 	int filterY);

	void Process(LPGAMEOBJECT objSrc, DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void CollisionWithBlockingObj(LPGAMEOBJECT objSrc, DWORD dt, LPCOLLISIONEVENT colEvent);
	void CollisionWithNonBlockingObj(LPGAMEOBJECT objSr, DWORD dt, LPCOLLISIONEVENT colEvent);

	static CCollision* GetInstance();
};