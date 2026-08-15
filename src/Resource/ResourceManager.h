#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>
#include "src/Output/Render.h"
#include "src/Common/enum.h"

//struct TTF_Impl;
namespace ems_engine
{

	std::shared_ptr<SDL_Texture> readTexture(std::string file_path, std::string sceneID, Render& window);
	std::shared_ptr<TTF_Font> readFont(std::string path, float size);
	void clearTextureCache(std::string sceneID);
	void clearFontCache();
}
