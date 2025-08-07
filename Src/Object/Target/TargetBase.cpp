
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"


#include "TargetBase.h"

TargetBase::TargetBase(void)
{
}

TargetBase::~TargetBase(void)
{
	MV1DeleteModel(trans_.modelId);
}

void TargetBase::Load(void)
{
}

void TargetBase::Init(void)
{
	// モデルの基本設定
	trans_.modelId = MV1LoadModel((Application::PATH_MODEL + "Enemy/enemy.mv1").c_str());
	trans_.scl = AsoUtility::VECTOR_ONE;
	// 初期座標
	trans_.pos = { 0.0f,0.0f,0.0f };
	trans_.quaRot =
		Quaternion::Euler({ AsoUtility::Deg2RadF(90.0f), AsoUtility::Deg2RadF(0.0f),  AsoUtility::Deg2RadF(0.0f) });
	trans_.quaRotLocal =
		Quaternion::Euler({ AsoUtility::Deg2RadF(0.0f), AsoUtility::Deg2RadF(0.0f),  AsoUtility::Deg2RadF(0.0f) });
	trans_.Update();

	ChangeState(STATE::POP_UP);
}

void TargetBase::Update(void)
{
	

	// 回転の球面補間
	stepTime_ -= scnMng_.GetDeltaTime();

	trans_.quaRot = Quaternion::Slerp(
		trans_.quaRot, goalQua_, (limitTime_ - stepTime_) / limitTime_);

	if (stepTime_ < 0.0f)
	{
		switch (state_)
		{
		case STATE::POP_UP:
			ChangeState(STATE::ALIVE);			
			break;
		case STATE::POP_DOWN:
			ChangeState(STATE::DEATH);		
			break;
		case STATE::ALIVE:
	
			break;
		case STATE::DEATH:
			ChangeState(STATE::POP_UP);
			break;
		}
	}

	trans_.Update();
}

void TargetBase::Draw(void)
{
	MV1DrawModel(trans_.modelId);

	VECTOR twoDPos = ConvWorldPosToScreenPos(trans_.pos);
	Vector2 start = Vector2(twoDPos.x - 30, twoDPos.y - 50);
	Vector2 end = Vector2(twoDPos.x + 30, twoDPos.y + 50);

	DrawBox(start.x, start.y, end.x, end.y, 0xff0000, false);

	DrawFormatString(100, 16, 0x000000, "%2.f,%2.f,%2.f", twoDPos.x, twoDPos.y, twoDPos.z);
}

void TargetBase::SetPos(VECTOR pos)
{
	trans_.pos = pos;
	trans_.Update();
}

void TargetBase::Release(void)
{
}

bool TargetBase::InRange(Vector2 mPos)
{
	VECTOR twoDPos = ConvWorldPosToScreenPos(trans_.pos);
	Vector2 start = Vector2(twoDPos.x - 30, twoDPos.y - 50);
	Vector2 end = Vector2(twoDPos.x + 30, twoDPos.y + 50);


	return (start.x <= mPos.x && start.y <= mPos.y
		&& end.x >= mPos.x && end.y >= mPos.y);
}

void TargetBase::ChangeState(STATE state)
{
	state_ = state;

	switch (state_)
	{
	case STATE::POP_UP:

		goalQua_ =
			Quaternion::Euler({ AsoUtility::Deg2RadF(0.0f), AsoUtility::Deg2RadF(0.0f),  AsoUtility::Deg2RadF(0.0f) });
		limitTime_ = 10.0f;//完了までの時間
		stepTime_ = limitTime_;//経過時間

			break;
	case STATE::POP_DOWN:

		goalQua_ =
			Quaternion::Euler({ AsoUtility::Deg2RadF(90.0f), AsoUtility::Deg2RadF(0.0f),  AsoUtility::Deg2RadF(0.0f) });
		limitTime_ = 10.0f;//完了までの時間
		stepTime_ = limitTime_;//経過時間

			break;
	case STATE::ALIVE:

		goalQua_ =
			Quaternion::Euler({ AsoUtility::Deg2RadF(0.0f), AsoUtility::Deg2RadF(0.0f),  AsoUtility::Deg2RadF(0.0f) });
		limitTime_ = 0.0f;//完了までの時間
		stepTime_ = limitTime_;//経過時間

			break;
	case STATE::DEATH:

		goalQua_ =
			Quaternion::Euler({ AsoUtility::Deg2RadF(90.0f), AsoUtility::Deg2RadF(0.0f),  AsoUtility::Deg2RadF(0.0f) });
		limitTime_ = 0.0f;//完了までの時間
		stepTime_ = limitTime_;//経過時間

			break;
	}

}
