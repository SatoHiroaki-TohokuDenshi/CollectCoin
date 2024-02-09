#pragma once
#include <vector>

//��Ԃ�\���C���^�[�t�F�[�X
class State {
private:

public:
	//�f�X�g���N�^
	virtual ~State() = 0;
	//�s��
	virtual void Action(std::vector<int>& count) = 0;
	//���̃X�e�[�g
	virtual State* GetNextState() = 0;
};
