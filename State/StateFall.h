#pragma once
#include "StateBase.h"

//�ҋ@���
class StateFall :
	public State {
private:

public:
	StateFall();
	virtual ~StateFall();

	//�s��
	virtual void Action(DirectX::XMINT3& count) override;
	//���̃X�e�[�g���擾
	virtual State* GetNextState() override;
};
