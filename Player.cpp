#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

#include "Engine/Camera.h"

namespace {
	const float SPEED_UNIT_XZ = 0.1f;
	const float SPEED_UNIT_Y = 0.02f;
}

//�R���X�g���N�^
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), hModel_(-1), pStage_(nullptr)
	, state_(ActionState::IDLE), isOnFloor_(true), frame_(0)
	, moveCount_(0, 0, 0)
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

	pStage_ = FindObject("Stage");

	SphereCollider* collision = new SphereCollider(XMFLOAT3(0.5f, 0.6f, 0.5f), 0.1f);
	AddCollider(collision);
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
		UpdateAir();
		break;
	case Player::ActionState::LAND:
		UpdateLand();
		break;
	}

	//�ʒu���X�V
	UpdatePosition();
	Camera::SetTarget(transform_.position_);
}

//�`��
void Player::Draw() {
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Player::Release() {

}

//�����ɓ�������
void Player::OnCollision(GameObject* pTarget) {
	if (pTarget->GetObjectName() == "Stage") {
		//�㏸���Ȃ�I��
		if (moveCount_.y > 0)
			return;
		if (moveCount_.y == 0)
			isOnFloor_ = true;
		if (moveCount_.y < 0) {
			state_ = ActionState::LAND;
			moveCount_ = { 0,0,0 };
			isOnFloor_ = true;
		}
	}
}

//��Ԃ̍X�V
void Player::UpdateState() {
	//���̏�ɂ��邩�𔻒�
	isOnFloor_ = false;
	Collision(pStage_);

	//���n��Ԃ͓����ōX�V
	if (state_ == ActionState::LAND) {
		return;
	}
	//���̏�ɂ��Ȃ�
	if (!isOnFloor_) {
		state_ = ActionState::AIR;
		return;
	}
	//�X�y�[�X�o�[
	if (Input::IsKeyDown(DIK_SPACE)) {
		moveCount_.y = 30;
		isOnFloor_ = false;
		state_ = ActionState::AIR;
		return;
	}
	//WASD�L�[
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
	moveCount_ = { 0,0,0 };
}

//�ړ�
void Player::UpdateMove() {
	moveCount_.x = 0;
	moveCount_.z = 0;

	if (Input::IsKey(DIK_D)) {
		moveCount_.x += 2;
	}
	if (Input::IsKey(DIK_A)) {
		moveCount_.x -= 2;
	}
	if (Input::IsKey(DIK_W)) {
		moveCount_.z += 2;
	}
	if (Input::IsKey(DIK_S)) {
		moveCount_.z -= 2;
	}

	//���R���g���[����������Ă���΃_�b�V��
	if (Input::IsKey(DIK_LCONTROL)) {
		moveCount_.x *= 2;
		moveCount_.z *= 2;
	}
}

//��
void Player::UpdateAir() {
	moveCount_.x = 0;
	moveCount_.z = 0;

	if (Input::IsKey(DIK_D)) {
		moveCount_.x += 1;
	}
	if (Input::IsKey(DIK_A)) {
		moveCount_.x -= 1;
	}
	if (Input::IsKey(DIK_W)) {
		moveCount_.z += 1;
	}
	if (Input::IsKey(DIK_S)) {
		moveCount_.z -= 1;
	}

	moveCount_.y -= 2;
}

//���n
void Player::UpdateLand() {
	if (frame_ < 5) {
		frame_++;
		return;
	}
	frame_ = 0;
	state_ = ActionState::IDLE;
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
			if (state_ == ActionState::LAND)
				break;
		}
	}
}
