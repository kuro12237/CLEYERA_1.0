#pragma once
#include"Pch.h"
#include"LogManager.h"

struct ChunkHeader
{
	char id[4];
	int32_t size;
};

struct RiffHeader
{
	ChunkHeader chunk;
	char Type[4];
};

struct FormatChunk
{
	ChunkHeader chunk;
	WAVEFORMATEX fmt;
};

struct soundData
{
	WAVEFORMATEX wfex;
	BYTE* pBuffer;
	unsigned int bufferSize;
};

class AudioManager
{
public:


	static AudioManager* GetInstance();

	static void Initialize();

	static void Finalize();

	static uint32_t SoundLoadWave(const char* filename);

	static void SoundUnLoad();

	static void AudioPlayWave(uint32_t soundHandle);
	static void AudioStopWave(uint32_t soundHandle);

private:

	ComPtr<IXAudio2> xAudio=nullptr;
	IXAudio2MasteringVoice* masterVoice = nullptr;
	uint32_t soundDataCount_{};

	static const uint32_t kSoundDataMax = 64;
	IXAudio2SourceVoice* pSourcevoice[kSoundDataMax] = {};

	soundData soundData_[kSoundDataMax]{};
	bool InitializeFlag = false;

#pragma region Singleton
	AudioManager() = default;
	~AudioManager() = default;
	AudioManager(const AudioManager&) = delete;
	const AudioManager& operator=(const AudioManager&) = delete;
#pragma endregion
};

