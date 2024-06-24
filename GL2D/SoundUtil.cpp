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
	Result = FMOD::System_Create(&SoundSystem);

	if (Result != FMOD_OK)	
		exit(EXIT_FAILURE);

	SoundSystem->init(32, FMOD_INIT_NORMAL, ExtDvData);
	SoundSystem->createDSPByType(FMOD_DSP_TYPE_LOWPASS, &LowPass);

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

void SoundUtil::Update() {
	SoundSystem->update();
}

void SoundUtil::PlaySound(std::string SoundName, std::string ChannelName, unsigned int Ms) {
	auto ChannelIter = LoadedChannelList.find(ChannelName);

	SoundSystem->playSound(LoadedSoundList.find(SoundName)->second, 0, false, &ChannelIter->second);

	if (Ms > 0)
		ChannelIter->second->setPosition(Ms, FMOD_TIMEUNIT_MS);
}

void SoundUtil::PauseSound(std::string ChannelName, bool Flag) {
	LoadedChannelList.find(ChannelName)->second->setPaused(Flag);
}

void SoundUtil::StopSound(std::string ChannelName) {
	LoadedChannelList.find(ChannelName)->second->stop();
}

unsigned int SoundUtil::GetLength(std::string SoundName) {
	unsigned int Length{};
	LoadedSoundList.find(SoundName)->second->getLength(&Length, FMOD_TIMEUNIT_MS);

	return Length;
}

unsigned int SoundUtil::GetPlayTime(std::string ChannelName) {
	unsigned int Position{};
	LoadedChannelList.find(ChannelName)->second->getPosition(&Position, FMOD_TIMEUNIT_MS);

	return Position;
}

void SoundUtil::SetPlaySpeed(std::string ChannelName, float PlaySpeed) {
	LoadedChannelList.find(ChannelName)->second->setPitch(PlaySpeed);
}

void SoundUtil::SetFreqCutOff(std::string ChannelName, float Frequency) {
	LowPass->setParameterFloat(FMOD_DSP_LOWPASS_CUTOFF, Frequency);
	LoadedChannelList.find(ChannelName)->second->addDSP(0, LowPass);
}

void SoundUtil::UnSetFreqCutOff(std::string ChannelName) {
	LoadedChannelList.find(ChannelName)->second->removeDSP(LowPass);
}

void SoundUtil::SetBeatDetect(std::string ChannelName) {
	SoundSystem->createDSPByType(FMOD_DSP_TYPE_FFT, &BeatDetector);
	LoadedChannelList.find(ChannelName)->second->addDSP(0, BeatDetector);
}

void SoundUtil::UnSetBeatDetect(std::string ChannelName) {
	LoadedChannelList.find(ChannelName)->second->removeDSP(BeatDetector);
}

float SoundUtil::DetectBeat(float Threshold) {
	FMOD_DSP_PARAMETER_FFT* FFT = nullptr;
	BeatDetector->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void**)&FFT, 0, 0, 0);

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