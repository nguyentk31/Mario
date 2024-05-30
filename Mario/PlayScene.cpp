#include <iostream>
#include <fstream>
#include "AssetIDs.h"
#include <algorithm>
#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"

#include "SampleKeyEventHandler.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
	numbersOfObjects = vector<int>(50, 0);
	orderOfObjects = {
		OBJECT_TYPE_BACKGROUNDS,
		OBJECT_TYPE_BOX,
		OBJECT_TYPE_MUSHROOM,
		OBJECT_TYPE_VENUS_FIRE_TRAP,
		OBJECT_TYPE_GOOMBA,
		OBJECT_TYPE_KOOPA_TROOPA,
		OBJECT_TYPE_COIN,
		OBJECT_TYPE_BRICK,
		OBJECT_TYPE_QUESTION_BLOCK,
		OBJECT_TYPE_FIREBALL,
		OBJECT_TYPE_MARIO,
	};

}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) {
		DebugOut(L"[ERROR] Invalid object set: %s\n", ToWSTR(line).c_str());
		return;
	}

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x,y); 
		player = (CMario*)obj;  

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: {
		obj = new CGoomba(x,y); break;
		break;
	}
	case OBJECT_TYPE_COIN: 
	{
		obj = new CCoin(x, y);
		break;
	}
	case OBJECT_TYPE_PLATFORM:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_BRICK:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int lengthX = atoi(tokens[5].c_str());
		int lengthY = atoi(tokens[6].c_str());
		int spriteIdMap[3][3];
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				spriteIdMap[i][j] = atoi(tokens[7 + i * 3 + j].c_str());
		obj = new CBrick(x, y, cell_width, cell_height, lengthX, lengthY, spriteIdMap);
		break;
	}
	case OBJECT_TYPE_BACKGROUNDS:
	{
		int spriteId = atoi(tokens[3].c_str());
		obj = new CBackgrounds(x, y, spriteId);
		break;
	}
	case OBJECT_TYPE_BOX:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int lengthX = atoi(tokens[5].c_str());
		int lengthY = atoi(tokens[6].c_str());
		int spriteColorId = atoi(tokens[7].c_str());
		bool rightShadow = atoi(tokens[8].c_str());
		bool bottomShadow = atoi(tokens[9].c_str());
		obj = new CBox(x, y, cell_width, cell_height, lengthX, lengthY, spriteColorId, rightShadow, bottomShadow);
		break;
	}
	case OBJECT_TYPE_QUESTION_BLOCK:
	{
		int type = atoi(tokens[3].c_str());
		obj = new CQuestionBlock(x, y, type);
		break;
	}
	case OBJECT_TYPE_VENUS_FIRE_TRAP: {
		obj = new CVenusFireTrap(x, y);
		break;
	
	}
	case OBJECT_TYPE_KOOPA_TROOPA: {
		obj = new CKoopaTroopa(x, y);
		break;
	}
	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
		break;
	}

	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	// Add object to the scene
	AddObject(object_type, obj);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// Create non-background object and collision handle needed list
	vector<LPGAMEOBJECT> nonbgObjects;
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->IsBackground())
			continue;
		else
			// Reverse the order of non-background objects to update them in the correct order
			nonbgObjects.insert(nonbgObjects.begin(), objects[i]);

	}

	// Update collision object with other objects
	size_t numNonBgObjects = nonbgObjects.size();
	for ( int i = 0; i < numNonBgObjects; i++)
	{
		if (!nonbgObjects[i]->IsCollidable())
			continue;
		
		LPGAMEOBJECT obj = nonbgObjects[i];
		// nonbgObjects.erase(nonbgObjects.begin() + i);
		obj->Update(dt, &nonbgObjects);
		// i--;
		// numNonBgObjects--;
	}
	

	// Swap dead question block
	auto question_blocks = find_if(objects.begin(), objects.end(), [](CGameObject* obj) {
		return dynamic_cast<CQuestionBlock*>(obj) != nullptr;
	});
	sort(question_blocks, objects.end(), [](CGameObject* a, CGameObject* b) {
		CQuestionBlock* qa = dynamic_cast<CQuestionBlock*>(a);
		CQuestionBlock* qb = dynamic_cast<CQuestionBlock*>(b);
		if (qa && qb) {
			if (qa->GetState() != QUESTION_BLOCK_STATE_ALIVE && qb->GetState() == QUESTION_BLOCK_STATE_ALIVE)
				return true;
		}
		return false;
	});

	

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame *game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;

	if (cx < 0) cx = 0;

	CGame::GetInstance()->SetCamPos(cx, 224.0f /*cy*/);

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

// Add new object to current scene
void CPlayScene::AddObject(int object_type, LPGAMEOBJECT obj)
{
	// Find the position to insert the new object
	int pos = 0;
	for (int i = 0; i < orderOfObjects.size(); i++)
	{
		pos += numbersOfObjects[orderOfObjects[i]];
		if (orderOfObjects[i] == object_type)
			break;

	}


	// Insert the new object
	if (pos < objects.size())
	{
		objects.insert(objects.begin() + pos, obj);
	}
	else
	{
		objects.push_back(obj);
	}

	// Increase the number of objects of this type
	numbersOfObjects[object_type]++;
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}