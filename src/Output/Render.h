#pragma once
#include <SDL3/SDL.h>

#include <iostream>



//111110110100000 1000001001110010 100111001010110 100111001010110 1001100100000101 100111001111110
//上面這段保佑這個專案乖乖，勿刪

namespace ems_engine
{

	class Entity;
	struct RenderConfig;

	struct TextureDeleter
	{
		void operator()(SDL_Texture* t) const
		{
			if (t) SDL_DestroyTexture(t);
		}
	};

	class Render
	{
	public:
		Render(const char* w_title, int w_w, int w_h);
		SDL_Texture* loadTexture(const char* file_path);
		void endWindow();
		void beforeRender();
		void RenderEntity(RenderConfig config);
		void renderText(SDL_Texture* Texture, SDL_FRect render);
		SDL_Renderer* getRenderer() const;
		SDL_Window* getSDLWindow() const;
		void display();
		void fullscreen(bool full);
		void Vsync(bool full);
		void mousegrab(bool full);
		//void meta(bool full);
		void setTitle(const char* title);
		void getSize(int& w, int& h);
		void stopTextInput();
	private:
		void clear();
		std::unique_ptr<SDL_Texture, TextureDeleter> RTT_texture;
		SDL_Window* window;
		SDL_Renderer* renderer;
	};
}
