#pragma once
#include "StateBase.h"

//空中状態
class StateJump :
    public State {
private:
	bool frag_;

public:
	StateJump();
	virtual ~StateJump();

	//行動
	virtual void Action(DirectX::XMINT3& count) override;
	//次のステートを取得
	virtual State* GetNextState() override;
};
