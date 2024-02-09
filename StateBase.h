#pragma once
#include <DirectXMath.h>

//状態を表すインターフェース
class State {
private:

public:
	//デストラクタ
	virtual ~State() = 0;
	//行動
	virtual void Action(DirectX::XMINT3& count) = 0;
	//次のステート
	virtual State* GetNextState() = 0;
};
