#pragma once
#include "Engine/GameObject.h"

class Button;

//�^�C�g���V�[�����Ǘ�����N���X
class TitleScene : public GameObject {
private:
	int hPict_;    //�摜�ԍ�
	Button* pButton_;
	bool isMoveScene_;
	int hBlack_;
	int frame_;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�V�[���J��
	void MoveNextScene();
};
