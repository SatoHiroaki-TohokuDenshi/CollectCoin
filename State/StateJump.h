#pragma once
#include "StateBase.h"

//ジャンプした瞬間
class StateJump :
    public State {
private:

public:
	StateJump();
	virtual ~StateJump();

	//行動
	virtual void Action(DirectX::XMINT3& count) override;
	//次のステートを取得
	virtual State* GetNextState() override;
};
