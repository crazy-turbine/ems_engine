#include "include/ems_engine/Engine.h"
#include "src/Output/Audio.h"
#include "src/Output/Render.h"
#include "src/Resource/jsonManager.h"
#include <SDL3/SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>

ems::Engine::Engine()
{
	windowWidth = 0;
	windowHeight = 0;
	render_sys = nullptr;
	Display = NULL;
	displayMode = nullptr;
}

bool ems::Engine::init()
{
	if (!initSDL())
		return false;
	if (!checkResolution())
		return false;
	if (!set_cursor())
		return false;

	render_sys = std::make_unique<Render>("A Day of Feb", windowWidth, windowHeight);

}
bool ems::Engine::initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		showError("SDL Init Error:", SDL_GetError());
		return false;
	}
	if (!TTF_Init())
	{
		showError("SDL Init Error:", SDL_GetError());
		return false;
	}

	sound_sys = std::make_unique<audio>();
	sound_sys->initAudio();
	Display = SDL_GetPrimaryDisplay();
	displayMode = SDL_GetCurrentDisplayMode(Display);

	if (displayMode == 0)
	{
		showError("SDL Init Error:", SDL_GetError());
		return false;
	}
	return true;
}
void ems::Engine::showError(std::string msg, std::string err)
{
	std::cout << "[ERROR]:" << msg << err << std::endl;
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "A Day of Feb", err.c_str(), NULL);
	//MessageBoxW(nullptr, to_utf16(err).c_str(), L"A Day of Feb", MB_OK | MB_ICONERROR);
}
bool ems::Engine::checkResolution()
{
	if (displayMode->w < 1024 || displayMode->h < 768)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "A Day of Feb", "您的顯示器解析度低於遊戲所支援之最低解析度(1024*768)。", NULL);
		//MessageBoxW(nullptr, L"您的顯示器解析度低於遊戲所支援之最低解析度(1024*768)。", L"A Day of Feb", MB_OK | MB_ICONERROR);
		return false;
	}
	std::cout << "[DEBUG]:Screen Resolution:" << windowWidth << "x" << windowHeight << std::endl;
	windowWidth = displayMode->w / 3 * 2;
	windowHeight = displayMode->h / 3 * 2;
	if (windowWidth < 640)
		windowWidth = 640;
	if (windowHeight < 480)
		windowHeight = 480;
	std::cout << "[DEBUG]:Window Resolution:" << windowWidth << "x" << windowHeight << std::endl;
	return true;
}
bool ems::Engine::set_cursor()
{
	SDL_Surface* surf = IMG_Load("res/gfx/cursor.png");
	if (!surf)
	{
		showError("IMG Load Error:", SDL_GetError());
		return false;
	}
	SDL_Cursor* cur = SDL_CreateColorCursor(surf, 0, 0);
	if (!cur)
	{
		showError("Cursor Error:", SDL_GetError());
		return false;
	}
	SDL_DestroyCursor(SDL_GetCursor());
	SDL_SetCursor(cur);
	SDL_ShowCursor();
	return true;
}