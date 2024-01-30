#pragma once
#include "Engine/GameObject.h"

//前方宣言
class Text;

//Timerを管理するクラス
class Timer : public GameObject {
private:
	//1秒間のフレーム数
	const int FPS = GetPrivateProfileInt("GAME", "Fps", 60, ".\\setup.ini");

	int second_;		// タイマーの秒数
	int frame_;			// 総フレーム数
	bool isActive_;		// タイマーは起動されているか
	bool isFinish_;		// タイマーが終わっているか
	bool isDisplay_;	// 画面に表示を行うか

	Text* pText_;		// タイマー表示用の文字クラス
	struct DisplayPosition {
		int x;
		int y;
		DisplayPosition() :x(0), y(0) {};
		DisplayPosition(int _x, int _y) 
			:x(_x), y(_y) {};
	}* displayPos_;		//タイマーの表示位置

public:
	//コンストラクタ
	Timer(GameObject* parent);

	//デストラクタ
	~Timer();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

//新規関数群
public:
	/// <summary>タイマーを秒数で設定</summary>
/// <param name="sec">秒数</param>
	void SetTimer(int sec);
	/// <summary>タイマーを分秒で設定</summary>
	/// <param name="min">分</param>
	/// <param name="sec">秒</param>
	void SetTimer(int min, int sec);

	/// <summary>タイマーをスタート</summary>
	void StartTimer();

	/// <summary>タイマーが終わっているか</summary>
	/// <returns>終わっているならtrue</returns>
	bool IsFinish();

	/// <summary>画面表示を有効にする</summary>
	void SetDisplayEnable();
	/// <summary>画面表示を無効にする</summary>
	void SetDisplayDisable();

	/// <summary>表示位置を設定(左上原点)</summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	void SetTimerPos(int x, int y);
};
