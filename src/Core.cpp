#include "include/ems_engine/Core.h"
#include "Output/Audio.h"
#include "Output/Render.h"
#include "Output/RenderManager.h"
#include "Resource/jsonManager.h"
#include "Scene/sceneManager.h"
#include "Action/ActionBehavior.h"
#include "Action/ActionPolicyManager.h"
#include "Resource/ResourceManager.h"
#include "Input/InputManager.h"
#include "Common/idConverter.h"
#include "Common/Event.h"
#include "Common/enum.h"
#include <SDL3/SDL_ttf.h>
#include <SDL_image.h>
#include <SDL3/SDL.h>
#include <iostream>
namespace ems_engine
{

	// Definition of the opaque SDLData declared in the header
	struct Core::SDLData
	{
		SDL_DisplayID Display;
		SDL_Event event{};
		const SDL_DisplayMode* displayMode;
		SDLData() : Display(0), event{}, displayMode(nullptr) {}
	};

	Core::Core()
	{
		windowWidth = 0;
		windowHeight = 0;
		render_sys = nullptr;
		sound_sys = nullptr;
		input_mgr = nullptr;
		button_def = nullptr;
		ap_mgr = nullptr;
		sdl_data = std::make_unique<SDLData>();
		state = std::make_unique<EngineState>();
	}
	Core::~Core()
	{
		ui_mgr->deleteAll();
		if (render_sys != nullptr)
		{
			render_sys->endWindow();//關閉視窗
			render_sys->stopTextInput();//停止文字輸入
		}
		//TTF_CloseFont(big_font);//釋放big_font字體
		//TTF_CloseFont(font);//釋放font字體
		if (render_sys->getRenderer() != nullptr)
			SDL_DestroyRenderer(render_sys->getRenderer());//釋放renderer渲染器
		rc_mgr->clearFontCache();
		TTF_Quit();//釋放SDL_ttf
		SDL_Quit();//釋放SDL
		sound_sys->cleanupAudio();
		//ma_sound_uninit(&bgm_1);     // 銷毀音效
		//ma_engine_uninit(&music_engine);   // 銷毀引擎
	}
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
		rc_mgr = std::make_unique<ResourceManager>();
		ui_mgr = std::make_unique<SceneManager>(rc_mgr.get(), render_sys.get());
		input_mgr = std::make_unique<InputManager>(button_def.get(), ui_mgr.get(), render_sys.get());
		
		//id_converter = std::make_unique<ID_Converter>();
		sound_sys = std::make_unique<audio>();
		sound_sys->initAudio();
		render_mgr->setRecouceManagerPtr(rc_mgr.get());

		ui_mgr->setTargetSceneID("global");
		ui_mgr->UpdateScene();
		ui_mgr->setTargetSceneID("home");
		ui_mgr->UpdateScene();

		if (custom_init)
		{
			custom_init(this);
		}
		app = true;
		return true;
	}
	void Core::run(std::function<bool(Core*)> custom_update)
	{

		try
		{
			while (app)
			{
				handleEvents();
				if (custom_update)
				{
					app = custom_update(this);
				}
				if (!render_mgr->runRender(*render_sys.get(), *ui_mgr.get()))
				{
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "A Day of Feb", "您的遊戲檔案不完整，無法正確載入材質。\n請嘗試將遊戲重新安裝，若嘗試後此情況扔然持續發生，請聯絡Evil Month Studio團隊。\n聯絡我們:evilmonth.studio@gmail.com", render_sys->getSDLWindow());
					
					app = false;
				}
				if (ui_mgr->getSceneID() == "game_exit")
				{
					app = false;
				}
			}
		}
		catch (const json::exception& e)
		{
			std::cout << "[ERROR]:" << e.id << " | " << e.what() << std::endl;
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "A Day of Feb", "遊戲發生致命錯誤，請聯繫開發團隊。\nA fatal error has occurred in the game. Please contact the developer.", NULL);
			return;
		}
		catch (const std::exception& e)
		{
			std::cout << "[ERROR]:" << e.what() << std::endl;
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "A Day of Feb", "遊戲發生致命錯誤，請聯繫開發團隊。\nA fatal error has occurred in the game. Please contact the developer.", NULL);
			return;
		}

		
	}
	void Core::handleEvents()
	{
		
		while (SDL_PollEvent(&sdl_data->event))
		{
			EngineEvent(sdl_data->event, *render_sys.get(), *ui_mgr.get());
		}
		input_mgr->InputRefresh();
		if (state->isRefreshText)
		{
			//render_mgr->refreshUIText("zh_tw", *ui_mgr.get(), render_sys->getRenderer(), *id_converter.get());
			state->isRefreshText = false;
		}
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

		//sound_sys = std::make_unique<audio>();
		
		sdl_data->Display = SDL_GetPrimaryDisplay();
		sdl_data->displayMode = SDL_GetCurrentDisplayMode(sdl_data->Display);

		if (sdl_data->displayMode == 0)
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
		if (sdl_data->displayMode->w < 1024 || sdl_data->displayMode->h < 768)
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "A Day of Feb", "您的顯示器解析度低於遊戲所支援之最低解析度(1024*768)。", NULL);
			//MessageBoxW(nullptr, L"您的顯示器解析度低於遊戲所支援之最低解析度(1024*768)。", L"A Day of Feb", MB_OK | MB_ICONERROR);
			return false;
		}
		std::cout << "[DEBUG]:Screen Resolution:" << windowWidth << "x" << windowHeight << std::endl;
		windowWidth = sdl_data->displayMode->w / 3 * 2;
		windowHeight = sdl_data->displayMode->h / 3 * 2;
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
	SceneManager* Core::getUIManager()
	{
		return ui_mgr.get();
	}
}
