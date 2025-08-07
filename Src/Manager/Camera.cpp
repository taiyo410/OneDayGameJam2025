#include <math.h>
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "../Utility/AsoUtility.h"
#include "../Object/Common/Transform.h"

#include "InputManager.h"

#include "../Application.h"

#include "Camera.h"

Camera::Camera(void)
{
	angles_ = VECTOR();
	cameraUp_ = VECTOR();
	mode_ = MODE::NONE;
	pos_ = AsoUtility::VECTOR_ZERO;
	targetPos_ = AsoUtility::VECTOR_ZERO;
	followTransform_ = nullptr;
}

Camera::~Camera(void)
{
}

void Camera::Init(void)
{

	ChangeMode(MODE::FIXED_POINT);

}

void Camera::Update(void)
{
	// ������ LookAtSmoothly ���Ăяo��

	// ��: ����̃I�u�W�F�N�g�����炩�ɒǏ]����ꍇ
	/*if (followTransform_) {
		LookAtSmoothly(followTransform_->pos, INTERPOLATION_SPEED);
	}*/
}

void Camera::SetBeforeDraw(void)
{

	// �N���b�v������ݒ肷��(SetDrawScreen�Ń��Z�b�g�����)
	SetCameraNearFar(CAMERA_NEAR, CAMERA_FAR);

	switch (mode_)
	{
	case Camera::MODE::FIXED_POINT:
		SetBeforeDrawFixedPoint();
		break;
	}

	// �J�����̐ݒ�(�ʒu�ƒ����_�ɂ�鐧��)
	SetCameraPositionAndTargetAndUpVec(
		pos_, 
		targetPos_, 
		cameraUp_
	);

	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();

}

void Camera::Draw(void)
{
}

void Camera::SetFollow(const Transform* follow)
{
	followTransform_ = follow;
}

VECTOR Camera::GetPos(void) const
{
	return pos_;
}

VECTOR Camera::GetAngles(void) const
{
	return angles_;
}

VECTOR Camera::GetTargetPos(void) const
{
	return targetPos_;
}

Quaternion Camera::GetQuaRot(void) const
{
	return rot_;
}

Quaternion Camera::GetQuaRotOutX(void) const
{
	return rotOutX_;
}

VECTOR Camera::GetForward(void) const
{
	return VNorm(VSub(targetPos_, pos_));
}

void Camera::ChangeMode(MODE mode)
{

	// �J�����̏����ݒ�
	SetDefault();

	// �J�������[�h�̕ύX
	mode_ = mode;

	// �ύX���̏���������
	switch (mode_)
	{
	case Camera::MODE::FIXED_POINT:
		// �J�����ʒu�F���_���班�����ꂽ�Ƃ���ɒu���i��F�΂ߏォ��j
		pos_ = VGet(0.0f, 200.0f, -550.0f);

		// �����_�F���_�i{0,0,0}�j
		targetPos_ = AsoUtility::VECTOR_ZERO;
		targetPos_.y = 300.0f;

		// ������iY���j
		cameraUp_ = AsoUtility::DIR_U;

		SetMouseDispFlag(true);
		break;
	}

}

void Camera::SetDefault(void)
{

	// �J�����̏����ݒ�
	pos_ = DEFAULT_CAMERA_POS;

	// �����_
	targetPos_ = AsoUtility::VECTOR_ZERO;

	// �J�����̏����
	cameraUp_ = AsoUtility::DIR_U;

	angles_.x = AsoUtility::Deg2RadF(30.0f);
	angles_.y = 0.0f;
	angles_.z = 0.0f;

	rot_ = Quaternion();

}

void Camera::SyncFollow(void)
{

	//auto& gIns = GravityManager::GetInstance();

	// ������̈ʒu
	VECTOR pos = followTransform_->pos;

	// �d�͂̕�������ɏ]��
	//Quaternion gRot = gIns.GetTransform().quaRot;
	Quaternion gRot = Quaternion();

	// ���ʂ���ݒ肳�ꂽY�����A��]������
	rotOutX_ = gRot.Mult(Quaternion::AngleAxis(angles_.y, AsoUtility::AXIS_Y));

	// ���ʂ���ݒ肳�ꂽX�����A��]������
	rot_ = rotOutX_.Mult(Quaternion::AngleAxis(angles_.x, AsoUtility::AXIS_X));

	VECTOR localPos;

	// �����_(�ʏ�d�͂ł����Ƃ����Y�l��Ǐ]�ΏۂƓ����ɂ���)
	localPos = rotOutX_.PosAxis(LOCAL_F2T_POS);
	targetPos_ = VAdd(pos, localPos);

	// �J�����ʒu
	localPos = rot_.PosAxis(LOCAL_F2C_POS);
	pos_ = VAdd(pos, localPos);

	// �J�����̏����
	cameraUp_ = gRot.GetUp();

}

void Camera::ProcessRot(void)
{
	//���K�@ �J�����̗v���ɉ����āA�J����������������Ă�������
	//	�E Y���ɁA360�x��]���邱��
	//	�E X���ɁA���40�x�A����15�x��]���邱��
	//	�E �J��������͖��L�[��p���邱��

	auto& ins = InputManager::GetInstance();


	//��]���Ɨʌ���
	//const float ROT_POW = 1.0f;
	const float ROT_POW = AsoUtility::Deg2RadF(1.0f);
	VECTOR axisDeg = AsoUtility::VECTOR_ZERO;


	if (angles_.x <= LIMIT_X_UP_RAD)
	{
		if (ins.IsNew(KEY_INPUT_DOWN)) { axisDeg.x = ROT_POW; }
	}

	if (angles_.x >= LIMIT_X_DW_RAD)
	{
		if (ins.IsNew(KEY_INPUT_UP)) { axisDeg.x = -ROT_POW; }
	}


	if (ins.IsNew(KEY_INPUT_RIGHT)) { axisDeg.y = ROT_POW; }
	if (ins.IsNew(KEY_INPUT_LEFT)) { axisDeg.y = -ROT_POW; }


	if (!AsoUtility::EqualsVZero(axisDeg))
	{
		//�����]����������]�ʂ��N�H�[�^�j�I���ō��
		Quaternion rotPow = Quaternion();

		/*rotPow = rotPow.Mult(
			Quaternion::AngleAxis(
				AsoUtility::Deg2RadF(axisDeg.z), AsoUtility::AXIS_Z
			));*/
		rotPow = rotPow.Mult(
			Quaternion::AngleAxis(
				AsoUtility::Deg2RadF(axisDeg.x), AsoUtility::AXIS_X
			));
		rotPow = rotPow.Mult(
			Quaternion::AngleAxis(
				AsoUtility::Deg2RadF(axisDeg.y), AsoUtility::AXIS_Y
			));

		// ��]�Ȃ�������(����)
		angles_ = VAdd(angles_, axisDeg);

	}

}

void Camera::SetBeforeDrawFixedPoint(void)
{
	// �������Ȃ�
}


