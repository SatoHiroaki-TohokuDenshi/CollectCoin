#include "StateManager.h"
#include <utility>
#include "StateIdle.h"

StateManager::StateManager() {
	myState_ = new StateIdle();
}

StateManager::~StateManager() {
	delete myState_;
}

void StateManager::UpdateState() {
	//次のステートを取得
	State* tmp = myState_->GetNextState();

	//同じステート（nullptr）なら終了
	if (tmp == nullptr)
		return;

	//入れ替えて解放
	std::swap(myState_, tmp);
	delete tmp;
}

void StateManager::Action(DirectX::XMINT3& count) {
	myState_->Action(count);
}
