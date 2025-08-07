
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/Camera.h"

#include "TargetBase.h"

TargetBase::TargetBase(void)
{
	state_ = STATE::POP_UP;

	limitTime_ = 0.0f;
	stepTime_ = 0.0f;

	isScorePlus_ = false;
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
	int i = rand() % 2;

	if (i == 0){
		trans_.modelId = MV1LoadModel((Application::PATH_MODEL + "Enemy/enemy.mv1").c_str());
		isScorePlus_ = true;
	}
	else{
		trans_.modelId = MV1LoadModel((Application::PATH_MODEL + "Friend/friend.mv1").c_str());
		isScorePlus_ = false;
	}
	trans_.scl = AsoUtility::VECTOR_ONE;
	// 初期座標
	trans_.pos = { 0.0f,0.0f,0.0f };
	trans_.quaRot =
		Quaternion::Euler({ AsoUtility::Deg2RadF(90.0f), AsoUtility::Deg2RadF(0.0f),  AsoUtility::Deg2RadF(0.0f) });
	trans_.quaRotLocal =
		Quaternion::Euler({ AsoUtility::Deg2RadF(0.0f), AsoUtility::Deg2RadF(0.0f),  AsoUtility::Deg2RadF(0.0f) });
	trans_.Update();

	ChangeState(STATE::POP_UP);

	size_ = Vector2(180, 300);
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
			ChangeState(STATE::POP_DOWN);
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
	Vector2 start = Vector2(twoDPos.x - size_.x/2, twoDPos.y - size_.y);
	Vector2 end = Vector2(twoDPos.x + size_.x / 2, twoDPos.y);

	DrawBox(start.x, start.y, end.x, end.y, 0xff0000, false);

	DrawFormatString(100, 16, 0x000000, "%2.f,%2.f,%2.f", twoDPos.x, twoDPos.y, twoDPos.z);

	DrawFormatString(twoDPos.x, 500, 0xffffff, "%2.f", twoDPos.x);
	DrawFormatString(twoDPos.x, 516, 0xffffff, "%2.f", twoDPos.y);
	DrawFormatString(twoDPos.x, 532, 0xffffff, "%.2f", stepTime_);
}

void TargetBase::DebugDraw(void)
{
	/*
	VECTOR twoDPos = ConvWorldPosToScreenPos(trans_.pos);
	Vector2 start = Vector2(twoDPos.x - size_.x / 2, twoDPos.y - size_.y);
	Vector2 end = Vector2(twoDPos.x + size_.x / 2, twoDPos.y );

	DrawBox(start.x, start.y, end.x, end.y, 0xff0000, true);
	DrawCircle(twoDPos.x, twoDPos.y, 10, 0x00ff00);*/
}

void TargetBase::Release(void)
{
}

void TargetBase::SetPos(const VECTOR pos)
{
	trans_.pos = pos;
	trans_.Update();
}

bool TargetBase::InRange(Vector2F mPos)
{
	SetDrawScreen(SceneManager::GetInstance().GetMainScreen());
	SceneManager::GetInstance().GetCamera().lock()->SetBeforeDraw();

	VECTOR twoDPos = ConvWorldPosToScreenPos(trans_.pos);
	Vector2 start = Vector2(twoDPos.x - size_.x / 2, twoDPos.y - size_.y);
	Vector2 end = Vector2(twoDPos.x + size_.x / 2, twoDPos.y);


	return (start.x <= mPos.x && start.y <= mPos.y
		&& end.x >= mPos.x && end.y >= mPos.y);
}

void TargetBase::ChangeState(const STATE state)
{
	state_ = state;

	switch (state_)
	{
	case STATE::POP_UP:

		trans_.quaRot =
			Quaternion::Euler({ AsoUtility::Deg2RadF(90.0f), AsoUtility::Deg2RadF(0.0f),  AsoUtility::Deg2RadF(0.0f) });
		goalQua_ =
			Quaternion::Euler({ AsoUtility::Deg2RadF(0.0f), AsoUtility::Deg2RadF(0.0f),  AsoUtility::Deg2RadF(0.0f) });
		limitTime_ = 1.0f;//完了までの時間
		stepTime_ = limitTime_;//経過時間

			break;
	case STATE::POP_DOWN:

		goalQua_ =
			Quaternion::Euler({ AsoUtility::Deg2RadF(90.0f), AsoUtility::Deg2RadF(0.0f),  AsoUtility::Deg2RadF(0.0f) });
		limitTime_ = 1.0f;//完了までの時間
		stepTime_ = limitTime_;//経過時間

			break;
	case STATE::ALIVE:

		//待機時間
		stepTime_ = 1.5f;

			break;
	case STATE::DEATH:

		//待機時間
		stepTime_ = 3.5f;

			break;
	}

}

void TargetBase::Hit(Vector2F mPos)
{
}

void TargetBase::CharChange()
{
	int i = rand() % 2;

	MV1DeleteModel(trans_.modelId);

	if (i==0)
	{
		trans_.modelId = MV1LoadModel((Application::PATH_MODEL + "Enemy/enemy.mv1").c_str());
		isScorePlus_ = true;
	}
	else
	{
		trans_.modelId = MV1LoadModel((Application::PATH_MODEL + "Friend/friend.mv1").c_str());
		isScorePlus_ = false;
	}
	trans_.Update();
}

const VECTOR TargetBase::GetCenter(void)
{
	
	const auto& cPos = VAdd(trans_.pos, VScale(trans_.GetUp(), size_.y / 2));
	return cPos;
}
