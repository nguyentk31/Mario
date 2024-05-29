#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Mario.h"
#include "Object-Goomba.h"
#include "Platform.h"
#include "Portal.h"
#include "Backgrounds.h"
#include "Box.h"
#include "Object-Brick.h"
#include "Object-QuestionBlock.h"
#include "Object-Coin.h"
#include "Object-VenusFireTrap.h"
//#include "Koopas.h"


class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					

	vector<LPGAMEOBJECT> objects;
	// Numbers of each object type in the scene
	vector<int> numbersOfObjects;
	vector<int> orderOfObjects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	// Add new object to the current scene
	void AddObject(int object_type, LPGAMEOBJECT obj);

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

