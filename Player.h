#pragma once
#include "Engine/GameObject.h"

//Player���Ǘ�����N���X
class Player : public GameObject {
private:
	int hModel_;	// ���f���Ǘ��ԍ�

	//�v���C���[�̏��
	enum class ActionState {
		IDLE = 0,	// �ҋ@
		MOVE,		// �ړ�
		AIR,		// ��
		LAND,		// ���n
	} state_;

	XMFLOAT3 velocity_;	// �ړ���
	bool isOnFloor_;	// ���̏�ɂ��邩
	int frame_;			// ���n�d���p�J�E���g�ϐ�

	//��Ԃ̍X�V
	void UpdateState();
	//�ҋ@
	void UpdateIdle();
	//�ړ�
	void UpdateMove();
	//��
	void UpdateAir();
	//���n
	void UpdateLand();

public:
	//�R���X�g���N�^
	Player(GameObject* parent);

	//�f�X�g���N�^
	~Player();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};
