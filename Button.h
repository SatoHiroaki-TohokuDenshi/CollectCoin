#pragma once
#include "Engine/GameObject.h"
#include <array>

//�O���錾
class Text;

//Button���Ǘ�����N���X
class Button : public GameObject {
private:
	//�摜�Ǘ��ϐ�
	std::array<int, 2> hPict_{ -1, -1 };
	XMFLOAT3 position_;		// �\���ʒu
	XMFLOAT3 pictSize_;		// �摜�T�C�Y

	Text* pText_;			// �����N���X
	std::string txt_;		// �\��������
public:
	//�R���X�g���N�^
	Button(GameObject* parent);

	//�f�X�g���N�^
	~Button();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

//�V�K�֐��Q
public:
	// �ǂݍ���
	void LoadFile(std::string fileName);

	// �ʒu�̐ݒ�
	// �����F���ォ��̃s�N�Z����
	void SetButtonPosition(int x, int y);

	// �}�E�X���z�o�[���Ă��邩
	bool IsHovered();

	// �\��������̐ݒ�
	void SetText(std::string t);

public:
	bool isClicked();
};
