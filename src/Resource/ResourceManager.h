#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>
#include "src/Output/Render.h"
#include "src/Common/enum.h"
#include <unordered_map>
#include <memory>
#include<string>

//struct TTF_Impl;
namespace ems_engine
{
	class ResourceManager
	{
	public:
		uint64_t loadTexture(std::string file_path, std::string sceneID, Render& window);
		std::shared_ptr<SDL_Texture> getTexture(uint64_t file_path, std::string sceneID, Render& window);
		
		std::shared_ptr<TTF_Font> readFont(std::string path, float size);
		void clearTextureCache(std::string sceneID);
		void clearFontCache();
	private:
		using texture_map = std::unordered_map < uint64_t, std::shared_ptr<SDL_Texture>>;
		//sceneID,entityID,Texture
		std::unordered_map < std::string, texture_map> textureCache;
		using font_map = std::unordered_map < float, std::shared_ptr<TTF_Font>>;
		std::unordered_map < std::string, font_map> fontCache;
	};
}
