#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"
#include "Engine/BoxCollider.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"), hModel_(-1)
{
}

//�f�X�g���N�^
Stage::~Stage() {

}

//������
void Stage::Initialize() {
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Model\\TestGround.fbx");
	assert(hModel_ >= 0);

	CsvReader csv;
	csv.Load("Map.csv");
	map_.resize(csv.GetHeight());
	for (int h = 0; h < map_.size(); h++) {
		map_[h].resize(csv.GetWidth());
		for (int w = 0; w < map_[h].size(); w++) {
			map_[h][w] = csv.GetValue(h, w);
			BoxCollider* collision = new BoxCollider(XMFLOAT3((float)w + 0.5f, -0.5f, (float)h + 0.5f), XMFLOAT3(1, 1, 1));
			AddCollider(collision);
		}
	}
}

//�X�V
void Stage::Update() {

}

//�`��
void Stage::Draw() {
	Transform t{};

	for (int h = 0; h < map_.size(); h++) {
		for (int w = 0; w < map_[h].size(); w++) {
			t.position_ = { (float)w, 0.0f, (float)h };
			Model::SetTransform(hModel_, t);
			Model::Draw(hModel_);
		}
	}
}

//�J��
void Stage::Release() {

}
