#include "../../Application.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"

#include "PanelTarget.h"


PanelTarget::PanelTarget(void)
{
}

PanelTarget::~PanelTarget(void)
{
}

void PanelTarget::Init(void)
{
	// ÉÇÉfÉãÇÃäÓñ{ê›íË
	int i = rand() % 2;

	if (i == 0) {
		trans_.modelId = MV1LoadModel((Application::PATH_MODEL + "Enemy/enemy.mv1").c_str());
	}
	else {
		trans_.modelId = MV1LoadModel((Application::PATH_MODEL + "Friend/friend.mv1").c_str());
	}
	trans_.scl = AsoUtility::VECTOR_ONE;
	// èâä˙ç¿ïW
	trans_.pos = { 0.0f,0.0f,0.0f };
	trans_.quaRot =
		Quaternion::Euler({ AsoUtility::Deg2RadF(90.0f), AsoUtility::Deg2RadF(0.0f),  AsoUtility::Deg2RadF(0.0f) });
	trans_.quaRotLocal =
		Quaternion::Euler({ AsoUtility::Deg2RadF(0.0f), AsoUtility::Deg2RadF(0.0f),  AsoUtility::Deg2RadF(0.0f) });
	trans_.Update();

	ChangeState(STATE::POP_UP);

	size_ = Vector2(180, 300);
}

void PanelTarget::Update(void)
{
	// âÒì]ÇÃãÖñ ï‚ä‘
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

void PanelTarget::Draw(void)
{
	MV1DrawModel(trans_.modelId);

	
}
