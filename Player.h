#pragma once
#include "Engine/GameObject.h"

//�O���錾
class StateManager;
class CameraController;
class Text;

//Player���Ǘ�����N���X
class Player : public GameObject {
private:
	int hModel_;	// ���f���Ǘ��ԍ�

	XMINT3 moveCount_;
	bool isOnFloor_;	// ���̏�ɂ��邩
	int frame_;			// ���n�d���p�J�E���g�ϐ�
	GameObject* pStage_;

	//�X�e�[�g�Ǘ�
	StateManager* pManager_;

	//�J�����Ǘ�
	CameraController* pCamera_;

	//�ʒu���̍X�V
	void UpdatePosition();

	//�R�C���̃J�E���g
	int countCoin_;

	Text* pText;

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

	void CountCoin() { countCoin_++; };
};
