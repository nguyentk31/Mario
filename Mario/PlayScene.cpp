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

	numbersOfObjectsForEachType = vector<int>(20, 0);
	orderRenderOfObjectsType = {
		OBJECT_TYPE_BACKGROUNDS,
		OBJECT_TYPE_BOX,
		OBJECT_TYPE_MUSHROOM,
		OBJECT_TYPE_VENUS_FIRE_TRAP,
		OBJECT_TYPE_PTOOIE,
		OBJECT_TYPE_COIN,
		OBJECT_TYPE_BRICK,
		OBJECT_TYPE_QUESTION_BLOCK,
		OBJECT_TYPE_BREAKABLE_BRICK,
		OBJECT_TYPE_SWITCH,
		OBJECT_TYPE_GOOMBA,
		OBJECT_TYPE_KOOPA_TROOPA,
		OBJECT_TYPE_LEAF,
		OBJECT_TYPE_FIREBALL,
		OBJECT_TYPE_MARIO,
	};
	orderUpdateOfObjectsType = {
		OBJECT_TYPE_MARIO,
		OBJECT_TYPE_FIREBALL,
		OBJECT_TYPE_QUESTION_BLOCK,
		OBJECT_TYPE_BREAKABLE_BRICK,
		OBJECT_TYPE_SWITCH,
		OBJECT_TYPE_BRICK,
		OBJECT_TYPE_BOX,
		OBJECT_TYPE_MUSHROOM,
		OBJECT_TYPE_KOOPA_TROOPA,
		OBJECT_TYPE_GOOMBA,
		OBJECT_TYPE_VENUS_FIRE_TRAP,
		OBJECT_TYPE_PTOOIE,
		OBJECT_TYPE_COIN,
		OBJECT_TYPE_LEAF,
		OBJECT_TYPE_TUNNEL,
	};

}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_PROPERTIES 3

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

void CPlayScene::_ParseSection_Property(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 2) return;
	if (tokens[0] == "width")
		sceneWidth = (float)atof(tokens[1].c_str());
	else if (tokens[0] == "height")
		sceneHeight = (float)atof(tokens[1].c_str());
	else
		DebugOut(L"[ERROR] Unknown game setting: %s\n", ToWSTR(tokens[0]).c_str());
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
		return;
	}
	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO: {
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x,y); 
		player = (CMario*)obj;  

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	}
	case OBJECT_TYPE_GOOMBA: {
		int color = (int)atof(tokens[3].c_str());
		int level = (int)atof(tokens[4].c_str());
		obj = new CGoomba(x,y, color, level);
		break;
	}
	case OBJECT_TYPE_COIN: 
	{
		obj = new CCoin(x, y);
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
	case OBJECT_TYPE_BREAKABLE_BRICK:
	{
		int type = atoi(tokens[3].c_str());
		obj = new CBreakableBrick(x, y, type);
		break;
	}
	case OBJECT_TYPE_BACKGROUNDS:
	{
		int spriteId = atoi(tokens[3].c_str());
		int width = atoi(tokens[4].c_str());
		int height = atoi(tokens[5].c_str());
		obj = new CBackgrounds(x, y, spriteId, width, height);
		break;
	}
	case OBJECT_TYPE_BOX:
	{
		int lengthx = (int)atof(tokens[3].c_str());
		int lengthy = (int)atof(tokens[4].c_str());
		int spriteColorId = atoi(tokens[5].c_str());
		bool rightShadow = atoi(tokens[6].c_str());
		bool bottomShadow = atoi(tokens[7].c_str());
		obj = new CBox(x, y, lengthx, lengthy, spriteColorId, rightShadow, bottomShadow);
		break;
	}
	case OBJECT_TYPE_QUESTION_BLOCK:
	{
		int type = atoi(tokens[3].c_str());
		obj = new CQuestionBlock(x, y, type);
		break;
	}
	case OBJECT_TYPE_VENUS_FIRE_TRAP: {
		int color = (int)atof(tokens[3].c_str());
		float rising_distance = (float)atof(tokens[4].c_str());
		obj = new CVenusFireTrap(x, y, color, rising_distance);
		break;
	
	}
	case OBJECT_TYPE_PTOOIE: {
		int color = (int)atof(tokens[3].c_str());
		float rising_distance = (float)atof(tokens[4].c_str());
		obj = new CPtooie(x, y, color, rising_distance);
		break;
	}
	case OBJECT_TYPE_KOOPA_TROOPA: {
		int color = (int)atof(tokens[3].c_str());
		int level = (int)atof(tokens[4].c_str());
		obj = new CKoopaTroopa(x, y, color, level);
		break;
	}
	case OBJECT_TYPE_SWITCH: {
		obj = new CSwitch(x, y);
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
	case OBJECT_TYPE_SPONSOR:
	{
		int num_objects = atoi(tokens[3].c_str());
		vector<int> objects_type;
		vector<vector<double>> objects_properties;
		for (int i = 0; i < num_objects; i++)
		{
			objects_type.push_back(atoi(tokens[4 + i * 5].c_str()));
			objects_properties.push_back({ atof(tokens[5 + i * 5].c_str()), atof(tokens[6 + i * 5].c_str()), atof(tokens[7 + i * 5].c_str()), atof(tokens[8 + i * 5].c_str()) });
		}
		obj = new CSponsor(x, y, objects_type, objects_properties);
		break;
	}
	case OBJECT_TYPE_TUNNEL:
	{
		float w = (float)atof(tokens[3].c_str());
		float h = (float)atof(tokens[4].c_str());
		int in_dir = atoi(tokens[5].c_str());
		float teleportX = (float)atof(tokens[6].c_str());
		float teleportY = (float)atof(tokens[7].c_str());
		obj = new CTunnel(x, y, w, h, in_dir, teleportX, teleportY);
		break;
	}

	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	// Add object to the scene
	AddObject(obj);
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
		if (line == "[PROPERTIES]") { section = SCENE_SECTION_PROPERTIES; continue; }; 	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{
			case SCENE_SECTION_PROPERTIES: _ParseSection_Property(line); break; 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
	// DebugOut(L"List object: ");
	// for (size_t i = 0; i < objects.size(); i++) {
	// 	DebugOut(L"%d ", objects[i]->GetObjectTypeID());
	// }
	// DebugOut(L"\n");
	// DebugOut(L"List order render: ");
	// for (size_t i = 0; i < orderRenderOfObjects.size(); i++) {
	// 	DebugOut(L"%d ", orderRenderOfObjects[i]);
	// }
	// DebugOut(L"\n");
	// DebugOut(L"List order update: ");
	// for (size_t i = 0; i < orderUpdateOfObjects.size(); i++) {
	// 	DebugOut(L"%d ", orderUpdateOfObjects[i]);
	// }
	// DebugOut(L"\n");
	// DebugOut(L"List number of objects: ");
	// for (size_t i = 0; i < orderRenderOfObjects.size(); i++) {
	// 	DebugOut(L"%d ", objects[orderRenderOfObjects[i]]->GetObjectTypeID());
	// }
	// DebugOut(L"\n");
}

void CPlayScene::Update(DWORD dt)
{
	// Create list of update objects
	vector<LPGAMEOBJECT> updateObjects;
	for (size_t i = 0; i < orderUpdateOfObjects.size(); i++)
		updateObjects.push_back(objects[orderUpdateOfObjects[i]]);

	for ( size_t i = 0; i < updateObjects.size(); i++)
	{
		if (!updateObjects[i]->IsCollidable())
			continue;
		
		LPGAMEOBJECT obj = updateObjects[i];
		updateObjects.erase(updateObjects.begin() + i);
		obj->Update(dt, &updateObjects);
		i--;
	}
	
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy, marioX, marioY;
	player->GetPosition(marioX, marioY);
	CGame *game = CGame::GetInstance();
	game->GetCamPos(cx, cy);

	cx = marioX - game->GetBackBufferWidth() / 2;
	if (cx < 0)
		cx = 0;
	else if (cx > sceneWidth - game->GetBackBufferWidth())
		cx = sceneWidth - game->GetBackBufferWidth();

	float limitTop, limitBottom;
	limitTop = cy + 32;
	limitBottom = cy + game->GetBackBufferHeight() - 32;
	if (marioY < limitTop)
	{
		float dif = limitTop - marioY;
		cy -= dif;
	} else if (marioY > limitBottom)
	{
		float dif = marioY - limitBottom;
		cy += dif;
	}
	if (cy < 0)
		cy = 0;
	else if (cy > sceneHeight - game->GetBackBufferHeight())
		cy = sceneHeight - game->GetBackBufferHeight();

	CGame::GetInstance()->SetCamPos(cx, cy);

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (size_t i = 0; i < orderRenderOfObjects.size(); i++)
		objects[orderRenderOfObjects[i]]->Render();
}

// Add new object to current scene
void CPlayScene::AddObject(LPGAMEOBJECT obj)
{
	int objtype = obj->GetObjectTypeID();
	int objpos = static_cast<int>(objects.size());

	// Skip sponsor, tunnel objects when rendering
	if (objtype != OBJECT_TYPE_SPONSOR && objtype != OBJECT_TYPE_TUNNEL) {
		// Find the position of object in Render order
		int renderpos = 0;
		for (size_t i = 0; i < orderRenderOfObjectsType.size(); i++)
		{
			renderpos += numbersOfObjectsForEachType[orderRenderOfObjectsType[i]];
			if (orderRenderOfObjectsType[i] == objtype)
				break;
		}
		if (renderpos > objpos)
			orderRenderOfObjects.push_back(objpos);
		else
			orderRenderOfObjects.insert(orderRenderOfObjects.begin() + renderpos, objpos);
	}

	// Skip background objects when updating
	if (objtype != OBJECT_TYPE_BACKGROUNDS) {
		// Find the position of object in Update order
		int updatepos = 0;
		for (size_t i = 0; i < orderUpdateOfObjectsType.size(); i++)
		{
			updatepos += numbersOfObjectsForEachType[orderUpdateOfObjectsType[i]];
			if (orderUpdateOfObjectsType[i] == objtype)
				break;
		}
		if (updatepos > objpos)
			orderUpdateOfObjects.push_back(objpos);
		else
			orderUpdateOfObjects.insert(orderUpdateOfObjects.begin() + updatepos, objpos);
	}
	
	objects.push_back(obj);
	numbersOfObjectsForEachType[objtype]++;

	// DebugOut(L"List object: ");
	// for (size_t i = 0; i < objects.size(); i++) {
	// 	DebugOut(L"%d ", objects[i]->GetObjectTypeID());
	// }
	// DebugOut(L"\n");
	// DebugOut(L"List order render: ");
	// for (size_t i = 0; i < orderRenderOfObjects.size(); i++) {
	// 	DebugOut(L"%d ", orderRenderOfObjects[i]);
	// }
	// DebugOut(L"\n");
	// DebugOut(L"List order update: ");
	// for (size_t i = 0; i < orderUpdateOfObjects.size(); i++) {
	// 	DebugOut(L"%d ", orderUpdateOfObjects[i]);
	// }
	// DebugOut(L"\n");
	// DebugOut(L"List number of objects: ");
	// for (size_t i = 0; i < orderRenderOfObjects.size(); i++) {
	// 	DebugOut(L"%d ", objects[orderRenderOfObjects[i]]->GetObjectTypeID());
	// }
	// DebugOut(L"\n");
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
	// Remove all deleted objects
	std::vector<int> deletedIndices;
	for (int i = 0; i < objects.size(); i++)
	{
		LPGAMEOBJECT o = objects[i];
		if (o->IsDeleted())
		{
			int objtype = o->GetObjectTypeID();
			DebugOut(L"[INFO] Delete object %d\n", objtype);
			numbersOfObjectsForEachType[objtype]--;
			delete o;
			objects[i] = NULL;
			deletedIndices.push_back(i);
		}
	}

	if (deletedIndices.size() == 0)
		return;
	
	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
	
	// Update order of objects
	for (size_t i = deletedIndices.size(); i > 0; i--)
	{
		int index = deletedIndices[i-1];

		orderRenderOfObjects.erase(
			remove_if(orderRenderOfObjects.begin(), orderRenderOfObjects.end(), [index](int j) { return j == index; }),
			orderRenderOfObjects.end());
		transform(orderRenderOfObjects.begin(), orderRenderOfObjects.end(), orderRenderOfObjects.begin(), [index](int j) { return j > index ? j - 1 : j; });
		
		orderUpdateOfObjects.erase(
			remove_if(orderUpdateOfObjects.begin(), orderUpdateOfObjects.end(), [index](int j) { return j == index; }),
			orderUpdateOfObjects.end());
		transform(orderUpdateOfObjects.begin(), orderUpdateOfObjects.end(), orderUpdateOfObjects.begin(), [index](int j) { return j > index ? j - 1 : j; });
	}
}