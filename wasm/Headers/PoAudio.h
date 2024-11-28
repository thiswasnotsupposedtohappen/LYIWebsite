IXAudio2 *xaudio2;
IXAudio2MasteringVoice *mastervoice;
struct Audio
{
	Audio()
	{
		xaudio2 = 0;
		mastervoice = 0;

	}
	short Initialize()
	{
		HRESULT hr;
#ifdef _XBOX
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif
#ifndef _XBOX
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif
		xaudio2 = NULL;
		hr = XAudio2Create(&xaudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
		if (hr != S_OK){ print("Audio: Failed to create device \n"); return 1; }
		hr = xaudio2->CreateMasteringVoice(&mastervoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL);
		if (hr != S_OK){ print("Audio: Failed to create master voice \n"); return 1; }
		print("Audio: Initialized \n");
		return 0;
	}
	~Audio()
	{
		if (xaudio2)xaudio2->Release();
	}
};
struct Sound
{
protected:
	IXAudio2SourceVoice* sourcevoice;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;
	HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition)
	{
		HRESULT hr = S_OK;
		if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
			return HRESULT_FROM_WIN32(GetLastError());

		DWORD dwChunkType;
		DWORD dwChunkDataSize;
		DWORD dwRIFFDataSize = 0;
		DWORD dwFileType;
		DWORD bytesRead = 0;
		DWORD dwOffset = 0;

		while (hr == S_OK)
		{
			DWORD dwRead;
			if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());
			if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());
			switch (dwChunkType)
			{
			case fourccRIFF:
				dwRIFFDataSize = dwChunkDataSize;
				dwChunkDataSize = 4;
				if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
					hr = HRESULT_FROM_WIN32(GetLastError());
				break;

			default:
				if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
					return HRESULT_FROM_WIN32(GetLastError());
			}

			dwOffset += sizeof(DWORD)* 2;

			if (dwChunkType == fourcc)
			{
				dwChunkSize = dwChunkDataSize;
				dwChunkDataPosition = dwOffset;
				return S_OK;
			}

			dwOffset += dwChunkDataSize;

			if (bytesRead >= dwRIFFDataSize) return S_FALSE;

		}
		return S_OK;
	}
	HRESULT ReadChunkData(HANDLE hFile, void * _buffer, DWORD _buffersize, DWORD _bufferoffset)
	{
		HRESULT hr = S_OK;
		if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, _bufferoffset, NULL, FILE_BEGIN))
			return HRESULT_FROM_WIN32(GetLastError());
		DWORD dwRead;
		if (0 == ReadFile(hFile, _buffer, _buffersize, &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());
		return hr;
	}
public:
	short Initialize(char* _filename)
	{
		char filepath[256];
		strcpy_s(filepath, AUDIOPATH);
		strcat_s(filepath, _filename);
		HANDLE hFile;		
		hFile = CreateFile(filepath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == 0x00000000){ print("Audio: Sound: file not found (%s) \n", _filename); return 1; }
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
		if (dwChunkSize == 0 && dwChunkPosition == 0){ print("Audio: Sound: Invalid file (%s) \n",_filename); return 1; }
		DWORD filetype;
		ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
		FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
		BYTE * pDataBuffer = new BYTE[dwChunkSize];
		ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);
		buffer.AudioBytes = dwChunkSize;
		buffer.pAudioData = pDataBuffer;
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
		DeleteFile(_filename);
		print("Audio: Sound: Initialized (%s) \n", _filename);
		return 0;
	}
	void Play()
	{
		
		xaudio2->CreateSourceVoice(&sourcevoice, (WAVEFORMATEX*)&wfx, 0, XAUDIO2_DEFAULT_FREQ_RATIO, NULL, NULL, NULL);
		sourcevoice->SubmitSourceBuffer(&buffer);
		sourcevoice->Start(0, XAUDIO2_COMMIT_NOW);
	}
	void SetFrequency(float _ratio)
	{
		sourcevoice->SetFrequencyRatio(_ratio);
	}
	void SetVolume(float _volume)
	{
		sourcevoice->SetVolume(_volume);
	}
};