#pragma once
#include "src/GameObject/Entity.h"
#include "src/GameObject/ttf.h"
#include "src/GameObject/Sprite.h"
//#include "src/Common/function.h"
#include <vector>
#include <map>
#include "src/Scene/sceneManager.h"


//111110110100000 1000001001110010 100111001010110 100111001010110 1001100100000101 100111001111110
//上面這段保佑這個專案乖乖，勿刪


namespace ems_engine
{

	//extern std::map<std::string, Entity*> EntityMap;
	extern std::map<std::string, Sprite*> SpriteMap;

	void createEntity(Render& window, SceneManager& Manager);
	void createTEXT(SceneManager& Manager, std::string lang);
	void createSprite(Render& window, int w, int h);
	void createMap(Render& window, int w, int h);
	Entity* getEntity(const std::string& name);
	Sprite* getSprite(const std::string& name);
	//Map* getMap(const std::string& name);

	//清理所有實體
	//void deleteAll();
	//SceneManager同名function已取代此功能
}
