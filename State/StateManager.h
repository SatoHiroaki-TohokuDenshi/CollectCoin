#pragma once
#include <DirectXMath.h>

//�O���錾
class State;

//�X�e�[�g���Ǘ�����N���X
class StateManager {
private:
	State* myState_;

public:
	StateManager();
	~StateManager();

	//�X�e�[�g�̍X�V
	void UpdateState();
	//�s��
	void Action(DirectX::XMINT3& count);
	
	//���݊O����
	void SetStateFall();

	//���n
	void SetStateLand();
};
