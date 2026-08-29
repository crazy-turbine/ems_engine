#include "Output/Render.h"
#include <SDL_image.h>
#include "src/Common/struct.h"
#include "src/Resource/ResourceManager.h"
//#include "src/Gameplay/Entity.h"
//#include <SDL3/SDL_ttf.h>
// #include "src/Common/enum.h"
//111110110100000 1000001001110010 100111001010110 100111001010110 1001100100000101 100111001111110
//上面這段保佑這個專案乖乖，勿刪

namespace ems_engine
{

	Render::Render(const char* w_title, int w_w, int w_h)
		:window(NULL), renderer(NULL)
	{

		SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d12");
		SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
		window = SDL_CreateWindow(w_title, w_w, w_h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);

		SDL_Surface* iconSurface = IMG_Load("res/gfx/icon.png");
		if (iconSurface != nullptr)
		{
			SDL_SetWindowIcon(window, iconSurface);
			SDL_DestroySurface(iconSurface); //釋放記憶體
		}
		else
		{
			std::cout << "icon不存在或已經損毀:" << SDL_GetError() << std::endl;
		}
		renderer = SDL_CreateRenderer(window, NULL);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		/*fullscreen(config.fullscreen);
		mousegrab(config.mouseGrab);*/
		fullscreen(true);
		mousegrab(true);
		SDL_SetWindowMinimumSize(window, 640, 480);
		if (window == NULL)
		{
			std::cout << "視窗創建失敗:" << SDL_GetError() << std::endl;
		}
		Vsync(true);
		//Vsync(config.Vsync);


		//renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		SDL_SetRenderLogicalPresentation(renderer, 3840, 2160, SDL_LOGICAL_PRESENTATION_LETTERBOX);
		SDL_Texture* raw_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 3840, 2160);

		if (!raw_tex) {
			std::cout << "RTT 建立失敗: " << SDL_GetError() << std::endl;
		}

		RTT_texture = std::unique_ptr<SDL_Texture, TextureDeleter>(raw_tex, TextureDeleter());
		SDL_SetTextureScaleMode(RTT_texture.get(), SDL_SCALEMODE_LINEAR);
		SDL_SetTextureBlendMode(RTT_texture.get(), SDL_BLENDMODE_BLEND);
	}

	SDL_Texture* Render::loadTexture(const char* file_path)
	{
		SDL_Texture* texture = NULL;//初始化
		texture = IMG_LoadTexture(renderer, file_path);//從main.cpp導入材質

		if (texture == NULL)
		{
			std::cout << "材質載入失敗:" << SDL_GetError() << std::endl;
		}
		return texture;//將材質回傳給main.cpp的變數
	}

	void Render::endWindow()
	{
		if (window != nullptr)
		{
			SDL_DestroyWindow(window);
			window = nullptr;
		}
	}

	void Render::clear()
	{
		SDL_RenderClear(renderer);
	}
	void Render::beforeRender()
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		clear();
		if (!SDL_SetRenderTarget(renderer, RTT_texture.get()))
		{
			std::cout << "Error:SDL_SetRenderTarget Fail!/nSDL_GETERROR:" << SDL_GetError() << std::endl;
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		clear();
	}

	void Render::RenderEntity(RenderConfig config, SDL_Texture* texture)
	{
		SDL_FlipMode fliptype;

		switch (config.flip)
		{
		case FlipType::None:
			fliptype = SDL_FLIP_NONE;
			break;
		case FlipType::Horizontal:
			fliptype = SDL_FLIP_HORIZONTAL;
			break;
		case FlipType::Vertical:
			fliptype = SDL_FLIP_VERTICAL;
			break;
		}

		SDL_FRect dst;

		dst.x = config.x;
		dst.y = config.y;
		dst.w = config.w;
		dst.h = config.h;

		SDL_FPoint Point;
		SDL_FPoint* center;
		if (config.useDefaultCenter)
			center = NULL;
		else
		{
			Point.x = config.PointX;
			Point.y = config.PointY;
			center = &Point;
		}


		SDL_SetTextureAlphaMod(texture, config.alpha);
		SDL_RenderTextureRotated(renderer, texture, nullptr, &dst, config.angle, center, fliptype);
	}

	void Render::renderText(SDL_Texture* Texture, SDL_FRect render)
	{
		SDL_RenderTexture(renderer, Texture, nullptr, &render);
	}


	SDL_Renderer* Render::getRenderer() const
	{
		return renderer;
	}

	SDL_Window* Render::getSDLWindow() const
	{
		return window;
	}

	void Render::display()
	{
		SDL_SetRenderTarget(renderer, nullptr);
		SDL_FRect dest_rect = { 0, 0, 3840.0f, 2160.0f };
		SDL_RenderTexture(renderer, RTT_texture.get(), nullptr, &dest_rect);
		SDL_RenderPresent(renderer);
	}

	void Render::fullscreen(bool full)
	{

		if (full)
		{
			SDL_SetWindowFullscreen(window, true);
			std::cout << "[DEBUG]:Fullscreen turn ON" << std::endl;
		}
		else
		{
			SDL_SetWindowFullscreen(window, false);
			std::cout << "[DEBUG]:Fullscreen turn OFF" << std::endl;
		}
	}
	void Render::Vsync(bool full)
	{

		if (full)
		{
			if (!SDL_SetRenderVSync(renderer, 1))
			{
				SDL_Log("[ERROR]:VSync can not turn on: %s", SDL_GetError());
				return;
			}
			std::cout << "[DEBUG]:Vsync turn ON" << std::endl;
		}
		else
		{
			if (!SDL_SetRenderVSync(renderer, 0))
			{
				SDL_Log("[ERROR]:VSync can not turn off: %s", SDL_GetError());
				return;
			}
			std::cout << "[DEBUG]:Vsync turn OFF" << std::endl;
		}
	}
	void Render::mousegrab(bool full)
	{

		if (full)
		{
			SDL_SetWindowMouseGrab(window, true);
			std::cout << "[DEBUG]:MouseGrab turn ON" << std::endl;
		}
		else
		{
			SDL_SetWindowMouseGrab(window, false);
			std::cout << "[DEBUG]:MouseGrab turn OFF" << std::endl;
		}
	}
	void Render::setTitle(const char* title)
	{
		SDL_SetWindowTitle(window, title);
	}

	void Render::getSize(int& w, int& h)
	{
		SDL_GetWindowSize(window, &w, &h);
	}

	void Render::stopTextInput()
	{
		SDL_StopTextInput(window);
	}
}
