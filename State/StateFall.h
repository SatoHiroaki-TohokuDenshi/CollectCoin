#pragma once
#include "StateBase.h"

//落下状態
class StateFall :
	public State {
private:

public:
	StateFall();
	virtual ~StateFall();

	//行動
	virtual void Action(DirectX::XMINT3& count) override;
	//次のステートを取得
	virtual State* GetNextState() override;
};
