#include "StateManager.h"
#include <utility>
#include "States.h"

StateManager::StateManager() {
	myState_ = new StateIdle();
}

StateManager::~StateManager() {
	delete myState_;
}

void StateManager::UpdateState() {
	//���̃X�e�[�g���擾
	State* tmp = myState_->GetNextState();

	//�����X�e�[�g�inullptr�j�Ȃ�I��
	if (tmp == nullptr)
		return;

	//����ւ��ĉ��
	std::swap(myState_, tmp);
	delete tmp;
}

void StateManager::Action(DirectX::XMINT3& count) {
	myState_->Action(count);
}

void StateManager::SetStateFall() {
	delete myState_;
	myState_ = new StateFall();
}

void StateManager::SetStateLand() {
	delete myState_;
	myState_ = new StateLand();
}
