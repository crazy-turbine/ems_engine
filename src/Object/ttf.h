#pragma once
#include "src/Common/struct.h"
#include <SDL3/SDL_ttf.h>
#include <SDL_image.h>
//#include "src/Common/function.h"
#include "src/Common/enum.h"
#include <memory>

namespace ems_engine
{

	class Render;

	class ttf
	{
	public:

		ttf(TextConfig config);
		~ttf()
		{
			//std::cout << "TTF: 已被銷毀 (Deleted)! Address: " << this << std::endl;
		}
		void render(Render& window);
		void setDisplayText(std::string& text);
		std::string getDisplayText();
		void setAlpha(Uint8 alpha_v);
		Uint8 getAlpha();
		void refreshTexture(SDL_Renderer* renderer);
		std::vector<JsonTarget>& getConditionTarget();
		std::vector<JsonTarget>& getDefaultTextTarget();
		std::vector<JsonTarget>& getHaveValueTextTarget();



	private:
		void single_text();

		std::string DisplayText = "I CAN'T FIND THAT TEXT!!";
		line_type display_type;
		std::string Ofont_path;
		std::shared_ptr<TTF_Font> Ofont;
		SDL_Color color;
		SDL_Texture* Texture;
		Uint8 alpha;
		int originalW = 0;
		float startX;
		float endX;
		float originalY;
		int alphaY;
		float max_wide;
		text_type TextType;
		std::vector<JsonTarget> conditionTarget;
		std::vector<JsonTarget> default_text;
		std::vector<JsonTarget> haveValue_text;
		SDL_FRect renderQuad = { 0, 0, 0, 0 };
	};
}
