#pragma once
#include <DirectXMath.h>

//前方宣言
class State;

//ステートを管理するクラス
class StateManager {
private:
	State* myState_;

public:
	StateManager();
	~StateManager();

	//ステートの更新
	void UpdateState();
	//行動
	void Action(DirectX::XMINT3& count);
	
	//踏み外した
	void SetStateFall();

	//着地
	void SetStateLand();
};
