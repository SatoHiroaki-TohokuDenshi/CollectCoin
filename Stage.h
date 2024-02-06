#pragma once
#include <vector>
#include "Engine/GameObject.h"

//Stageを管理するクラス
class Stage : public GameObject {
private:
	int hModel_;    //モデル番号
	std::vector<std::vector<int>> map_;

public:
	//コンストラクタ
	Stage(GameObject* parent);

	//デストラクタ
	~Stage();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	int GetModelHandle() { return hModel_; }
};
