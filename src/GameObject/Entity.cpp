#include "src/Output/Render.h"
#include "Entity.h"
#include "src/Resource/ResourceManager.h"
//#include "third_party/magic_enum/magic_enum.hpp"
//#include <Windows.h>

//111110110100000 1000001001110010 100111001010110 100111001010110 1001100100000101 100111001111110


Entity::Entity(EntityConfig config, Render& window_0)
	:visible(true), alpha(255), pos({config.x,config.y}), texture(nullptr), currentFrame(0),texture2(nullptr),layer(config.layer)
{
	action = config.actionID;
	seriesID = config.series_num;
	if (!config.slide_button.empty())
		slide_buttonID = config.slide_button;
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


	if (texture != nullptr)
	{
		float width, height;
		SDL_GetTextureSize(texture.get(), &width, &height);
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
	if (texture2 == nullptr)
	{
		texture_error = true;
	}
}


void Entity::CurrentFrame(float w,float h)
{
	currentFrame.w = w;
	currentFrame.h = h;
}

void Entity::setPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

Vector2f Entity::getPos()
{
	return pos;
}
Vector2f Entity::getOriginalPos()
{
	return O_pos;
}
void Entity::setTex_num(int tex_num)
{
	tex_use = tex_num;
}

int Entity::getTex_num()
{
	return tex_use;
}

SDL_Texture* Entity::getTex()
{
	if (tex_use == 1)
		return texture.get();
	else if (tex_use == 2)
	{
		if(texture2 != nullptr)
			return texture2.get();
	}
	else if (tex_use == 3)
	{
		if (texture3 != nullptr)
			return texture3.get();
	}
	else if (tex_use == 4)
	{
		if (texture4 != nullptr)
			return texture4.get();
	}
	return texture.get();
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

void Entity::setVisible(bool visibility)
{
	visible = visibility;
}

bool Entity::getVisible()
{
	return visible;
}

void Entity::setLayer(int layerID)
{
	layer = layerID;
}
int Entity::getLayer()
{
	return layer;
}
void Entity::setAlpha(Uint8 alpha_v)
{
	alpha = alpha_v;
	if (texture != nullptr)
	{
		SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(texture.get(), alpha);
	}
	if (texture2 != nullptr)
	{
		SDL_SetTextureBlendMode(texture2.get(), SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(texture2.get(), alpha);
	}
}

Uint8 Entity::getAlpha()
{
	return alpha;
}
std::string Entity::getAction()
{
	return action;
}
std::string Entity::getSlideButton()
{
	if (!slide_buttonID.empty())
		return slide_buttonID;
}
int Entity::getSeriesID()
{
	return seriesID;
}
int Entity::geterror()
{
	if (texture_error)
	{
		std::cout << "發生錯誤:材質載入失敗" << std::endl;
		return 1;
	}
	return 0;
}