#pragma once
#include "src/Common/struct.h"
#include <vector>
#include <memory>
//#include "src/Gameplay/ActionBehavior.h"
//#include "src/Common/enum.h"
#include <SDL_image.h>

//111110110100000 1000001001110010 100111001010110 100111001010110 1001100100000101 100111001111110
namespace ems_engine
{

	class Render;

	class Object
	{
	public:
		Object(ObjectConfig config, Render& window_0);
		~Object()
		{
			//std::cout << "Object: 已被銷毀 (Deleted)! Address: " << this << std::endl;
		}
		void CurrentFrame(float w, float h);
		void setPos(float x, float y);
		Vector2f getPos();
		Vector2f getOriginalPos();
		void setTex_num(int tex_num);
		int getTex_num();
		SDL_Texture* getTex();
		SDL_Rect getCurrentFrame();
		void setVisible(bool visibility);
		bool getVisible();
		void setLayer(int layerID);
		int getLayer();
		void setAlpha(Uint8 alpha_v);
		Uint8 getAlpha();
		std::string getAction();
		std::string getSlideButton();
		int getSeriesID();
		int geterror();
		RenderConfig& getRenderConfig();

	private:
		std::string action = "";
		RenderConfig RenderData;
		int layer;
		Vector2f pos;
		Vector2f O_pos;
		std::string slide_buttonID;
		std::vector<std::shared_ptr<SDL_Texture>> Texture;
		int TextureIndex = 0;
		//int tex_use = 1;
		int seriesID = 0;
		SDL_Rect currentFrame;
		bool visible = false;
		Uint8 alpha;
		bool texture_error = false;

	};
}
