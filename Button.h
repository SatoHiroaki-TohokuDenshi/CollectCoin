#pragma once
#include "Engine/GameObject.h"
#include <array>

//前方宣言
class Text;

//Buttonを管理するクラス
class Button : public GameObject {
private:
	//画像管理変数
	std::array<int, 2> hPict_{ -1, -1 };
	XMFLOAT3 position_;		// 表示位置
	XMFLOAT3 pictSize_;		// 画像サイズ

	Text* pText_;			// 文字クラス
	std::string txt_;		// 表示文字列
public:
	//コンストラクタ
	Button(GameObject* parent);

	//デストラクタ
	~Button();

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
	// 読み込み
	void LoadFile(std::string fileName);

	// 位置の設定
	// 引数：左上からのピクセル数
	void SetButtonPosition(int x, int y);

	// マウスがホバーしているか
	bool IsHovered();

	// 表示文字列の設定
	void SetText(std::string t);

public:
	bool isClicked();
};
