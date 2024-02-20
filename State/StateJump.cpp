#include "StateJump.h"
#include "States.h"

#include "../Engine/Input.h"

StateJump::StateJump() {

}

StateJump::~StateJump() {

}

void StateJump::Action(DirectX::XMINT3& count) {
	count.y = 30;

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

State* StateJump::GetNextState() {
	//‚·‚®—‰ºó‘Ô‚ÉˆÚs
	return new StateFall();;
}
