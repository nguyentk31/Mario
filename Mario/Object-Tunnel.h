#pragma once
#include "GameObject.h"

#define TUNNEL_IN_DIRECTION_DOWN 1
#define TUNNEL_IN_DIRECTION_UP 2

class CTunnel : public CGameObject
{
protected:
	int direction;
	float width, height; // pixel
	float teleportX, teleportY;
public: 	
	CTunnel(float x, float y, float w, float h, int in_dir, float teleportX, float teleportY) : CGameObject(OBJECT_TYPE_TUNNEL, x, y) {
		direction = in_dir;
		width = w;
		height = h;
		this->teleportX = teleportX;
		this->teleportY = teleportY;
	}
	void Render() {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {
		l = x - width / 2;
		t = y - height / 2;
		r = l + width;
		b = t + height;
	}
	int IsBlocking() { return 0; }
	int GetDirection() { return direction; }
	void GetTeleportPosition(float& x, float& y) { x = teleportX; y = teleportY; }
};