#pragma once
#include "StateBase.h"

//�ړ����
class StateMove :
	public State {
private:

public:
	StateMove();
	virtual ~StateMove();

	//�s��
	virtual void Action(DirectX::XMINT3& count) override;
	//���̃X�e�[�g���擾
	virtual State* GetNextState() override;
};
