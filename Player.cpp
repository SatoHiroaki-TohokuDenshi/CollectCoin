#include "Player.h"

//コンストラクタ
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), hModel_(-1)
	, state_(ActionState::IDLE)
{
}

//デストラクタ
Player::~Player() {

}

//初期化
void Player::Initialize() {

}

//更新
void Player::Update() {
	//状態の更新
	UpdateState();

	//状態によって処理を分岐
	switch (state_) {
	case Player::ActionState::IDLE:
		break;
	case Player::ActionState::MOVE:
		break;
	case Player::ActionState::AIR:
		break;
	case Player::ActionState::LAND:
		break;
	}
}

//描画
void Player::Draw() {

}

//開放
void Player::Release() {

}

//状態の更新
void Player::UpdateState() {

}

//待機
void Player::UpdateIdle() {

}

//移動
void Player::UpdateMove() {

}

//空中
void Player::UpdateAir() {

}

//着地
void Player::UpdateLand() {

}
