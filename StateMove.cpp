#include "StateMove.h"
#include "StateAir.h"
#include "StateIdle.h"

#include "Engine/Input.h"

StateMove::StateMove() {

}

StateMove::~StateMove() {

}

void StateMove::Action(DirectX::XMINT3& count) {
	count.x = 0;
	count.z = 0;

	if (Input::IsKey(DIK_D)) {
		count.x += 2;
	}
	if (Input::IsKey(DIK_A)) {
		count.x -= 2;
	}
	if (Input::IsKey(DIK_W)) {
		count.z += 2;
	}
	if (Input::IsKey(DIK_S)) {
		count.z -= 2;
	}

	//���R���g���[����������Ă���΃_�b�V��
	if (Input::IsKey(DIK_LCONTROL)) {
		count.x *= 2;
		count.z *= 2;
	}
}

State* StateMove::GetNextState() {
	//�W�����v
	if (Input::IsKeyDown(DIK_SPACE))
		return new StateAir();

	//�ړ��Ȃ�X�V����
	if (Input::IsKey(DIK_W) || Input::IsKey(DIK_A) ||
		Input::IsKey(DIK_S) || Input::IsKey(DIK_D))
		return nullptr;

	//���͂��Ȃ��Ȃ�ҋ@
	return new StateIdle();
}
