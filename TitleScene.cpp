#include "TitleScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Button.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hPict_(-1), pButton_(nullptr)
	, isMoveScene_(false), hBlack_(0), frame_(0) {

}

//初期化
void TitleScene::Initialize() {
	//画像データのロード
	hPict_ = Image::Load("Image\\logo-color.png");
	assert(hPict_ >= 0);
	//画像データのロード
	hBlack_ = Image::Load("Image\\BlackOut.png");
	assert(hBlack_ >= 0);

	Transform t{};
	t.position_.x -= 0.6f;
	t.scale_ = { 0.4f, 0.4f, 0.4f };
	Image::SetTransform(hPict_, t);

	t.position_ = {0.0f, 0.0f, 0.0f};
	t.scale_ = { 4.0f,4.0f, 4.0f };
	Image::SetTransform(hBlack_, t);
	Image::SetAlpha(hBlack_, 0);

	pButton_ = Instantiate<Button>(this);
	pButton_->LoadFile("Image\\TestButton");
	pButton_->SetButtonPosition(650, 232);
	pButton_->SetText("Play");
}

//更新
void TitleScene::Update() {
	if (pButton_->isClicked())
		isMoveScene_ = true;

	if (!isMoveScene_)
		return;

	MoveNextScene();
	if (frame_ < 255)
		return;

	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID::SCENE_ID_PLAY);
}

//描画
void TitleScene::Draw() {
	Image::Draw(hPict_);
	if (!isMoveScene_)
		return;

	Image::Draw(hBlack_);
}

//開放
void TitleScene::Release() {

}

void TitleScene::MoveNextScene() {
	frame_++;
	Image::SetAlpha(hBlack_, frame_);
}
