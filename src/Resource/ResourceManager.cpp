#include "ResourceManager.h"
#include <memory>
#include<string>
#include <unordered_map>

/*
struct TTF_Impl
{

};*/

namespace ems_engine
{

	using texture_map = std::unordered_map < std::string, std::shared_ptr<SDL_Texture>>;
	//sceneID,entityID,Texture
	std::unordered_map < std::string/*scene_ID*/, texture_map> textureCache;
	using font_map = std::unordered_map < float, std::shared_ptr<TTF_Font>>;
	std::unordered_map < std::string, font_map> fontCache;


	std::shared_ptr<SDL_Texture> readTexture(std::string file_path, std::string sceneID, Render& window)
	{
		if (file_path.empty())
		{
			std::cout << "[ERROR]:file_path=" << file_path << "sceneID=" << sceneID << std::endl;
			return nullptr;
		}
		auto scene_IDIt = textureCache.find(sceneID);
		if (scene_IDIt != textureCache.end())
		{
			texture_map& map = scene_IDIt->second;
			auto mapIt = map.find(file_path);
			if (mapIt != map.end())
			{
				return mapIt->second;
			}
		}
		SDL_Texture* rawtex = window.loadTexture(file_path.c_str());
		if (rawtex == nullptr)
		{
			std::cout << "[ERROR]:Texture not found! file_path:" << file_path << std::endl;
			return nullptr;
		}
		textureCache[sceneID][file_path] = std::shared_ptr<SDL_Texture>
			(
				rawtex, [](SDL_Texture* t)
				{
					if (t)
						SDL_DestroyTexture(t);
				}
			);
		return textureCache[sceneID][file_path];
	}

	std::shared_ptr<TTF_Font> readFont(std::string path, float size)
	{
		if (size == NULL)
		{
			std::cout << "[ERROR]:size=" << size << "path=" << path << std::endl;
			return nullptr;
		}
		auto pathIt = fontCache.find(path);
		if (pathIt != fontCache.end())
		{
			font_map& map = pathIt->second;
			auto mapIt = map.find(size);
			if (mapIt != map.end())
			{
				return mapIt->second;
			}
		}
		SDL_PropertiesID props = SDL_CreateProperties();
		SDL_SetStringProperty(props, TTF_PROP_FONT_CREATE_FILENAME_STRING, path.c_str());
		SDL_SetFloatProperty(props, TTF_PROP_FONT_CREATE_SIZE_FLOAT, size);
		SDL_SetNumberProperty(props, TTF_PROP_FONT_CREATE_VERTICAL_DPI_NUMBER, 96);
		SDL_SetNumberProperty(props, TTF_PROP_FONT_CREATE_HORIZONTAL_DPI_NUMBER, 96);
		TTF_Font* rawfont = TTF_OpenFontWithProperties(props);
		SDL_DestroyProperties(props);

		if (rawfont == nullptr)
		{
			std::cout << "[ERROR]:Font not found! path:" << path << std::endl;
			return nullptr;
		}
		fontCache[path][size] = std::shared_ptr<TTF_Font>
			(
				rawfont, [](TTF_Font* t)
				{
					if (t)
						TTF_CloseFont(t);
				}
			);
		return fontCache[path][size];
	}
	void clearTextureCache(std::string sceneID)
	{
		textureCache[sceneID].clear();
	}
	void clearFontCache()
	{
		fontCache.clear();
	}
}
