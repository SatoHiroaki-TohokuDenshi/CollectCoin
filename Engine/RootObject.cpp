#include "RootObject.h"
#include "SceneManager.h"

//コンストラクタ
RootObject::RootObject():
	GameObject(nullptr, "RootObject") {
}

//デストラクタ
RootObject::~RootObject() {

}

//初期化
void RootObject::Initialize() {
	//シーンマネージャーを作成
	Instantiate<SceneManager>(this);
}

//更新
void RootObject::Update() {

}

//描画
void RootObject::Draw() {

}

//開放
void RootObject::Release() {

}
