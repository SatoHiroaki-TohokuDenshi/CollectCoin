#include "StateIdle.h"
#include "States.h"

#include "../Engine/Input.h"

StateIdle::StateIdle() {

}

StateIdle::~StateIdle() {

}

void StateIdle::Action(DirectX::XMINT3& count) {
	count = { 0,0,0 };
}

State* StateIdle::GetNextState() {
	//ジャンプ
	if (Input::IsKeyDown(DIK_SPACE))
		return new StateJump();

	//移動
	if (Input::IsKey(DIK_W) || Input::IsKey(DIK_A) ||
		Input::IsKey(DIK_S) || Input::IsKey(DIK_D))
		return new StateMove();

	//入力がないなら待機
	return nullptr;
}
