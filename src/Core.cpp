#include "include/ems_engine/Core.h"
#include "Output/Audio.h"
#include "Output/Render.h"
#include "Output/RenderManager.h"
#include "Resource/jsonManager.h"
#include "Scene/sceneManager.h"
#include "Action/ActionBehavior.h"
#include "Action/ActionPolicyManager.h"
#include "Input/InputManager.h"
#include "Common/Event.h"
#include <SDL3/SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
namespace ems_engine
{

	Core::Core()
	{
		windowWidth = 0;
		windowHeight = 0;
		render_sys = nullptr;
		sound_sys = nullptr;
		input_mgr = nullptr;
		button_def = nullptr;
		ap_mgr = nullptr;
		Display = NULL;
		displayMode = nullptr;
	}
	Core::~Core() = default;
	bool Core::init(std::function<void(Core*)> custom_init)
	{
		if (!initSDL())
			return false;
		/*if (!checkResolution())
			return false;*/
		if (!set_cursor())
			return false;

		render_sys = std::make_unique<Render>("A Day of Feb", windowWidth, windowHeight);
		render_mgr = std::make_unique<RenderManager>();
		ap_mgr = std::make_unique<ActionPolicyManager>();
		button_def = std::make_unique<ActionBehavior>(ap_mgr.get());
		ui_mgr = std::make_unique<SceneManager>();
		input_mgr = std::make_unique<InputManager>(button_def.get(), ui_mgr.get());
		
		custom_init(this);
		app = true;
		return true;
	}
	void Core::run(std::function<void(Core*)> custom_update)
	{
		while (app)
		{
			handleEvents();
			
			if (!render_mgr->runRender(*render_sys.get(), *ui_mgr.get()))
			{
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "A Day of Feb", "您的遊戲檔案不完整，無法正確載入材質。\n請嘗試將遊戲重新安裝，若嘗試後此情況扔然持續發生，請聯絡Evil Month Studio團隊。\n聯絡我們:evilmonth.studio@gmail.com", render_sys->getSDLWindow());
				//MessageBoxW(nullptr, L"您的遊戲檔案不完整，無法正確載入材質。/n請嘗試將遊戲重新安裝，若嘗試後此情況扔然持續發生，請聯絡Evil Month Studio團隊。/n聯絡我們:evilmonth.studio@gmail.com", L"A Day of Feb", MB_OK | MB_ICONERROR);
				app = false;
			}

			custom_update(this);
		}
	}
	void Core::handleEvents()
	{
		input_mgr->InputRefresh();
		EngineEvent(event, *render_sys.get(), *ui_mgr.get());
	}
	bool Core::initSDL()
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
	void Core::showError(std::string msg, std::string err)
	{
		std::cout << "[ERROR]:" << msg << err << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "A Day of Feb", err.c_str(), NULL);
		//MessageBoxW(nullptr, to_utf16(err).c_str(), L"A Day of Feb", MB_OK | MB_ICONERROR);
	}
	bool Core::checkResolution()
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
	bool Core::set_cursor()
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

	void Core::setActionGroup(std::string group_name, std::function<void()> group_function)
	{
		button_def->setActionGroup(group_name, group_function);
	}
	ActionPolicyManager* Core::getActionPolicyManager()
	{
		return ap_mgr.get();
	}
}
