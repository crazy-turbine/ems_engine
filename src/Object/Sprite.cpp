#include "src/Object/Sprite.h"
#include "src/Resource/ResourceManager.h"
#include <string>

//111110110100000 1000001001110010 100111001010110 100111001010110 1001100100000101 100111001111110
//上面這段保佑這個專案乖乖，勿刪
namespace ems_engine
{

	Sprite::Sprite(std::string sceneID, float x, float y, float w, float h, const char* file_path, Render& window_0, int frames, Uint32 speed)
		:frameWidth(w), frameHeight(h), frameCount(frames), currentFrame(0), animationSpeed(speed), flip_0(false), visible(true)
	{
		//texture = readTexture(file_path, sceneID, window_0);
		destRect = { x,y,w,h };
		srcRect = { 0,0,w,h };//第一幀
		lastUpdateTime = SDL_GetTicks();

	}


	//檢查是否到更新幀的時間
	void Sprite::update(bool stop)
	{

		Uint32 now = SDL_GetTicks();
		if (!stop)
		{
			if (now - lastUpdateTime > animationSpeed)
			{
				currentFrame = (currentFrame + 1) % frameCount; // 切換到下一幀
				srcRect.x = currentFrame * frameWidth; // 設定要顯示的區域
				lastUpdateTime = now; // 更新時間戳
			}
		}
		else
		{
			currentFrame = 0;
			srcRect.x = currentFrame * frameWidth;
		}
	}

	void Sprite::setflip(bool flip)
	{
		flip_0 = flip;
	}
	
	bool Sprite::isflip()
	{
		return flip_0;
	}


	void Sprite::setsize(int display_w, int display_h)
	{
		destRect.w = display_w;
		destRect.h = display_h;
	}

	void Sprite::setVisible(bool visibility)
	{
		visible = visibility;
	}

	bool Sprite::isVisible()
	{
		return visible;
	}
}


