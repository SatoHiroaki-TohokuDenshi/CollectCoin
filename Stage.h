#pragma once
#include <vector>
#include "Engine/GameObject.h"

//Stage���Ǘ�����N���X
class Stage : public GameObject {
private:
	int hModel_;    //���f���ԍ�
	std::vector<std::vector<int>> map_;

public:
	//�R���X�g���N�^
	Stage(GameObject* parent);

	//�f�X�g���N�^
	~Stage();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	int GetModelHandle() { return hModel_; }
};
