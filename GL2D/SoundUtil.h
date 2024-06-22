#pragma once
#include "fmod.hpp"
#include "fmod_errors.h"
#include <unordered_map>
#include <string>

#define FFT_SIZE 1024 // FFT Å©±â

class SoundUtil {
private:
	std::unordered_map<std::string, FMOD::Sound*> LoadedSoundList;
	std::unordered_map<std::string, FMOD::Channel*> LoadedChannelList;
	FMOD::System* SoundSystem{};
	FMOD::DSP* FDsp{};

	FMOD_RESULT f_result{};
	void* extdvdata{};

public:
	void Init();
	void LoadSoundFromList();
	void LoadChannelFromList();
	void PlaySound(std::string SoundName, std::string ChannelName, unsigned int Sec =0);
	void StopSound(std::string ChannelName);
	void SetBeatDetectChannel(std::string ChannelName);
	float DetectBeat(float Threshold);
};
extern SoundUtil soundUtil;
