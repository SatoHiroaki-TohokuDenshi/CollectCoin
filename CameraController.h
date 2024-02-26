#pragma once
#include "Engine/GameObject.h"

//�J�����̓�����Ǘ�����N���X
class CameraController : public GameObject {
private:

public:
	//�R���X�g���N�^
	CameraController(GameObject* parent);

	//�f�X�g���N�^
	~CameraController();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};
