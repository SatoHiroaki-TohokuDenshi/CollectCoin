#pragma once
#include <DirectXMath.h>

//��Ԃ�\���C���^�[�t�F�[�X
class State {
private:

public:
	//�f�X�g���N�^
	virtual ~State() = 0;
	//�s��
	virtual void Action(DirectX::XMINT3& count) = 0;
	//���̃X�e�[�g
	virtual State* GetNextState() = 0;
};
