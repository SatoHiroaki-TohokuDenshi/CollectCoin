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

	int moveCountX_;	// X�̈ړ���
	int moveCountY_;	// Y�̈ړ���
	int moveCountZ_;	// Z�̈ړ���
	bool isOnFloor_;	// ���̏�ɂ��邩
	int frame_;			// ���n�d���p�J�E���g�ϐ�
	GameObject* pStage_;

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

	//�ʒu���̍X�V
	void UpdatePosition();

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

	//�����ɓ�������
	//�����FpTarget ������������
	void OnCollision(GameObject* pTarget) override;
};
