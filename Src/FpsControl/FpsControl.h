#pragma once

//�t���[�����[�g
static constexpr float FRAME_RATE(1000 / 60);

class FpsControl
{
public:

	FpsControl();	// �R���X�g���N�^
	~FpsControl();	// �f�X�g���N�^

	//������
	void Init();

	//�t���[�����[�g�X�V
	bool UpdateFrameRate();

	//�t���[�����[�g�v�Z
	void CalcFrameRate();

	//�t���[�����[�g�\��(�f�o�b�O�\��)
	void DrawFrameRate();

private:

	//���݂̎���
	int currentTime_;

	//�O��̃t���[�����s���̎���
	int prevFrameTime_;

	//�t���[���J�E���g�p
	int frameCnt_;

	//�t���[�����[�g���X�V��������
	int updateFrameRateTime_;

	//�t���[�����[�g(�\���p)
	float frameRate_;

};

