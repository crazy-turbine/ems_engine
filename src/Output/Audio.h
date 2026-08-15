#pragma once
#include "third_party/miniaudio.h"
#include <iostream>
namespace ems_engine
{

	class audio
	{
	public:
		bool initAudio();
		void cleanupAudio();
		void playButtonSound();
	private:
		ma_engine music_engine;
		ma_sound bgm_1;
		ma_engine sound_engine;
		const char* sfx_1 = "res/sound/button_sound.wav";
		bool audioInitialized = false;
	};
}
