#pragma once
#include "Engine/GameObject.h"

//前方宣言
class StateManager;
class CameraController;
class Text;

//Playerを管理するクラス
class Player : public GameObject {
private:
	int hModel_;	// モデル管理番号

	XMINT3 moveCount_;
	bool isOnFloor_;	// 床の上にいるか
	int frame_;			// 着地硬直用カウント変数
	GameObject* pStage_;

	//ステート管理
	StateManager* pManager_;

	//カメラ管理
	CameraController* pCamera_;

	//位置情報の更新
	void UpdatePosition();

	//コインのカウント
	int countCoin_;

	Text* pText;

public:
	//コンストラクタ
	Player(GameObject* parent);

	//デストラクタ
	~Player();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//何かに当たった
	//引数：pTarget 当たった相手
	void OnCollision(GameObject* pTarget) override;

	void CountCoin() { countCoin_++; };
};
