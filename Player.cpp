#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

//コンストラクタ
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), hModel_(-1) , state_(ActionState::IDLE)
	, velocity_(0.0f, 0.0f, 0.0f), isOnFloor_(true), frame_(0)
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
		break;
	case Player::ActionState::LAND:
		break;
	}

	//位置を更新
	transform_.position_ = transform_.position_ + velocity_;
}

//描画
void Player::Draw() {
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Player::Release() {

}

//状態の更新
void Player::UpdateState() {
	velocity_.x = 0.0f;
	velocity_.z = 0.0f;

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

}

//移動
void Player::UpdateMove() {
	if (Input::IsKey(DIK_D)) {
		velocity_.x += 0.5f;
	}
	if (Input::IsKey(DIK_A)) {
		velocity_.x -= 0.5f;
	}
	if (Input::IsKey(DIK_W)) {
		velocity_.z += 0.5f;
	}
	if (Input::IsKey(DIK_S)) {
		velocity_.z -= 0.5f;
	}

	//左コントロールが押されていればダッシュ
	if (Input::IsKey(DIK_LCONTROL)) {
		velocity_.x *= 2.0f;
		velocity_.z *= 2.0f;
	}
}

//空中
void Player::UpdateAir() {

}

//着地
void Player::UpdateLand() {

}
