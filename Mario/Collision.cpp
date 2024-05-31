#include "Collision.h"
#include "GameObject.h"

#include "debug.h"

#define BLOCK_PUSH_FACTOR 0.4f

int CCollisionEvent::WasCollided() { return t >= 0.0f && t <= 1.0f && obj->IsDirectionColliable(nx, ny)==1; }

CCollision* CCollision::__instance = NULL;

CCollision* CCollision::GetInstance()
{
	if (__instance == NULL) __instance = new CCollision();
	return __instance;
}

bool CCollisionEvent::compare(const LPCOLLISIONEVENT& a,const LPCOLLISIONEVENT& b)
{
	if (a->t != b->t)
		return a->t < b->t;
	if (a->obj->IsBlocking() && !b->obj->IsBlocking()) return true;
	if (!a->obj->IsBlocking() && b->obj->IsBlocking()) return false;
	return false;
}

/*
	SweptAABB 
*/
void CCollision::SweptAABB(
	float ml, float mt, float mr, float mb,
	float dx, float dy,
	float sl, float st, float sr, float sb,
	float& t, float& nx, float& ny)
{

	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;

	//
	// Broad-phase test 
	//

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	if (br < sl || bl > sr || bb < st || bt > sb) return;


	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}

	if (dx == 0)
	{
		tx_entry = -9999999.0f;
		tx_exit = 99999999.0f;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999999999.0f;
		ty_exit = 99999999999.0f;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}

}

/*
	Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT CCollision::SweptAABB(LPGAMEOBJECT objSrc, DWORD dt, LPGAMEOBJECT objDest)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	float mvx, mvy;
	objSrc->GetSpeed(mvx, mvy);
	float mdx = mvx * dt;
	float mdy = mvy * dt;

	float svx, svy;
	objDest->GetSpeed(svx, svy);
	float sdx = svx * dt;
	float sdy = svy * dt;

	//
	// NOTE: new m speed = original m speed - collide object speed
	// 
	float dx = mdx - sdx;
	float dy = mdy - sdy;

	objSrc->GetBoundingBox(ml, mt, mr, mb);
	objDest->GetBoundingBox(sl, st, sr, sb);

	SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent* e = new CCollisionEvent(t, nx, ny, dx, dy, objDest, objSrc);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects

	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CCollision::Scan(LPGAMEOBJECT objSrc, DWORD dt, vector<LPGAMEOBJECT>* objDests, vector<bool>& processedFlags, LPCOLLISIONEVENT& firstColEvt, int& colEventIndex)
{
	vector<pair<LPCOLLISIONEVENT, int>> coEvtWithIndex;
	int coEvtIndex = 0;

	for (UINT i = 0; i < objDests->size(); i++)
	{
		if (processedFlags[i]) continue;
		// skip deleted objects
		if (objDests->at(i)->IsDeleted()) {
			processedFlags[i] = true;
			continue;	
		}
		
		LPCOLLISIONEVENT e = SweptAABB(objSrc, dt, objDests->at(i));
		if (e->WasCollided()==1)
			coEvtWithIndex.push_back(make_pair(e, coEvtIndex++));
		else
			delete e;
	}

	if (coEvtWithIndex.size() == 0)
	{
		firstColEvt = NULL;
		colEventIndex = -1;
		return;
	}

	sort(coEvtWithIndex.begin(), coEvtWithIndex.end(), [](const auto& a, const auto& b) {
    		return CCollisionEvent::compare(a.first, b.first);
	});
	firstColEvt = coEvtWithIndex[0].first;
	colEventIndex = coEvtWithIndex[0].second;

}

void CCollision::Process(LPGAMEOBJECT objSrc, DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<bool> processedFlags(coObjects->size(), false);
	LPCOLLISIONEVENT firstCol = NULL;
	int colEventIndex;

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		Scan(objSrc, dt, coObjects, processedFlags, firstCol, colEventIndex);

		if (firstCol == NULL)
		{
			objSrc->OnNoCollision(dt);
			return;
		}

		if (firstCol->obj->IsBlocking())
		{
			CollisionWithBlockingObj(objSrc, dt, firstCol);
		}
		else
		{
			CollisionWithNonBlockingObj(objSrc, dt, firstCol);
		}

		processedFlags[colEventIndex] = true;
	}

	delete firstCol;

}

void CCollision::CollisionWithBlockingObj(LPGAMEOBJECT objSrc, DWORD dt, LPCOLLISIONEVENT colEvent)
{
	float x, y, vx, vy, dx, dy;
	objSrc->GetPosition(x, y);
	objSrc->GetSpeed(vx, vy);
	dx = vx * dt;
	dy = vy * dt;

	if (colEvent->nx != 0)
	{
		x += colEvent->t * dx + colEvent->nx * BLOCK_PUSH_FACTOR;
	}
	else
	{
		y += colEvent->t * dy + colEvent->ny * BLOCK_PUSH_FACTOR;
	}

	objSrc->SetPosition(x, y);
	objSrc->OnCollisionWith(colEvent);
}

void CCollision::CollisionWithNonBlockingObj(LPGAMEOBJECT objSrc, DWORD dt, LPCOLLISIONEVENT colEvent)
{
	objSrc->OnCollisionWith(colEvent);
}
