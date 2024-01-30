#include "Timer.h"
#include "Engine/Text.h"

//コンストラクタ
Timer::Timer(GameObject* parent)
	: GameObject(parent, "Timer"), second_(-1), frame_(0), isActive_(false), isFinish_(false)
	, isDisplay_(false), pText_(nullptr), displayPos_(nullptr)
{
}

//デストラクタ
Timer::~Timer() {

}

//初期化
void Timer::Initialize() {
	pText_ = new Text();
}

//更新
void Timer::Update() {
	//有効化されていないなら終了
	if (!isActive_)	return;

	//フレームを進める
	frame_++;

	//1秒経っていないなら
	if (frame_ % FPS == 0)	return;

	//1秒減らす
	second_--;

	//残り時間が0秒なら
	if (second_ <= 0) {
		isActive_ = false;
		isFinish_ = true;
	}
}

//描画
void Timer::Draw() {
	//表示が有効化されていないなら終了
	if (!isDisplay_)	return;

	pText_->Draw(displayPos_->x, displayPos_->y, second_);
}

//開放
void Timer::Release() {
	if ((displayPos_) != nullptr) {
		delete (displayPos_);
		(displayPos_) = nullptr;
	}
}

void Timer::SetTimer(int sec) {
	//マイナスが指定されていたら設定しない
	if (sec < 0)	return;
	second_ = sec;
}

void Timer::SetTimer(int min, int sec) {
	//マイナスが指定されていたら設定しない
	if (sec < 0)	return;
	second_ = (min * 60) + sec;
}

void Timer::StartTimer() {
	//タイマーが設定されていないなら終了
	if (second_ < 0)	return;
	isActive_ = true;
	isFinish_ = false;
}

bool Timer::IsFinish() {
	return isFinish_;
}

void Timer::SetDisplayEnable() {
	isDisplay_ = true;
}

void Timer::SetDisplayDisable() {
	isDisplay_ = false;
}

void Timer::SetTimerPos(int x, int y) {
	if (displayPos_ == nullptr)
		displayPos_ = new DisplayPosition(x, y);
	else {
		displayPos_->x = x;
		displayPos_->y = y;
	}
}
