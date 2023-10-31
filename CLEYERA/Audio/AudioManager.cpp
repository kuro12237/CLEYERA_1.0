#include"AudioManager.h"

AudioManager* AudioManager::GetInstance()
{
	static AudioManager instance;
	return &instance;
}

void AudioManager::Initialize()
{
	HRESULT hr{};
	if (!AudioManager::GetInstance()->InitializeFlag)
	{
		AudioManager::GetInstance()->InitializeFlag = true;
	}
	else {
		LogManager::Log("Audio::Initialize_ERROR\n");

		assert(0);
	}

	hr = XAudio2Create(&AudioManager::GetInstance()->xAudio, 0, XAUDIO2_DEFAULT_PROCESSOR);
	assert(SUCCEEDED(hr));
	//masterのボイスの作成
	hr = AudioManager::GetInstance()->xAudio->CreateMasteringVoice(&AudioManager::GetInstance()->masterVoice);
	assert(SUCCEEDED(hr));
}

void AudioManager::Finalize()
{
	AudioManager::GetInstance()->xAudio.Reset();
}

uint32_t AudioManager::SoundLoadWave(const char* filename)
{
	//HRESULT result{};
	AudioManager::GetInstance()->soundDataCount_++;
	ifstream file;
	file.open(filename, std::ios_base::binary);
	assert(SUCCEEDED(file.is_open()));

	//fileがRiffに一致するかTypeがWaveか
	RiffHeader riff = {};
	file.read((char*)&riff, sizeof(riff));
	if (strncmp(riff.chunk.id,"RIFF",4) != 0)
	{assert(0);}
	if (strncmp(riff.Type, "WAVE", 4) != 0)
	{assert(0);}

	//Formatのチャンク読み込み
	FormatChunk format = {};
	//チャンクヘッダーの確認
	file.read((char*)&format, sizeof(ChunkHeader));
	if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
		assert(0);
	}

	assert(format.chunk.size <= sizeof(format.fmt));
	file.read((char*)&format.fmt, format.chunk.size);
	
	//Dataチャンクの読み込み
	ChunkHeader data = {};
	file.read((char*)&data, sizeof(data));
	if (strncmp(data.id,"JUNK",4) == 0){

		file.seekg(data.size, ios_base::cur);
		file.read((char*)&data, sizeof(data));
	}
	if (strncmp(data.id, "data", 4) != 0)
	{assert(0);}
	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);
	file.close();
	//代入
	AudioManager::GetInstance()->soundData_[AudioManager::GetInstance()->soundDataCount_].wfex = format.fmt;
	AudioManager::GetInstance()->soundData_[AudioManager::GetInstance()->soundDataCount_].pBuffer = reinterpret_cast<BYTE*>(pBuffer);
	AudioManager::GetInstance()->soundData_[AudioManager::GetInstance()->soundDataCount_].bufferSize = data.size;

	return AudioManager::GetInstance()->soundDataCount_;
}

void AudioManager::SoundUnLoad()
{
	for (int i = AudioManager::GetInstance()->soundDataCount_; i >0 ; i--)
	{
		delete[] AudioManager::GetInstance()->soundData_[i].pBuffer;
		AudioManager::GetInstance()->soundData_[i].pBuffer = 0;
		AudioManager::GetInstance()->soundData_[i].bufferSize = 0;
		AudioManager::GetInstance()->soundData_[i].wfex = {};
	}
	AudioManager::GetInstance()->soundDataCount_ = 0;
}

void AudioManager::AudioPlayWave(uint32_t soundHandle)
{
	HRESULT result{};
 
	result = AudioManager::GetInstance()->xAudio->CreateSourceVoice(&AudioManager::GetInstance()->pSourcevoice[soundHandle], &AudioManager::GetInstance()->soundData_[soundHandle].wfex);
	assert(SUCCEEDED(result));

	XAUDIO2_BUFFER buf{};
	buf.pAudioData = AudioManager::GetInstance()->soundData_[soundHandle].pBuffer;
	buf.AudioBytes = AudioManager::GetInstance()->soundData_[soundHandle].bufferSize;
	buf.Flags = XAUDIO2_END_OF_STREAM;

	result = AudioManager::GetInstance()->pSourcevoice[soundHandle]->SubmitSourceBuffer(&buf);
	result = AudioManager::GetInstance()->pSourcevoice[soundHandle]->Start();

	assert(SUCCEEDED(result));
}

void AudioManager::AudioStopWave(uint32_t soundHandle)
{
	HRESULT result{};
	result = AudioManager::GetInstance()->pSourcevoice[soundHandle]->Stop();

	assert(SUCCEEDED(result));
}
