#pragma once
#include "StateBase.h"

//空中状態
class StateAir :
    public State {
private:

public:
	StateAir();
	virtual ~StateAir();

	//行動
	virtual void Action(DirectX::XMINT3& count) override;
	//次のステートを取得
	virtual State* GetNextState() override;
};
