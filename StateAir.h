#pragma once
#include "StateBase.h"

//�󒆏��
class StateAir :
    public State {
private:

public:
	StateAir();
	virtual ~StateAir();

	//�s��
	virtual void Action(DirectX::XMINT3& count) override;
	//���̃X�e�[�g���擾
	virtual State* GetNextState() override;
};
