#include"../../Utility/AsoUtility.h"
#include"../../Manager/SceneManager.h"
#include "Panel.h"

Panel::Panel(void)
{
	appearCnt_ = 0.0f;
}

Panel::~Panel(void)
{
}

void Panel::Init(void)
{
	
}

void Panel::Update(void)
{
	switch (state_)
	{
	case TargetBase::STATE::ALIVE:
		AliveUpdate();
		break;
	case TargetBase::STATE::DEATH:
		break;
	default:
		break;
	}
}

void Panel::Draw(void)
{

}

void Panel::Release(void)
{
}

void Panel::AliveUpdate(void)
{
	//appearCnt_ -= SceneManager::GetInstance().GetDeltaTime();
	//if (appearCnt_ <= 0.0f)
	//{
	//	
	//}
}

void Panel::DesideTarget(void)
{
	TYPE type = static_cast<TYPE>(GetRand(static_cast<int>(TYPE::MAX)));
}
