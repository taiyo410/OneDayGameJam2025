
#include "../../Application.h"
#include "../../Utility/AsoUtility.h"


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

	mRot_ = 90.0f;
	goalRot_ = 0.0f;
}

void TargetBase::Update(void)
{
	//今回回転させたい回転量をクォータニオンで作る
	Quaternion rotPow = Quaternion();

	int rot = 0;
	if (goalRot_ == 90.0f)
	{
		rot = 10;
		rotPow = rotPow.Mult(
			Quaternion::AngleAxis(
				AsoUtility::Deg2RadF(AsoUtility::Deg2RadF(rot)), AsoUtility::AXIS_X
			));
	}
	else if (goalRot_ == 0.0f)
	{
		rot = -10; 
		rotPow = rotPow.Mult(
			Quaternion::AngleAxis(
				AsoUtility::Deg2RadF(AsoUtility::Deg2RadF(rot)), AsoUtility::AXIS_X
			));
	}

	mRot_ += AsoUtility::Deg2RadF(rot);
	if (mRot_ >= 90.0f&& goalRot_ == 90.0f)
	{
		goalRot_ = 0.0f;
	}
	if (mRot_ <= 0.0f&& goalRot_ == 0.0f)
	{
		goalRot_ = 90.0f;
	}

	// 回転諒を加える(合成)
	trans_.quaRot = trans_.quaRot.Mult(rotPow);

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
