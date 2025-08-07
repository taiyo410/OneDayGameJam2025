#include <DxLib.h>
#include "FpsControl.h"
#include "../Application.h"

FpsControl::FpsControl()
{
	currentTime_ = 0;
	prevFrameTime_ = 0;
	frameCnt_ = 0;
	updateFrameRateTime_ = 0;
	frameCnt_ = 0.0f;
}

FpsControl::~FpsControl()
{
}

void FpsControl::Init()
{
	//������
	currentTime_ = 0;
	prevFrameTime_ = 0;
	frameCnt_ = 0;
	updateFrameRateTime_ = 0;
	frameCnt_ = 0.0f;
}

bool FpsControl::UpdateFrameRate()
{
	Sleep(1);	//�V�X�e���ɏ�����Ԃ�

	//���݂̎������擾
	currentTime_ = GetNowCount();

	//���݂̎������A�O��̃t���[�����s�����
	//1/60�b�o�߂��Ă����珈�������s����
	if (currentTime_ - prevFrameTime_ >= FRAME_RATE)
	{
		//�t���[�����s���̎��Ԃ��v�Z
		prevFrameTime_ = currentTime_;

		//�t���[�������J�E���g
		frameCnt_++;

		//1/60�o�߂���
		return true;
	}

	return false;
}

void FpsControl::CalcFrameRate()
{
	//�O��̃t���[�����[�g�X�V����̌o�ߎ��Ԃ����߂�
	int difTime = currentTime_ - updateFrameRateTime_;

	//�O��̃t���[�����[�g���X�V����
	//1�b�ȏ�o�߂��Ă�����t���[�����[�g���X�V����
	if (difTime > 1000)
	{
		//�t���[���񐔂��~���b�ɍ��킹��
		//�����܂ŏo�����̂�float�ɃL���X�g
		float castFrameCnt = (float)(frameCnt_ * 1000);

		//�t���[�����[�g�����߂�
		//���z�ʂ�Ȃ� 60000 / 1000 ��60�ƂȂ�
		frameRate_ = castFrameCnt / difTime;

		//�t���[�����[�g�X�V���Ԃ��X�V
		updateFrameRateTime_ = currentTime_;
	}
}

void FpsControl::DrawFrameRate()
{
	//�f�o�b�O�p�\��

	//�X�N���[���̉E�[�ɏo��悤�ɕ\��
	DrawFormatString(
		Application::SCREEN_SIZE_X - 90,
		0,
		0xff0000,
		"FPS[%.2f]",
		frameRate_);
}
