#pragma once
#include "StateBase.h"

//�ҋ@���
class StateIdle :
	public State {
private:

public:
	StateIdle();
	virtual ~StateIdle();

	//�s��
	virtual void Action(DirectX::XMINT3& count) override;
	//���̃X�e�[�g���擾
	virtual State* GetNextState() override;
};
