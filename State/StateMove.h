#pragma once
#include "StateBase.h"

//移動状態
class StateMove :
	public State {
private:

public:
	StateMove();
	virtual ~StateMove();

	//行動
	virtual void Action(DirectX::XMINT3& count) override;
	//次のステートを取得
	virtual State* GetNextState() override;
};
