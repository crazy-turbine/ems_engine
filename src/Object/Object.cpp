#include "src/Output/Render.h"
#include "Object.h"
#include "src/Resource/ResourceManager.h"
#include "src/Common/struct.h"
//#include "third_party/magic_enum/magic_enum.hpp"
//#include <Windows.h>

//111110110100000 1000001001110010 100111001010110 100111001010110 1001100100000101 100111001111110
namespace ems_engine
{

	Object::Object(ObjectConfig config, Render& window_0)
		:visible(true), alpha(255), pos({ config.x,config.y }), currentFrame(0), layer(config.layer), TextureIndex(0)
	{
		action = config.actionID;
		seriesID = config.series_num;
		if (!config.slide_button.empty())
			slide_buttonID = config.slide_button;

		for (const auto& path : config.TexturePath)
		{
			Texture.push_back(readTexture(path, config.sceneID, window_0));
		}
		/*
		if (!config.path1.empty())
			texture = readTexture(config.path1, config.sceneID, window_0);
		else
			texture_error = true;
		if (!config.path2.empty())
			texture2 = readTexture(config.path2, config.sceneID, window_0);
		if (!config.path3.empty())
			texture3 = readTexture(config.path3, config.sceneID, window_0);
		if (!config.path4.empty())
			texture4 = readTexture(config.path4, config.sceneID, window_0);
		*/
		RenderData.Texture = Texture.at(TextureIndex).get();

		if (Texture.at(0) != nullptr)
		{
			float width, height;
			SDL_GetTextureSize(Texture.at(0).get(), &width, &height);
			//SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
			if (config.w != 0)
				width = config.w;
			if (config.h != 0)
				height = config.h;
			currentFrame.w = width;
			currentFrame.h = height;
			pos.x = config.x;
			pos.y = config.y;
			O_pos.x = config.x;
			O_pos.y = config.y;
			//std::cout<<"X:" << xy.x <<"Y:" << xy.y << std::endl;
		}
		else
		{
			texture_error = true;
		}
	}


	void Object::CurrentFrame(float w, float h)
	{
		currentFrame.w = w;
		currentFrame.h = h;
	}

	void Object::setPos(float x, float y)
	{
		pos.x = x;
		pos.y = y;
	}

	Vector2f Object::getPos()
	{
		return pos;
	}
	Vector2f Object::getOriginalPos()
	{
		return O_pos;
	}
	void Object::setTex_num(int tex_num)
	{
		TextureIndex = tex_num;
		RenderData.Texture = Texture.at(TextureIndex).get();
	}

	int Object::getTex_num()
	{
		return TextureIndex;
	}

	SDL_Texture* Object::getTex()
	{
		return Texture.at(TextureIndex).get();
	}

	SDL_Rect Object::getCurrentFrame()
	{
		return currentFrame;
	}

	void Object::setVisible(bool visibility)
	{
		visible = visibility;
	}

	bool Object::getVisible()
	{
		return visible;
	}

	void Object::setLayer(int layerID)
	{
		layer = layerID;
	}
	int Object::getLayer()
	{
		return layer;
	}
	void Object::setAlpha(Uint8 alpha_v)
	{
		alpha = alpha_v;

		for (auto& tex : Texture)
		{
			if (tex != nullptr)
			{
				SDL_SetTextureBlendMode(tex.get(), SDL_BLENDMODE_BLEND);
				SDL_SetTextureAlphaMod(tex.get(), alpha);
			}
		}
	}

	Uint8 Object::getAlpha()
	{
		return alpha;
	}
	std::string Object::getAction()
	{
		return action;
	}
	std::string Object::getSlideButton()
	{
		if (!slide_buttonID.empty())
			return slide_buttonID;
	}
	int Object::getSeriesID()
	{
		return seriesID;
	}
	int Object::geterror()
	{
		if (texture_error)
		{
			std::cout << "發生錯誤:材質載入失敗" << std::endl;
			return 1;
		}
		return 0;
	}
}
