#pragma once
#include "StateBase.h"

//���n���
class StateLand :
	public State {
private:

public:
	StateLand();
	virtual ~StateLand();

	//�s��
	virtual void Action(DirectX::XMINT3& count) override;
	//���̃X�e�[�g���擾
	virtual State* GetNextState() override;
};
