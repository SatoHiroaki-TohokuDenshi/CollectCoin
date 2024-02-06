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

	SphereCollider* collision = new SphereCollider(XMFLOAT3(1.5f, 0.6f, 0.5f), 0.6f);
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
		break;
	}

	//�ʒu���X�V
	transform_.position_ = transform_.position_ + velocity_;
	Camera::SetPosition(transform_.position_ - XMFLOAT3(0.0f, 0.0f, 3.0f));
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
		if (velocity_.y < 0) {
			velocity_.y = 0.0f;
			isOnFloor_ = true;
			state_ = ActionState::LAND;

			Stage* pStage = (Stage*)FindObject("Stage");    //�X�e�[�W�I�u�W�F�N�g��T��
			int hGroundModel = pStage->GetModelHandle();    //���f���ԍ����擾

			RayCastData data;
			//���C�̔��ˈʒu
			data.start = transform_.position_ + XMFLOAT3(0.0f, 3.0f, 0.0f);
			data.dir = XMFLOAT3(0, -1, 0);			//���C�̕���
			Model::RayCast(hGroundModel, &data);	//���C�𔭎�

			if (data.hit) {
				transform_.position_.y -= data.dist;
			}
		}
	}
}

//��Ԃ̍X�V
void Player::UpdateState() {
	velocity_.x = 0.0f;
	velocity_.z = 0.0f;

	//���̏�ɂ��Ȃ�
	if (!isOnFloor_) {
		state_ = ActionState::AIR;
		return;
	}
	//�X�y�[�X�o�[
	if (Input::IsKeyDown(DIK_SPACE)) {
		velocity_.y = 0.4f;
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

}

//�ړ�
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

	//���R���g���[����������Ă���΃_�b�V��
	if (Input::IsKey(DIK_LCONTROL)) {
		velocity_.x *= 2.0f;
		velocity_.z *= 2.0f;
	}
}

//��
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

//���n
void Player::UpdateLand() {
	if (frame_ < 10) {
		frame_++;
		return;
	}

	state_ = ActionState::IDLE;
}
