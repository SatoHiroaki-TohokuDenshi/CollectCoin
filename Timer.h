#pragma once
#include "Engine/GameObject.h"

//�O���錾
class Text;

//Timer���Ǘ�����N���X
class Timer : public GameObject {
private:
	//1�b�Ԃ̃t���[����
	const int FPS = GetPrivateProfileInt("GAME", "Fps", 60, ".\\setup.ini");

	int second_;		// �^�C�}�[�̕b��
	int frame_;			// ���t���[����
	bool isActive_;		// �^�C�}�[�͋N������Ă��邩
	bool isFinish_;		// �^�C�}�[���I����Ă��邩
	bool isDisplay_;	// ��ʂɕ\�����s����

	Text* pText_;		// �^�C�}�[�\���p�̕����N���X
	struct DisplayPosition {
		int x;
		int y;
		DisplayPosition() :x(0), y(0) {};
		DisplayPosition(int _x, int _y) 
			:x(_x), y(_y) {};
	}* displayPos_;		//�^�C�}�[�̕\���ʒu

public:
	//�R���X�g���N�^
	Timer(GameObject* parent);

	//�f�X�g���N�^
	~Timer();

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
	/// <summary>�^�C�}�[��b���Őݒ�</summary>
/// <param name="sec">�b��</param>
	void SetTimer(int sec);
	/// <summary>�^�C�}�[�𕪕b�Őݒ�</summary>
	/// <param name="min">��</param>
	/// <param name="sec">�b</param>
	void SetTimer(int min, int sec);

	/// <summary>�^�C�}�[���X�^�[�g</summary>
	void StartTimer();

	/// <summary>�^�C�}�[���I����Ă��邩</summary>
	/// <returns>�I����Ă���Ȃ�true</returns>
	bool IsFinish();

	/// <summary>��ʕ\����L���ɂ���</summary>
	void SetDisplayEnable();
	/// <summary>��ʕ\���𖳌��ɂ���</summary>
	void SetDisplayDisable();

	/// <summary>�\���ʒu��ݒ�(���㌴�_)</summary>
	/// <param name="x">x���W</param>
	/// <param name="y">y���W</param>
	void SetTimerPos(int x, int y);
};
