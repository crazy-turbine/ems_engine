#define MINIAUDIO_IMPLEMENTATION
#include "src/Output/Audio.h"



bool audio::initAudio()
{
    if (ma_engine_init(nullptr, &music_engine) != MA_SUCCESS)
    {
        std::cout << "音樂引擎初始失敗" << std::endl;
        MessageBoxW(nullptr, L"音樂引擎初始化失敗。/n", L"A Day of Feb", MB_OK | MB_ICONERROR);
        return false;
    }

    if (ma_sound_init_from_file(&music_engine, "res/music/the_end.wav", 0, nullptr, nullptr, &bgm_1) != MA_SUCCESS)
    {
        std::cout << "音樂讀取錯誤" << std::endl;
        MessageBoxW(nullptr, L"遊戲音樂檔案已損毀。/n", L"A Day of Feb", MB_OK | MB_ICONERROR);
        ma_engine_uninit(&music_engine);
        return false;
    }

    if (ma_engine_init(nullptr, &sound_engine) != MA_SUCCESS)
    {
        std::cout << "音效引擎初始失敗" << std::endl;
        MessageBoxW(nullptr, L"音效引擎初始化失敗。/n", L"A Day of Feb", MB_OK | MB_ICONERROR);
        ma_sound_uninit(&bgm_1);
        ma_engine_uninit(&music_engine);
        return false;
    }


    ma_sound_set_looping(&bgm_1, MA_TRUE);
    ma_sound_start(&bgm_1);

    audioInitialized = true;
    return true;
}

void audio::cleanupAudio()
{
    if (!audioInitialized) return;
    ma_engine_uninit(&sound_engine);
    ma_sound_uninit(&bgm_1);
    ma_engine_uninit(&music_engine);
    audioInitialized = false;
}

void audio::playButtonSound()
{
    ma_engine_play_sound(&sound_engine, sfx_1, NULL);
}