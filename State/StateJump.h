#pragma once
#include "StateBase.h"

//�W�����v�����u��
class StateJump :
    public State {
private:

public:
	StateJump();
	virtual ~StateJump();

	//�s��
	virtual void Action(DirectX::XMINT3& count) override;
	//���̃X�e�[�g���擾
	virtual State* GetNextState() override;
};
