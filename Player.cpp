#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

#include "Engine/Camera.h"

namespace {
	const float SPEED_UNIT_XZ = 0.1f;
	const float SPEED_UNIT_Y = 0.02f;
}

//コンストラクタ
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), hModel_(-1), pStage_(nullptr)
	, state_(ActionState::IDLE), isOnFloor_(true), frame_(0)
	, moveCountX_(0), moveCountY_(0), moveCountZ_(0)
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

	SphereCollider* collision = new SphereCollider(XMFLOAT3(0.5f, 0.6f, 0.5f), 0.1f);
	AddCollider(collision);
}

//更新
void Player::Update() {
	//状態の更新
	UpdateState();

	//状態によって処理を分岐
	switch (state_) {
	case Player::ActionState::IDLE:
		UpdateIdle();
		break;
	case Player::ActionState::MOVE:
		UpdateMove();
		break;
	case Player::ActionState::AIR:
		UpdateAir();
		break;
	case Player::ActionState::LAND:
		UpdateLand();
		break;
	}

	//位置を更新
	UpdatePosition();
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
		if (moveCountY_ < 0) {
			state_ = ActionState::LAND;
			moveCountX_ = 0;
			moveCountY_ = 0;
			moveCountZ_ = 0;
			isOnFloor_ = true;
		}
	}
}

//状態の更新
void Player::UpdateState() {
	//着地状態は内部で更新
	if (state_ == ActionState::LAND) {
		return;
	}
	//床の上にいない
	if (!isOnFloor_) {
		state_ = ActionState::AIR;
		return;
	}
	//スペースバー
	if (Input::IsKeyDown(DIK_SPACE)) {
		moveCountY_ = 30;
		isOnFloor_ = false;
		state_ = ActionState::AIR;
		return;
	}
	//WASDキー
	if (Input::IsKey(DIK_W) || Input::IsKey(DIK_A) ||
		Input::IsKey(DIK_S) || Input::IsKey(DIK_D)) {
		state_ = ActionState::MOVE;
		return;
	}

	//何も入力が無かったら待機
	state_ = ActionState::IDLE;
}

//待機
void Player::UpdateIdle() {
	moveCountX_ = 0;
	moveCountY_ = 0;
	moveCountZ_ = 0;
}

//移動
void Player::UpdateMove() {
	moveCountX_ = 0;
	moveCountZ_ = 0;

	if (Input::IsKey(DIK_D)) {
		moveCountX_ += 2;
	}
	if (Input::IsKey(DIK_A)) {
		moveCountX_ -= 2;
	}
	if (Input::IsKey(DIK_W)) {
		moveCountZ_ += 2;
	}
	if (Input::IsKey(DIK_S)) {
		moveCountZ_ -= 2;
	}

	//左コントロールが押されていればダッシュ
	if (Input::IsKey(DIK_LCONTROL)) {
		moveCountX_ *= 2;
		moveCountZ_ *= 2;
	}
}

//空中
void Player::UpdateAir() {
	moveCountX_ = 0;
	moveCountZ_ = 0;

	if (Input::IsKey(DIK_D)) {
		moveCountX_ += 1;
	}
	if (Input::IsKey(DIK_A)) {
		moveCountX_ -= 1;
	}
	if (Input::IsKey(DIK_W)) {
		moveCountZ_ += 1;
	}
	if (Input::IsKey(DIK_S)) {
		moveCountZ_ -= 1;
	}

	moveCountY_ -= 2;
}

//着地
void Player::UpdateLand() {
	if (frame_ < 30) {
		frame_++;
		return;
	}
	frame_ = 0;
	state_ = ActionState::IDLE;
}

void Player::UpdatePosition() {
	transform_.position_.x += SPEED_UNIT_XZ * moveCountX_;
	transform_.position_.z += SPEED_UNIT_XZ * moveCountZ_;
	if (moveCountY_ == 0)
		return;
	if (moveCountY_ > 0) {
		for (int i = 0; i < moveCountY_; i++) {
			transform_.position_.y += SPEED_UNIT_Y;
		}
	}
	else {
		for (int i = 0; i < abs(moveCountY_); i++) {
			transform_.position_.y -= SPEED_UNIT_Y;
			Collision(pStage_);
			if (state_ == ActionState::LAND)
				break;
		}
	}
}
