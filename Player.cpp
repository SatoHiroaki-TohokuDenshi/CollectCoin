#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), hModel_(-1) , state_(ActionState::IDLE)
	, velocity_(0.0f, 0.0f, 0.0f), isOnFloor_(true), frame_(0)
{
}

//�f�X�g���N�^
Player::~Player() {

}

//������
void Player::Initialize() {
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Model\\TestPlayer.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void Player::Update() {
	//��Ԃ̍X�V
	UpdateState();

	//��Ԃɂ���ď����𕪊�
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

	//�ʒu���X�V
	transform_.position_ = transform_.position_ + velocity_;
}

//�`��
void Player::Draw() {
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Player::Release() {

}

//��Ԃ̍X�V
void Player::UpdateState() {
	velocity_.x = 0.0f;
	velocity_.z = 0.0f;

	if (Input::IsKey(DIK_W) || Input::IsKey(DIK_A) ||
		Input::IsKey(DIK_S) || Input::IsKey(DIK_D)) {
		state_ = ActionState::MOVE;
		return;
	}

	//�������͂�����������ҋ@
	state_ = ActionState::IDLE;
}

//�ҋ@
void Player::UpdateIdle() {

}

//�ړ�
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

	//���R���g���[����������Ă���΃_�b�V��
	if (Input::IsKey(DIK_LCONTROL)) {
		velocity_.x *= 2.0f;
		velocity_.z *= 2.0f;
	}
}

//��
void Player::UpdateAir() {

}

//���n
void Player::UpdateLand() {

}
