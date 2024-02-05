#include "Player.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), hModel_(-1)
	, state_(ActionState::IDLE)
{
}

//�f�X�g���N�^
Player::~Player() {

}

//������
void Player::Initialize() {

}

//�X�V
void Player::Update() {
	//��Ԃ̍X�V
	UpdateState();

	//��Ԃɂ���ď����𕪊�
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

//�`��
void Player::Draw() {

}

//�J��
void Player::Release() {

}

//��Ԃ̍X�V
void Player::UpdateState() {

}

//�ҋ@
void Player::UpdateIdle() {

}

//�ړ�
void Player::UpdateMove() {

}

//��
void Player::UpdateAir() {

}

//���n
void Player::UpdateLand() {

}
