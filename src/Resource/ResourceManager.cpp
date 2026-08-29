#include "ResourceManager.h"
#include "Common/toHash.h"
#include <SDL3/SDL.h>
#include <iostream>

/*
struct TTF_Impl
{

};*/

namespace ems_engine
{




	uint64_t ResourceManager::loadTexture(std::string file_path, std::string sceneID, Render& window)
	{
		if (file_path.empty())
		{
			std::cout << "[ERROR]:file_path=" << file_path << "sceneID=" << sceneID << std::endl;
			return 0;
		}
		uint64_t path_hash = string_toHash(file_path);
		auto scene_IDIt = textureCache.find(sceneID);
		if (scene_IDIt != textureCache.end())
		{
			texture_map& map = scene_IDIt->second;
			auto mapIt = map.find(path_hash);
			if (mapIt != map.end())
			{
				return path_hash;
			}
		}
		else
		{
			SDL_Texture* rawtex = window.loadTexture(file_path.c_str());
			if (rawtex == nullptr)
			{
				std::cout << "[ERROR]:loadTexture Failed! file_path:" << file_path << std::endl;
				return 0;
			}
			SDL_SetTextureBlendMode(rawtex, SDL_BLENDMODE_BLEND);
			textureCache[sceneID][path_hash] = std::shared_ptr<SDL_Texture>
				(
					rawtex, [](SDL_Texture* t)
					{
						if (t)
							SDL_DestroyTexture(t);
					}
				);
			return path_hash;
		}
		
	}
	std::shared_ptr<SDL_Texture> ResourceManager::getTexture(uint64_t file_path, std::string sceneID, Render& window)
	{
	
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
		else
		{
			scene_IDIt = textureCache.find("global");
			if (scene_IDIt != textureCache.end())
			{
				texture_map& map = scene_IDIt->second;
				auto mapIt = map.find(0);
				if (mapIt != map.end())
				{
					return mapIt->second;
				}
			}
		}
		return nullptr;
		
	}

	std::shared_ptr<TTF_Font> ResourceManager::readFont(std::string path, float size)
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
	void ResourceManager::clearTextureCache(std::string sceneID)
	{
		textureCache[sceneID].clear();
	}
	void ResourceManager::clearFontCache()
	{
		fontCache.clear();
	}
}
