#include "StateFall.h"
#include "States.h"

#include "../Engine/Input.h"

StateFall::StateFall() {

}

StateFall::~StateFall() {

}

void StateFall::Action(DirectX::XMINT3& count) {
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

State* StateFall::GetNextState() {
	//Playerë§Ç©ÇÁíÖínÇ…à⁄çs
	return nullptr;
}
