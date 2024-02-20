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

//�R���X�g���N�^
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), hModel_(-1), pStage_(nullptr)
	, isOnFloor_(true), frame_(0), moveCount_(0, 0, 0)
	, pManager_(new StateManager)
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

	SphereCollider* collision = new SphereCollider(XMFLOAT3(0.5f, 0.58f, 0.5f), 0.1f);
	AddCollider(collision);
}

//�X�V
void Player::Update() {
	isOnFloor_ = false;
	Collision(pStage_);
	if (!isOnFloor_)
		pManager_->SetStateAir();

	//��Ԃ̍X�V
	pManager_->UpdateState();

	//��Ԃɂ���ď����𕪊�
	pManager_->Action(moveCount_);

	//�ʒu���X�V
	UpdatePosition();
	Camera::SetPosition(XMFLOAT3(transform_.position_.x, transform_.position_.y, transform_.position_.z - 1.0f));
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
