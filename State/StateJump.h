#pragma once
#include "StateBase.h"

//�󒆏��
class StateJump :
    public State {
private:
	bool frag_;

public:
	StateJump();
	virtual ~StateJump();

	//�s��
	virtual void Action(DirectX::XMINT3& count) override;
	//���̃X�e�[�g���擾
	virtual State* GetNextState() override;
};
