#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Text.h"
#include "Engine/SphereCollider.h"
#include "State/StateManager.h"

#include "CameraController.h"

namespace {
	const float SPEED_UNIT_XZ = 0.1f;
	const float SPEED_UNIT_Y = 0.02f;
}

//�R���X�g���N�^
Player::Player(GameObject* parent)
	: GameObject(parent, "Player"), hModel_(-1), pStage_(nullptr)
	, isOnFloor_(true), frame_(0), moveCount_(0, 0, 0)
	, pManager_(new StateManager), pCamera_(nullptr)
	, countCoin_(0), pText(nullptr)
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
	pCamera_ = Instantiate<CameraController>(this);

	pText = new Text();
	pText->Initialize();
}

//�X�V
void Player::Update() {
	isOnFloor_ = false;
	Collision(pStage_);
	if (!isOnFloor_)
		pManager_->SetStateFall();

	//��Ԃ̍X�V
	pManager_->UpdateState();

	//��Ԃɂ���ď����𕪊�
	pManager_->Action(moveCount_);

	//�ʒu���X�V
	UpdatePosition();
}

//�`��
void Player::Draw() {
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	pText->Draw(30, 30, countCoin_);
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
	//���ݒn�̃x�N�g��
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

	//�ړ��ʂ̃x�N�g��
	XMVECTOR vMove = {
		SPEED_UNIT_XZ * moveCount_.x,
		0.0f,
		SPEED_UNIT_XZ * moveCount_.z,
		0.0f
	};

	//�J�����̌����ɕό`������s��
	XMMATRIX mRotateY = XMMatrixRotationY(XMConvertToRadians(pCamera_->GetRotate().y));

	//�ړ��x�N�g����ό`
	vMove = XMVector3TransformCoord(vMove, mRotateY);

	//���ݒn�̍X�V
	vPos += vMove;
	XMStoreFloat3(&transform_.position_, vPos);
	pCamera_->SetPosition(transform_.position_);

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
