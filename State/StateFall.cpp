#include "StateFall.h"
#include "States.h"

#include "../Engine/Input.h"

StateFall::StateFall() {

}

StateFall::~StateFall() {

}

void StateFall::Action(DirectX::XMINT3& count) {
	count = { 0,0,0 };
}

State* StateFall::GetNextState() {
	return nullptr;
}
