#include "Coin.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"

#include "Player.h"

//�R���X�g���N�^
Coin::Coin(GameObject* parent)
	:GameObject(parent, "Coin"), hModel_(-1) {

}

//�f�X�g���N�^
Coin::~Coin() {

}

//������
void Coin::Initialize() {
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Model\\Coin.fbx");
	assert(hModel_ >= 0);

	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.6f);
	AddCollider(collision);
}

//�X�V
void Coin::Update() {
	transform_.rotate_.y += 1.0f;
}

//�`��
void Coin::Draw() {
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Coin::Release() {

}

//�����ɓ�������
void Coin::OnCollision(GameObject* pTarget) {
	//���������Ƃ��̏���
	if (pTarget->GetObjectName() == "Player") {
		KillMe();
		((Player*)pTarget)->CountCoin();
	}
}
