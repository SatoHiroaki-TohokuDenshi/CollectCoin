#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "State/StateManager.h"

#include "Engine/Camera.h"

namespace {
	const float SPEED_UNIT_XZ = 0.1f;
	const float SPEED_UNIT_Y = 0.02f;
}

//コンストラクタ
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), hModel_(-1), pStage_(nullptr)
	, isOnFloor_(true), frame_(0), moveCount_(0, 0, 0)
	, pManager_(new StateManager)
{
}

//デストラクタ
Player::~Player() {

}

//初期化
void Player::Initialize() {
	//モデルデータのロード
	hModel_ = Model::Load("Model\\TestPlayer.fbx");
	assert(hModel_ >= 0);

	pStage_ = FindObject("Stage");

	SphereCollider* collision = new SphereCollider(XMFLOAT3(0.5f, 0.58f, 0.5f), 0.1f);
	AddCollider(collision);
}

//更新
void Player::Update() {
	isOnFloor_ = false;
	Collision(pStage_);
	if (!isOnFloor_)
		pManager_->SetStateAir();

	//状態の更新
	pManager_->UpdateState();

	//状態によって処理を分岐
	pManager_->Action(moveCount_);

	//位置を更新
	UpdatePosition();
	Camera::SetPosition(XMFLOAT3(transform_.position_.x, transform_.position_.y, transform_.position_.z - 1.0f));
	Camera::SetTarget(transform_.position_);
}

//描画
void Player::Draw() {
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Player::Release() {

}

//何かに当たった
void Player::OnCollision(GameObject* pTarget) {
	if (pTarget->GetObjectName() == "Stage") {
		//上昇中なら終了
		if (moveCount_.y > 0)
			return;
		if (moveCount_.y == 0)
			isOnFloor_ = true;
		if (moveCount_.y < 0) {
			pManager_->SetStateLand();
			moveCount_ = { 0,0,0 };
			isOnFloor_ = true;
		}
	}
}

void Player::UpdatePosition() {
	transform_.position_.x += SPEED_UNIT_XZ * moveCount_.x;
	transform_.position_.z += SPEED_UNIT_XZ * moveCount_.z;
	if (moveCount_.y == 0)
		return;
	if (moveCount_.y > 0) {
		for (int i = 0; i < moveCount_.y; i++) {
			transform_.position_.y += SPEED_UNIT_Y;
		}
	}
	else {
		for (int i = 0; i < abs(moveCount_.y); i++) {
			transform_.position_.y -= SPEED_UNIT_Y;
			Collision(pStage_);
			if (moveCount_.y == 0)
				break;
		}
	}
}
