#pragma once
#include "Engine/GameObject.h"

class Button;

//タイトルシーンを管理するクラス
class TitleScene : public GameObject {
private:
	int hPict_;    //画像番号
	Button* pButton_;
	bool isMoveScene_;
	int hBlack_;
	int frame_;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//シーン遷移
	void MoveNextScene();
};
