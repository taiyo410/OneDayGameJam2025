#pragma once

#include <string>
#include"../Scene/SelectScene.h"
class DataBank
{
public:	
	/// <summary>
	/// �����I�ɃC���X�e���X�𐶐�����
	/// </summary>
	/// <param name=""></param>
	static void CreateInstance(void);

	/// <summary>
	/// �ÓI�C���X�^���X�̎擾
	/// </summary>
	/// <param name=""></param>
	/// <returns>�C���X�^���X��Ԃ�</returns>
	static DataBank& GetInstance(void);

	/// <summary>
	/// ������
	/// </summary>
	/// <param name=""></param>
	void Init(void);

	/// <summary>
	/// �������
	/// </summary>
	/// <param name=""></param>
	void Destroy(void);

	/// <summary>
	/// �v���C���[�l����ݒ�
	/// </summary>
	/// <param name="num">�v���C���[�l��</param>
	/// <returns>�������ݒ�ł����true,��肪�N�����false</returns>
	bool SetPlayerNum(int _num);
	

	/// <summary>
	/// �v���C���[�l����Ԃ�
	/// </summary>
	/// <param name=""></param>
	/// <returns>�v���C���[�l��</returns>
	int GetPlayerNum(void);

	/// <summary>
	/// �Z���N�g�V�[����ID���擾
	/// </summary>
	/// <param name="_id"></param>
	/// <returns>�Z���N�gID</returns>
	const SelectScene::SELECT_ID GetSelectId(void)const;

	/// <summary>
	/// �Z���N�gID��ݒ�
	/// </summary>
	/// <param name="_id"></param>
	void SetSelectId(const SelectScene::SELECT_ID _id);




private:


	static DataBank* instance_;
	DataBank(void);
	DataBank(const DataBank& instance_) = default;
	~DataBank(void);
	int playerNum_;		//�v���C���[�̐l��
	int maxPlayerNum_;	//�R���g���[���[�����v���C���[�l���������Ȃ�Ȃ��悤�ɂ���

	SelectScene::SELECT_ID selectId_;	//�I���V�[����ID

};

