#include "Button.h"
#include "Engine/Text.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/Direct3D.h"

// コンストラクタ
Button::Button(GameObject* parent)
	:GameObject(parent, "Button"), position_{ transform_.position_ }
	, pictSize_{ 0.0f, 0.0f, 0.0f }, pText_(nullptr), txt_("")
{
}

// デストラクタ
Button::~Button() {

}

// 初期化
void Button::Initialize() {
	pText_ = new Text;
	pText_->Initialize();
}

// 更新
void Button::Update() {

}

// 描画
void Button::Draw() {
	// 画像が読み込まれていないなら終了
	if (hPict_[0] < 0)	return;

	// 原点を左上に設定
	float px = (float)(position_.x - Direct3D::screenWidth_ / 2.0f);
	float py = (float)(-position_.y + Direct3D::screenHeight_ / 2.0f);

	px += (float)(pictSize_.x / 2.0f);
	py -= (float)(pictSize_.y / 2.0f);

	// ピクセル単位に変換
	px /= (float)(Direct3D::screenWidth_ / 2.0f);
	py /= (float)(Direct3D::screenHeight_ / 2.0f);

	Transform t{};
	t.position_ = { px, py, 0.0f };

	int index = 0;
	if (IsHovered()) {
		index = 1;
	}
	else {
		index = 0;
	}
	Image::SetTransform(hPict_[index], t);
	Image::Draw(hPict_[index]);

	if (txt_ != ""){
		int tx = (int)(position_.x + (pictSize_.x / 2.0f));
		tx -= (int)(txt_.size() / 2) * pText_->GetTextWidth();
		int ty = (int)(position_.y + (pictSize_.y / 2.0f));
		pText_->Draw(tx, ty, txt_.c_str());
	}
}

// 開放
void Button::Release() {
	pText_->Release();
}

void Button::LoadFile(std::string fileName) {
	for (int i = 0; i < hPict_.size(); i++) {
		hPict_[i] = Image::Load(fileName + ".png");
		assert(hPict_[i] >= 0);

		fileName += "Clicked";
	}


	pictSize_ = Image::GetImageSize(hPict_[0]);
}

void Button::SetButtonPosition(int x, int y) {
	position_ = { (float)x, (float)y, 0.0f };
}

bool Button::IsHovered() {
	XMFLOAT3 mouse = Input::GetMousePosition();
	if (mouse.x >= position_.x && mouse.x < position_.x + pictSize_.x &&
		mouse.y >= position_.y && mouse.y < position_.y + pictSize_.y) {
		return true;
	}
	return false;
}

void Button::SetText(std::string t) {
	txt_ = t;
}