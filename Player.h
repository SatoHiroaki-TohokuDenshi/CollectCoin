#pragma once
#include "Engine/GameObject.h"

//Playerを管理するクラス
class Player : public GameObject {
private:
	int hModel_;	// モデル管理番号

	//プレイヤーの状態
	enum class ActionState {
		IDLE = 0,	// 待機
		MOVE,		// 移動
		AIR,		// 空中
		LAND,		// 着地
	} state_;

	int moveCountX_;	// Xの移動量
	int moveCountY_;	// Yの移動量
	int moveCountZ_;	// Zの移動量
	bool isOnFloor_;	// 床の上にいるか
	int frame_;			// 着地硬直用カウント変数
	GameObject* pStage_;

	//状態の更新
	void UpdateState();
	//待機
	void UpdateIdle();
	//移動
	void UpdateMove();
	//空中
	void UpdateAir();
	//着地
	void UpdateLand();

	//位置情報の更新
	void UpdatePosition();

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
};
