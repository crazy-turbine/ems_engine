#pragma once
#include <SDL_image.h>
//#include "src/Object/Entity.h"
#include "src/Output/Render.h"
//RenderConfig#include "src/Common/enum.h"
#include <string>

//111110110100000 1000001001110010 100111001010110 100111001010110 1001100100000101 100111001111110
//上面這段保佑這個專案乖乖，勿刪
namespace ems_engine
{

	class Sprite
	{
	public:
		Sprite(std::string sceneID, float x, float y, float w, float h, const char* file_path, Render& window_0, int frames, Uint32 speed);
		void update(bool stop);
		void setflip(bool flip);
		bool getflip();
		void setsize(int display_w, int display_h);
		void setVisible(bool visibility);
		bool getVisible();
	private:
		std::shared_ptr<SDL_Texture> texture; // 角色的精靈圖
		SDL_FRect srcRect, destRect; // 源區域 & 目標區域
		int frameWidth, frameHeight; // 每個動畫幀的大小
		int frameCount; // 總共幾幀
		int currentFrame; // 當前動畫幀
		Uint32 animationSpeed; // 每幀播放多久 (毫秒)
		bool flip_0; //角色翻轉
		bool visible;
		Uint32 lastUpdateTime; // 記錄上次更新時間
		//Unit32大小限制為32位元，且僅記錄正值，故大小為2147483647*2+1=4294967295
	};
}
