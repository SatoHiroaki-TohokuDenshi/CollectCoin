#include "StateIdle.h"
#include "StateAir.h"
#include "StateMove.h"

#include "../Engine/Input.h"

StateIdle::StateIdle() {

}

StateIdle::~StateIdle() {

}

void StateIdle::Action(DirectX::XMINT3& count) {
	count = { 0,0,0 };
}

State* StateIdle::GetNextState() {
	//ƒWƒƒƒ“ƒv
	if (Input::IsKeyDown(DIK_SPACE))
		return new StateAir();

	//ˆÚ“®
	if (Input::IsKey(DIK_W) || Input::IsKey(DIK_A) ||
		Input::IsKey(DIK_S) || Input::IsKey(DIK_D))
		return new StateMove();

	//“ü—Í‚ª‚È‚¢‚È‚ç‘Ò‹@
	return nullptr;
}
