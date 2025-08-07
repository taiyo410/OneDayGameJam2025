#include "../../Utility/AsoUtility.h"
#include "../../Application.h"

#include "CanTarget.h"

CanTarget::CanTarget(void)
{
}

CanTarget::~CanTarget(void)
{
}

void CanTarget::Init(void)
{
	trans_.modelId = MV1LoadModel((Application::PATH_MODEL + "Friend/friend.mv1").c_str());

	trans_.scl = AsoUtility::VECTOR_ONE;
	// èâä˙ç¿ïW
	trans_.pos = { 0.0f,0.0f,0.0f };
	trans_.quaRot =
		Quaternion::Euler({ AsoUtility::Deg2RadF(0.0f), AsoUtility::Deg2RadF(0.0f),  AsoUtility::Deg2RadF(0.0f) });
	trans_.quaRotLocal =
		Quaternion::Euler({ AsoUtility::Deg2RadF(0.0f), AsoUtility::Deg2RadF(0.0f),  AsoUtility::Deg2RadF(0.0f) });
	trans_.Update();

	ChangeState(STATE::POP_UP);

	size_ = Vector2(150, 300);
}

void CanTarget::Update(void)
{
}

void CanTarget::Draw(void)
{
	MV1DrawModel(trans_.modelId);
}
