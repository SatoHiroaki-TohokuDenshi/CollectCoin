#pragma once
#include "StateBase.h"

//���n���
class StateLand :
	public State {
private:
	int frame_;	//�t���[����

public:
	StateLand();
	virtual ~StateLand();

	//�s��
	virtual void Action(DirectX::XMINT3& count) override;
	//���̃X�e�[�g���擾
	virtual State* GetNextState() override;
};
