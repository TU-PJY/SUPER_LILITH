#include "SoundUtil.h"
#include <iostream>

std::vector<float>FFTdata(FFT_SIZE);

struct FileNameAndOption {
	const char* FileName;
	FMOD_MODE Option;
};
FileNameAndOption FNO;


// list sounds to load
std::unordered_map<std::string, FileNameAndOption> SoundList
{

};

// list channels to load
std::vector<std::string> ChannelList
{

};


void SoundUtil::Init() {
	f_result = FMOD::System_Create(&SoundSystem);

	if (f_result != FMOD_OK)	
		exit(EXIT_FAILURE);

	SoundSystem->init(32, FMOD_INIT_NORMAL, extdvdata);

	LoadSoundFromList();
	LoadChannelFromList();
}

void SoundUtil::LoadSoundFromList() {
	for (auto& [SoundName, Struct] : SoundList) {
		FMOD::Sound* sound;
		SoundSystem->createSound(Struct.FileName, Struct.Option, 0, &sound);
		LoadedSoundList.insert(std::pair(SoundName, sound));
	}
}

void SoundUtil::LoadChannelFromList() {
	for (auto& s : ChannelList) {
		FMOD::Channel* channel;
		LoadedChannelList.insert(std::pair(s, channel));
	}
}

void SoundUtil::PlaySound(std::string SoundName, std::string ChannelName, unsigned int Sec) {
	SoundSystem->playSound(LoadedSoundList.find(SoundName)->second, 0, false, &LoadedChannelList.find(ChannelName)->second);
	if(Sec > 0)
		LoadedChannelList.find(ChannelName)->second->setPosition(Sec * 1000, FMOD_TIMEUNIT_MS);
}

void SoundUtil::StopSound(std::string ChannelName) {
	LoadedChannelList.find(ChannelName)->second->stop();
}

void SoundUtil::SetBeatDetectChannel(std::string ChannelName) {
	SoundSystem->createDSPByType(FMOD_DSP_TYPE_FFT, &FDsp);
	LoadedChannelList.find(ChannelName)->second->addDSP(0, FDsp);
}

float SoundUtil::DetectBeat(float Threshold) {
	SoundSystem->update();

	FMOD_DSP_PARAMETER_FFT* FFT = nullptr;
	FDsp->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void**)&FFT, 0, 0, 0);

	if (FFT) {
		int NumChannels = FFT->numchannels;

		if (NumChannels > 0) {
			memcpy(FFTdata.data(), FFT->spectrum[0], FFT_SIZE * sizeof(float));

			float BassEnergy = 0.0f;

			for (int i = 0; i < 10; ++i)
				BassEnergy += FFTdata[i];

			if (BassEnergy > Threshold) 
				return BassEnergy;
		}
	}

	return 0;
}