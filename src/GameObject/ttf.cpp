#include "src/GameObject/ttf.h"
#include "src/Output/Render.h"
#include "src/Resource/ResourceManager.h"
//#include "third_party/magic_enum/magic_enum.hpp"
namespace ems_engine
{

	ttf::ttf(TextConfig config)
		:display_type(config.Ltype), TextType(config.Ttype), color(config.color), startX(config.startX), endX(config.endX), originalY(config.y), Ofont_path(config.path)
	{
		conditionTarget = config.conditionTarget;
		default_text = config.default_text;
		haveValue_text = config.haveValue_text;

		Ofont = readFont(Ofont_path, config.size);
		max_wide = endX - startX - 60;
		switch (display_type)
		{
		case line_type::single:
			single_text();
			break;
		case line_type::multi:
			break;
		default:
			//std::cout << "[ERROR]:Unexpected value:" << magic_enum::enum_name(display_type) << std::endl;
			break;
		}
		renderQuad.y = originalY;
	}

	void ttf::render(Render& window)
	{
		window.renderText(Texture, renderQuad);
	}
	void ttf::setDisplayText(std::string& text)
	{
		DisplayText = text;
		switch (display_type)
		{
		case line_type::single:
			single_text();
			break;
		case line_type::multi:
			renderQuad.x = startX;
			break;
		default:
			//std::cout << "[ERROR]:Unexpected value:" << magic_enum::enum_name(display_type) << std::endl;
			break;
		}

	}
	std::string ttf::getDisplayText()
	{
		return DisplayText;
	}

	void ttf::setAlpha(Uint8 alpha_v)
	{
		alpha = alpha_v;
		SDL_SetTextureBlendMode(Texture, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(Texture, alpha);
	}

	Uint8 ttf::getAlpha()
	{
		return alpha;
	}
	void ttf::single_text()
	{
		//置中
		int text_w = 0, text_h = 0;
		TTF_Text* text = TTF_CreateText(nullptr, Ofont.get(), DisplayText.c_str(), static_cast<int>(DisplayText.size()));
		if (TTF_GetTextSize(text, &text_w, &text_h) == true)
		{
			float wide;
			if (static_cast<float>(text_w) > max_wide)
			{
				wide = max_wide;
				std::cout << "[DEBUG]:Wide:" << wide << std::endl;
			}
			else
			{
				wide = static_cast<float>(text_w);
			}
			renderQuad.x = (endX - startX - wide) / 2 + startX;
			std::cout << "[DEBUG]:Calculated renderX: " << renderQuad.x << std::endl;
		}
		else
		{
			std::cout << "[ERROR]:Failed to get text size: " << SDL_GetError() << std::endl;
		}
		TTF_DestroyText(text);
	}

	void ttf::refreshTexture(SDL_Renderer* renderer)
	{
		SDL_Surface* textSurface = TTF_RenderText_Blended(Ofont.get(), DisplayText.c_str(), 0, color);
		if (textSurface != NULL)
		{
			Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
			renderQuad.w = textSurface->w;
			renderQuad.h = textSurface->h;

			Uint32* pixels = (Uint32*)textSurface->pixels;
			int pitch = textSurface->pitch / 4;//1px = 4byte

			bool finish = false;
			for (int y = 0; y < textSurface->h; y++)
			{
				for (int x = 0; x < textSurface->w; x++)
				{
					Uint32 pixel = pixels[y * pitch + x];
					Uint8 r, g, b, a;
					SDL_GetRGBA(pixel, SDL_GetPixelFormatDetails(textSurface->format), SDL_GetSurfacePalette(textSurface), &r, &g, &b, &a);
					if (a > 0)
					{
						alphaY = y;
						renderQuad.y = originalY - y;
						finish = true;
						break;
					}
				}
				if (finish)
					break;
			}
			if (display_type == line_type::single && renderQuad.w > max_wide)
			{
				renderQuad.w = max_wide;
			}
		}
		SDL_DestroySurface(textSurface);
	}

	std::vector<JsonTarget>& ttf::getConditionTarget()
	{
		if (TextType != text_type::default_dynamic)
		{
			throw std::runtime_error("Text Type is NOT default_dynamic:" /* + std::string(magic_enum::enum_name(TextType))*/);
		}
		return conditionTarget;
	}
	std::vector<JsonTarget>& ttf::getDefaultTextTarget()
	{
		if (TextType != text_type::default_dynamic)
		{
			throw std::runtime_error("Text Type is NOT default_dynamic:"/* + std::string(magic_enum::enum_name(TextType))*/);
		}
		return default_text;
	}
	std::vector<JsonTarget>& ttf::getHaveValueTextTarget()
	{
		if (TextType != text_type::default_dynamic)
		{
			throw std::runtime_error("Text Type is NOT default_dynamic:"/* + std::string(magic_enum::enum_name(TextType))*/);
		}
		return haveValue_text;
	}
}
