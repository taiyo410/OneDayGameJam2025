#include <DxLib.h>

#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/ResourceManager.h"

#include "../Manager/Camera.h"

#include "../Object/Player/Player.h"

#include "../Object/Target/TargetBase.h"
#include "../Object/Target/PanelTarget.h"

#include "../Application.h"

#include "GameScene.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
	DeleteGraph(backGroundImg_);
	MV1DeleteModel(fenceModel_);
}

void GameScene::Init(void)
{
	SceneManager::GetInstance().GetCamera().lock()->ChangeMode(Camera::MODE::FIXED_POINT);

	//リソースマネージャのインスタンス 
	ResourceManager& res = ResourceManager::GetInstance();
	backGroundImg_ = res.Load(ResourceManager::SRC::BACKGROUND_TITLE).handleId_;
	fenceModel_ = MV1LoadModel((Application::PATH_MODEL + "fence.mv1").c_str());

	player_ = std::make_unique<Player>();
	player_->Init();

	float posX = -500.0f;
	for (int i = 0; i < 5; i++)
	{
		auto target = std::make_unique<PanelTarget>();
		target->Init();
		target->SetPos({ posX + i * 250.0f, 0.0f,150.0f });
		targets_.push_back(std::move(target));
	}

	// マウスを表示状態にする
	SetMouseDispFlag(false);

	modeUpdate_ = std::bind(&GameScene::PannelRule, this);
}

void GameScene::Update(void)
{


	PannelRule();


#ifdef _DEBUG

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
	{
		// マウスを表示状態にする
		SetMouseDispFlag(true);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::RESULT);
	}

#endif // DEBUG

	
}

void GameScene::Draw(void)
{
	DrawGraph(0, 0, backGroundImg_, true);

	DrawBox(0, 0, 100, 100, 0x0000ff, true);

	for (auto& target : targets_)
	{
		target->Draw();
	}

	MV1DrawModel(fenceModel_);

	player_->Draw();

	DrawLine(Application::SCREEN_SIZE_X / 2, 0, Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y, 0x00ff00);

	DrawSphere3D({ 0,0,0 }, 10, 10, 0xff0000, 0xff0000, false);

	for (auto& target : targets_)
	{
		if (target->InRange(player_->GetReticle()))
		{
			target->DebugDraw();
		}
	}
}

void GameScene::Release(void)
{
}

//パネルゲームモード
void GameScene::PannelRule()
{
	auto& ins = InputManager::GetInstance();
	Vector2 moPos = ins.GetMousePos();

	player_->Update();



	bool isWipeOut = true;
	for (auto& target : targets_)
	{
		target->Update();

		//ターゲットが全滅しているか
		if (target->IsState(TargetBase::STATE::ALIVE) || target->IsState(TargetBase::STATE::POP_UP)
			|| target->IsState(TargetBase::STATE::POP_DOWN))
		{
			isWipeOut = false;
		}

		if (player_->IsAttrck() && target->InRange(player_->GetReticle())
			&& (target->IsState(TargetBase::STATE::ALIVE) || target->IsState(TargetBase::STATE::POP_UP)))
		{
			//衝突
			target->ChangeState(TargetBase::STATE::POP_DOWN);
		}
	}

	//全滅していたなら
	if (isWipeOut)
	{
		for (auto& target : targets_)
		{
			target->CharChange();
			target->ChangeState(TargetBase::STATE::POP_UP);
		}
	}

}
//缶ゲームモード
void GameScene::CanRule()
{
}
