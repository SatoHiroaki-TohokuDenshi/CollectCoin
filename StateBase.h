#pragma once
#include <vector>

//状態を表すインターフェース
class State {
private:

public:
	//デストラクタ
	virtual ~State() = 0;
	//行動
	virtual void Action(std::vector<int>& count) = 0;
	//次のステート
	virtual State* GetNextState() = 0;
};
