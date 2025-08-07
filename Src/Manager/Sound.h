#pragma once
#include<string>
#include<DxLib.h>


class Sound
{
public:

	// �T�E���h�^�C�v
	enum class TYPE
	{
		NONE,
		SOUND_2D,	//2D����
		SOUND_3D,	//3D����
	};

	enum class TIMES
	{
		ONCE,	//1��
		LOOP,	//�J��Ԃ�
	};

	// �R���X�g���N�^
	Sound(void);
	// �R���X�g���N�^
	Sound(TYPE type, const std::string& path);

	// �f�X�g���N�^
	~Sound(void);

	//3D ���W�X�V����
	void Update(VECTOR pos);

	// �ǂݍ���
	void Load(void);

	// ���
	void Release(void);


	TYPE soundType_;


	// ���\�[�X�̓ǂݍ��ݐ�
	std::string path_;


	// ���̃n���h��ID
	int handleId_;


	//���̍ő剹��
	int maxVolume_;
	
	//3D�p
	VECTOR pos_;	//���W
	float radius_;	//�L���͈�

	//�ꎞ��~�p�i�V�K�j
	int pauseTime_; // ��~���̍Đ��ʒu�i�~���b�j
	bool isPaused_;

	bool Play(TIMES times, bool isForce = false);						//2D�p�����Đ�
	bool Play(VECTOR pos, float radius, TIMES times);	//3D�p�����Đ�

	void Stop(void);	//�Đ����̉������~����

	//�V�K
	void Pause(TIMES times);
	void Resume(TIMES times);



	bool CheckMove(void);	//�Đ��������m�F

	bool CheckLoad(void);	//���[�h���Ă��邩���m�F

	void ChengeVolume(float per);	//���̑傫����ς���

	void ChengeMaxVolume(float per);
};