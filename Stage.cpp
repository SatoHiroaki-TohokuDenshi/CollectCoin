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

	std::string fileName = "map0";
	map_.resize(2);
	for (int y = 0; y < map_.size(); y++) {
		//�}�b�v�f�[�^�̓ǂݍ���
		CsvReader csv{};
		csv.Load(fileName + std::to_string(y) + ".csv");

		map_[y].resize(csv.GetWidth());
		for (int x = 0; x < map_[y].size(); x++) {
			map_[y][x].resize(csv.GetHeight());
			int h = (int)map_[y][x].size() - 1;
			for (int z = 0; z < map_[y][x].size(); z++) {
				map_[y][x][z] = csv.GetValue(x, h--);
				if (map_[y][x][z] == 1) {
					BoxCollider* collision = new BoxCollider(XMFLOAT3((float)x + 0.5f, (float)y - 0.5f, (float)z + 0.5f), XMFLOAT3(1, 1, 1));
					AddCollider(collision);
				}
			}
		}
	}
}

//�X�V
void Stage::Update() {

}

//�`��
void Stage::Draw() {
	Transform t{};

	for (int y = 0; y < map_.size(); y++) {
		for (int x = 0; x < map_[y].size(); x++) {
			for (int z = 0; z < map_[y][x].size(); z++) {
				if (map_[y][x][z] == 1) {
					t.position_ = { (float)x, (float)y, (float)z };
					Model::SetTransform(hModel_, t);
					Model::Draw(hModel_);
				}
			}
		}
	}
}

//�J��
void Stage::Release() {

}
