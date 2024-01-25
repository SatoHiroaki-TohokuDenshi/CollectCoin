#include <xaudio2.h>
#include <vector>
#include "Audio.h"

#define SAFE_DELETE_ARRAY(p) if(p){delete[] p; p = nullptr;}

namespace Audio {
	//XAudio本体
	IXAudio2* pXAudio = nullptr;

	//マスターボイス
	IXAudio2MasteringVoice* pMasteringVoice = nullptr;

	//ファイル毎に必要な情報
	struct AudioData {
		//サウンド情報
		XAUDIO2_BUFFER buf = {};

		//ソースボイス
		IXAudio2SourceVoice** pSourceVoice = nullptr;

		//同時再生最大数
		int svNum = 1;

		//ファイル名
		std::string fileName;
	};
	std::vector<AudioData>	audioDatas;
}

//初期化
void Audio::Initialize() {
	HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);

	XAudio2Create(&pXAudio);
	pXAudio->CreateMasteringVoice(&pMasteringVoice);

}

//サウンドファイル(.wav）をロード
int Audio::Load(std::string fileName, bool isLoop, int svNum) {
	//すでに同じファイルを使ってないかチェック
	for (int i = 0; i < audioDatas.size(); i++) {
		if (audioDatas[i].fileName == fileName) {
			return i;
		}
	}

	BOOL res = TRUE;

	//チャンク構造体
	struct Chunk {
		char	id[5] =""; 			// ID
		unsigned int	size = 0;	// サイズ
	};

	//ファイルを開く
	HANDLE hFile;
	hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD dwBytes = 0;

	Chunk riffChunk = { 0 };
	res = ReadFile(hFile, &riffChunk.id, 4, &dwBytes, NULL);
	if (res == FALSE) {
		return -1;
	}
	res = ReadFile(hFile, &riffChunk.size, 4, &dwBytes, NULL);
	if (res == FALSE) {
		return -1;
	}

	char wave[4] = "";
	res = ReadFile(hFile, &wave, 4, &dwBytes, NULL);
	if (res == FALSE) {
		return -1;
	}

	Chunk formatChunk = { 0 };
	while (formatChunk.id[0] != 'f') {
		res = ReadFile(hFile, &formatChunk.id, 4, &dwBytes, NULL);
	}
	res = ReadFile(hFile, &formatChunk.size, 4, &dwBytes, NULL);
	if (res == FALSE) {
		return -1;
	}


	//フォーマットを読み取る
	//https://learn.microsoft.com/ja-jp/windows/win32/api/mmeapi/ns-mmeapi-waveformatex
	WAVEFORMATEX fmt{};
	res = res = ReadFile(hFile, &fmt.wFormatTag, 2, &dwBytes, NULL);	// 形式
	if (res == FALSE) {
		return -1;
	}
	res = ReadFile(hFile, &fmt.nChannels, 2, &dwBytes, NULL);			// チャンネル（モノラル/ステレオ）
	if (res == FALSE) {
		return -1;
	}
	res = ReadFile(hFile, &fmt.nSamplesPerSec, 4, &dwBytes, NULL);		// サンプリング数
	if (res == FALSE) {
		return -1;
	}
	res = ReadFile(hFile, &fmt.nAvgBytesPerSec, 4, &dwBytes, NULL);		// 1秒あたりのバイト数
	if (res == FALSE) {
		return -1;
	}
	res = ReadFile(hFile, &fmt.nBlockAlign, 2, &dwBytes, NULL);			// ブロック配置
	if (res == FALSE) {
		return -1;
	}
	res = ReadFile(hFile, &fmt.wBitsPerSample, 2, &dwBytes, NULL);		// サンプル当たりのビット数
	if (res == FALSE) {
		return -1;
	}


	//波形データの読み込み
	Chunk data = { 0 };
	while (true) {
		//次のデータのIDを調べる
		res = ReadFile(hFile, &data.id, 4, &dwBytes, NULL);
		if (res == FALSE) {
			return -1;
		}

		//「data」だったらループを抜けて次に進む
		if (strcmp(data.id, "data") == 0)
			break;

		//それ以外の情報ならサイズ調べて読み込む→使わない
		else {
			//サイズ調べて
			res = ReadFile(hFile, &data.size, 4, &dwBytes, NULL);
			char* pBuffer = new char[data.size];

			//無駄に読み込む
			res = ReadFile(hFile, pBuffer, data.size, &dwBytes, NULL);
			if (res == FALSE) {
				return -1;
			}
		}
	}

	//データチャンクのサイズを取得
	res = ReadFile(hFile, &data.size, 4, &dwBytes, NULL);

	//波形データを読み込む
	char* pBuffer = new char[data.size];
	res = ReadFile(hFile, pBuffer, data.size, &dwBytes, NULL);
	if (res == FALSE) {
		return -1;
	}
	CloseHandle(hFile);


	AudioData ad;

	ad.fileName = fileName;

	ad.buf.pAudioData = (BYTE*)pBuffer;
	ad.buf.Flags = XAUDIO2_END_OF_STREAM;

	if (isLoop)	ad.buf.LoopCount = XAUDIO2_LOOP_INFINITE;

	ad.buf.AudioBytes = data.size;


	ad.pSourceVoice = new IXAudio2SourceVoice * [svNum];

	for (int i = 0; i < svNum; i++) {
		pXAudio->CreateSourceVoice(&ad.pSourceVoice[i], &fmt);
	}
	ad.svNum = svNum;
	audioDatas.push_back(ad);

	//SAFE_DELETE_ARRAY(pBuffer);

	return (int)audioDatas.size() - 1;
}

//再生
void Audio::Play(int ID) {
	for (int i = 0; i < audioDatas[ID].svNum; i++) {
		XAUDIO2_VOICE_STATE state;
		audioDatas[ID].pSourceVoice[i]->GetState(&state);

		if (state.BuffersQueued == 0) {
			audioDatas[ID].pSourceVoice[i]->SubmitSourceBuffer(&audioDatas[ID].buf);
			audioDatas[ID].pSourceVoice[i]->Start();
			break;
		}
	}
}


void Audio::Stop(int ID) {
	for (int i = 0; i < audioDatas[ID].svNum; i++) {
		audioDatas[ID].pSourceVoice[i]->Stop();
		audioDatas[ID].pSourceVoice[i]->FlushSourceBuffers();
	}
}

//シーンごとの解放
void Audio::Release() {
	for (int i = 0; i < audioDatas.size(); i++) {
		for (int j = 0; j < audioDatas[i].svNum; j++) {
			audioDatas[i].pSourceVoice[j]->DestroyVoice();
		}
		SAFE_DELETE_ARRAY(audioDatas[i].buf.pAudioData);
	}
	audioDatas.clear();
}

//本体の解放
void Audio::AllRelease() {
	CoUninitialize();
	if (pMasteringVoice) {
		pMasteringVoice->DestroyVoice();
	}
	pXAudio->Release();
}
