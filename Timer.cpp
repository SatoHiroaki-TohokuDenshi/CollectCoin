#include "Timer.h"
#include "Engine/Text.h"

//�R���X�g���N�^
Timer::Timer(GameObject* parent)
	: GameObject(parent, "Timer"), second_(-1), frame_(0), isActive_(false), isFinish_(false)
	, isDisplay_(false), pText_(nullptr), displayPos_(nullptr)
{
}

//�f�X�g���N�^
Timer::~Timer() {

}

//������
void Timer::Initialize() {
	pText_ = new Text();
}

//�X�V
void Timer::Update() {
	//�L��������Ă��Ȃ��Ȃ�I��
	if (!isActive_)	return;

	//�t���[����i�߂�
	frame_++;

	//1�b�o���Ă��Ȃ��Ȃ�
	if (frame_ % FPS == 0)	return;

	//1�b���炷
	second_--;

	//�c�莞�Ԃ�0�b�Ȃ�
	if (second_ <= 0) {
		isActive_ = false;
		isFinish_ = true;
	}
}

//�`��
void Timer::Draw() {
	//�\�����L��������Ă��Ȃ��Ȃ�I��
	if (!isDisplay_)	return;

	pText_->Draw(displayPos_->x, displayPos_->y, second_);
}

//�J��
void Timer::Release() {
	if ((displayPos_) != nullptr) {
		delete (displayPos_);
		(displayPos_) = nullptr;
	}
}

void Timer::SetTimer(int sec) {
	//�}�C�i�X���w�肳��Ă�����ݒ肵�Ȃ�
	if (sec < 0)	return;
	second_ = sec;
}

void Timer::SetTimer(int min, int sec) {
	//�}�C�i�X���w�肳��Ă�����ݒ肵�Ȃ�
	if (sec < 0)	return;
	second_ = (min * 60) + sec;
}

void Timer::StartTimer() {
	//�^�C�}�[���ݒ肳��Ă��Ȃ��Ȃ�I��
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
