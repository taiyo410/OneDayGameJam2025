#include "../../Utility/AsoUtility.h"
#include "../../Application.h"

#include "../../Manager/SceneManager.h"
#include "../../Manager/Camera.h"

#include "CanTarget.h"

CanTarget::CanTarget(std::unique_ptr<Player>& player):player_(player)
{
	jumpPow_ = { 0.0f,0.0f,0.0f };
}

CanTarget::~CanTarget(void)
{
}

void CanTarget::Init(void)
{
	trans_.modelId = MV1LoadModel((Application::PATH_MODEL + "Can/Can.mv1").c_str());

	trans_.scl = VScale(AsoUtility::VECTOR_ONE, 0.1f);
	// 初期座標
	trans_.pos = { 0.0f,0.0f,0.0f };
	trans_.quaRot =
		Quaternion::Euler({ AsoUtility::Deg2RadF(0.0f), AsoUtility::Deg2RadF(0.0f),  AsoUtility::Deg2RadF(0.0f) });
	trans_.quaRotLocal =
		Quaternion::Euler({ AsoUtility::Deg2RadF(0.0f), AsoUtility::Deg2RadF(0.0f),  AsoUtility::Deg2RadF(0.0f) });
	trans_.Update();

	ChangeState(STATE::ALIVE);

	size_ = Vector2(100, 100);


	jumpDir_ = { 0.0f,0.0f,0.0f };
	jumpStep_ = 0.0f;
}

void CanTarget::Update(void)
{
	//重力移動
	// 重力方向
	VECTOR dirGravity = AsoUtility::DIR_D;

	// 重力の強さ
	float gravityPow = 2.0f;

	// 重力
	VECTOR gravity = VScale(dirGravity, gravityPow);
	jumpPow_ = VAdd(jumpPow_, gravity);

	// 最初は実装しない。地面と突き抜けることを確認する。
	// 内積
	float dot = VDot(dirGravity, jumpPow_);
	if (dot >= 0.0f)
	{
		// 重力方向と反対方向(マイナス)でなければ、ジャンプ力を無くす
		jumpPow_ = gravity;
	}

	jumpStep_ -= SceneManager::GetInstance().GetDeltaTime();
	if (jumpStep_ <= 0.0f)
	{
		jumpStep_ = 0.0f;
	}


	// ジャンプ量を加算
	trans_.pos = VAdd(trans_.pos, jumpPow_);
	trans_.pos = VAdd(trans_.pos, VScale(jumpDir_, jumpStep_));


	if (trans_.pos.y < 0.0f)
	{
		trans_.pos.y = 0.0f;
		if (IsState(TargetBase::STATE::ALIVE))
		{
			ChangeState(TargetBase::STATE::POP_DOWN);
		}
	}
	if (trans_.pos.x < -600.0f)
	{
		trans_.pos.x = -600.0f;
	}
	if (trans_.pos.x > 600.0f)
	{
		trans_.pos.x = 600.0f;
	}

	SetDrawScreen(SceneManager::GetInstance().GetMainScreen());
	SceneManager::GetInstance().GetCamera().lock()->SetBeforeDraw();

	VECTOR twoDPos = ConvWorldPosToScreenPos(trans_.pos);


	trans_.Update();
}

void CanTarget::Draw(void)
{
	MV1DrawModel(trans_.modelId);

	VECTOR twoDPos = ConvWorldPosToScreenPos(trans_.pos);
	Vector2 start = Vector2(twoDPos.x - size_.x / 2, twoDPos.y - size_.y);
	Vector2 end = Vector2(twoDPos.x + size_.x / 2, twoDPos.y);

	DrawBox(start.x, start.y, end.x, end.y, 0xff0000, false);

	DrawFormatString(twoDPos.x, twoDPos.y, 0xffffff, "%2.f,%2.f", trans_.pos.x, trans_.pos.y);
}

void CanTarget::SetHost(int id)
{
	playerId_ = id;
}

void CanTarget::Hit(Vector2F mPos)
{
	SetDrawScreen(SceneManager::GetInstance().GetMainScreen());
	SceneManager::GetInstance().GetCamera().lock()->SetBeforeDraw();

	ChangeState(TargetBase::STATE::ALIVE);

	VECTOR twoDPos = ConvWorldPosToScreenPos(trans_.pos);
	twoDPos.y -= size_.y / 2;

	
	Vector2F dir = Vector2F(twoDPos.x - mPos.x, mPos.y - twoDPos.y);
	jumpDir_ = VAdd({ dir.x,dir.y,0.0f }, AsoUtility::DIR_U);
	jumpDir_ = VNorm(jumpDir_);

	jumpStep_ = 5.0f;
}

bool CanTarget::OutXline(void)
{
	SetDrawScreen(SceneManager::GetInstance().GetMainScreen());
	SceneManager::GetInstance().GetCamera().lock()->SetBeforeDraw();

	VECTOR twoDPos = ConvWorldPosToScreenPos(trans_.pos);

	if (twoDPos.x > Application::SCREEN_SIZE_X
		|| twoDPos.x < 0)
	{
		return true;
	}

	return false;
}

void CanTarget::ChangeState(const STATE _state)
{
	if (state_ == _state)return;
	state_ = _state;
	switch (state_)
	{
	case TargetBase::STATE::POP_UP:
		break;
	case TargetBase::STATE::POP_DOWN:
		break;
	case TargetBase::STATE::ALIVE:
		break;
	case TargetBase::STATE::DEATH:
		isScorePlus_ = false;
		break;
	default:
		break;
	}
}
