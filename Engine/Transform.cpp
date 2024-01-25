#include "Transform.h"

//コンストラクタ
Transform::Transform(): pParent_(nullptr) {
	position_ = XMFLOAT3(0, 0, 0);
	rotate_ = XMFLOAT3(0, 0, 0);
	scale_ = XMFLOAT3(1, 1, 1);
	matTranslate_ = XMMatrixIdentity();
	matRotate_ = XMMatrixIdentity();
	matScale_ = XMMatrixIdentity();
}

//デストラクタ
Transform::~Transform() {

}

//各行列の計算
void Transform::Calclation() {
	//移動行列
	matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

	//回転行列
	XMMATRIX rotateX, rotateY, rotateZ;
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
	matRotate_ = rotateZ * rotateX * rotateY;

	//拡大縮小
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

//ワールド行列を取得
XMMATRIX Transform::GetWorldMatrix()  {
	Calclation();
	if (pParent_) {
		return  matScale_ * matRotate_ * matTranslate_ * pParent_->GetWorldMatrix();
	}

	return  matScale_ * matRotate_ * matTranslate_;
}
