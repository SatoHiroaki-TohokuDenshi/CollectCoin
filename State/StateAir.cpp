#include "StateAir.h"
#include "../Engine/Input.h"

StateAir::StateAir()
	: frag_(true) {

}

StateAir::~StateAir() {

}

void StateAir::Action(DirectX::XMINT3& count) {
	if (frag_) {
		frag_ = false;
		count.y = 30;
	}

	count.x = 0;
	count.z = 0;

	if (Input::IsKey(DIK_D)) {
		count.x += 1;
	}
	if (Input::IsKey(DIK_A)) {
		count.x -= 1;
	}
	if (Input::IsKey(DIK_W)) {
		count.z += 1;
	}
	if (Input::IsKey(DIK_S)) {
		count.z -= 1;
	}

	count.y -= 2;
}

State* StateAir::GetNextState() {
	return nullptr;
}
