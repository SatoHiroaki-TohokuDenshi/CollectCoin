#pragma once
#include "Engine/GameObject.h"

//�R�C�����Ǘ�����N���X
class Coin : public GameObject {
private:
    int hModel_;    //���f���ԍ�

public:
    //�R���X�g���N�^
    Coin(GameObject* parent);

    //�f�X�g���N�^
    ~Coin();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�����ɓ�������
    //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;
};
