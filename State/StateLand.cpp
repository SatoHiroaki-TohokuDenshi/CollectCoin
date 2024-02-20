#include "StateLand.h"
#include "States.h"

StateLand::StateLand()
	: frame_(0) {

}

StateLand::~StateLand() {

}

void StateLand::Action(DirectX::XMINT3& count) {
	count = { 0,0,0 };
	frame_++;
}

State* StateLand::GetNextState() {
	if (frame_ > 5)
		return new StateIdle();
	return nullptr;
}
