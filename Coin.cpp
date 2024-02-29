#include "Coin.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

#include "Player.h"

//コンストラクタ
Coin::Coin(GameObject* parent)
	:GameObject(parent, "Coin"), hModel_(-1) {

}

//デストラクタ
Coin::~Coin() {

}

//初期化
void Coin::Initialize() {
	//モデルデータのロード
	hModel_ = Model::Load("Model\\Coin.fbx");
	assert(hModel_ >= 0);

	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.6f);
	AddCollider(collision);
}

//更新
void Coin::Update() {
	transform_.rotate_.y += 1.0f;
}

//描画
void Coin::Draw() {
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Coin::Release() {

}

//何かに当たった
void Coin::OnCollision(GameObject* pTarget) {
	//当たったときの処理
	if (pTarget->GetObjectName() == "Player") {
		KillMe();
		((Player*)pTarget)->CountCoin();
	}
}
