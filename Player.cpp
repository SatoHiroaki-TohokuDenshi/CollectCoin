#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

#include "Stage.h"
#include "Engine/Camera.h"

namespace {
	const float SPEED = 0.1f;
	const float GRAVITY = 0.02f;
}

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

	SphereCollider* collision = new SphereCollider(XMFLOAT3(1.5f, 0.6f, 0.5f), 0.6f);
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
		break;
	}

	//位置を更新
	transform_.position_ = transform_.position_ + velocity_;
	Camera::SetPosition(transform_.position_ - XMFLOAT3(0.0f, 0.0f, 3.0f));
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
		if (velocity_.y < 0) {
			velocity_.y = 0.0f;
			isOnFloor_ = true;
			state_ = ActionState::LAND;

			Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクトを探す
			int hGroundModel = pStage->GetModelHandle();    //モデル番号を取得

			RayCastData data;
			//レイの発射位置
			data.start = transform_.position_ + XMFLOAT3(0.0f, 3.0f, 0.0f);
			data.dir = XMFLOAT3(0, -1, 0);			//レイの方向
			Model::RayCast(hGroundModel, &data);	//レイを発射

			if (data.hit) {
				transform_.position_.y -= data.dist;
			}
		}
	}
}

//状態の更新
void Player::UpdateState() {
	velocity_.x = 0.0f;
	velocity_.z = 0.0f;

	//床の上にいない
	if (!isOnFloor_) {
		state_ = ActionState::AIR;
		return;
	}
	//スペースバー
	if (Input::IsKeyDown(DIK_SPACE)) {
		velocity_.y = 0.4f;
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

}

//移動
void Player::UpdateMove() {
	if (Input::IsKey(DIK_D)) {
		velocity_.x += SPEED;
	}
	if (Input::IsKey(DIK_A)) {
		velocity_.x -= SPEED;
	}
	if (Input::IsKey(DIK_W)) {
		velocity_.z += SPEED;
	}
	if (Input::IsKey(DIK_S)) {
		velocity_.z -= SPEED;
	}

	//左コントロールが押されていればダッシュ
	if (Input::IsKey(DIK_LCONTROL)) {
		velocity_.x *= 2.0f;
		velocity_.z *= 2.0f;
	}
}

//空中
void Player::UpdateAir() {
	if (Input::IsKey(DIK_D)) {
		velocity_.x += SPEED / 2.0f;
	}
	if (Input::IsKey(DIK_A)) {
		velocity_.x -= SPEED / 2.0f;
	}
	if (Input::IsKey(DIK_W)) {
		velocity_.z += SPEED / 2.0f;
	}
	if (Input::IsKey(DIK_S)) {
		velocity_.z -= SPEED / 2.0f;
	}

	velocity_.y -= GRAVITY;
}

//着地
void Player::UpdateLand() {
	if (frame_ < 10) {
		frame_++;
		return;
	}

	state_ = ActionState::IDLE;
}
