#pragma once
#include <functional>
#include <string>


//111110110100000 1000001001110010 100111001010110 100111001010110 1001100100000101 100111001111110
//上面這段保佑這個專案乖乖，勿刪


namespace ems_engine
{
	class Sprite;
	class ttf;
	class SceneManager;
	class Scene;
	class ResourceManager;
	class Render;


	class Object;
	class TextureObject;

	//UI
	class UIElement;
	class UIStateElement;
	class UIButton;
	class UICheckBox;
	class UISlider;


	class ObjectFactory
	{
	public:
		ObjectFactory(ResourceManager* rc_mgr, Render* render_sys, std::string base_path);
		void createSceneObject(Scene* scene,std::string sceneID);
	private:

		void createObject(Object* object);
		void createObject(TextureObject* object);
		void createObject(UIElement* object);
		void createObject(UIStateElement* object);
		void createObject(UIButton* object);
		void createObject(UICheckBox* object);
		void createObject(UISlider* object);

		ResourceManager* rc_mgr_;
		Render* render_sys_;
		std::string base_path_ = "";
	};


	void createEntity(SceneManager& Manager, ResourceManager& rc_mgr, Render& window);
	void createTEXT(SceneManager& Manager, std::string lang, ResourceManager* rc_mgr);
	//void createSprite(Render& window, int w, int h);
	void createMap(Render& window, int w, int h);
	//Sprite* getSprite(const std::string& name);
	//Map* getMap(const std::string& name);
}
