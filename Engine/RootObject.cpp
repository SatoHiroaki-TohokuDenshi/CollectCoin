#include "RootObject.h"
#include "SceneManager.h"

//�R���X�g���N�^
RootObject::RootObject():
	GameObject(nullptr, "RootObject") {
}

//�f�X�g���N�^
RootObject::~RootObject() {

}

//������
void RootObject::Initialize() {
	//�V�[���}�l�[�W���[���쐬
	Instantiate<SceneManager>(this);
}

//�X�V
void RootObject::Update() {

}

//�`��
void RootObject::Draw() {

}

//�J��
void RootObject::Release() {

}
