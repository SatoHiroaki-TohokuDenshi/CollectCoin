#pragma once
#include <vector>
#include <string>

//-----------------------------------------------------------
//CSV�t�@�C���������N���X
//-----------------------------------------------------------
class CsvReader {
	//�ǂݍ��񂾃f�[�^�����Ă���2�����z��
	std::vector<std::vector<std::string>> data_;

	//�u,�v���u���s�v�܂ł̕�������擾
	//�����Freuult	���ʂ�����A�h���X
	//�����Fdata	���Ƃ̕�����f�[�^
	//�����Findex	�������ڂ��璲�ׂ邩
	//�ߒl�F�Ȃ�
	void GetToComma(std::string *result, std::string data, DWORD* index);

public:
	//�R���X�g���N�^
	CsvReader();

	//�f�X�g���N�^
	~CsvReader();

	//CSV�t�@�C���̃��[�h
	//�����FfileName�@�t�@�C����
	//�ߒl�F������true�@���s��false
	bool Load(std::string fileName);


	//�w�肵���ʒu�̃f�[�^�𕶎���Ŏ擾
	//�����Fw,h�@�擾�������ʒu
	//�ߒl�F�擾����������
	std::string GetString(DWORD w, DWORD h);

	//�w�肵���ʒu�̃f�[�^�𐮐��Ŏ擾
	//�����Fw,h�@�擾�������ʒu
	//�ߒl�F�擾�����l
	int GetValue(DWORD w, DWORD h);

	//�t�@�C���̗񐔂��擾
	//�����F�Ȃ�
	//�ߒl�F��
	size_t GetWidth();

	//�t�@�C���̍s�����擾
	//�����F�Ȃ�
	//�ߒl�F�s��
	size_t GetHeight();
};
