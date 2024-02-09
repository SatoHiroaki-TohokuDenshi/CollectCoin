#pragma once
#include "StateBase.h"

//着地状態
class StateLand :
	public State {
private:

public:
	StateLand();
	virtual ~StateLand();

	//行動
	virtual void Action(DirectX::XMINT3& count) override;
	//次のステートを取得
	virtual State* GetNextState() override;
};
