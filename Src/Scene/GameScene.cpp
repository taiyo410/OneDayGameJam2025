#include <DxLib.h>

#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/ResourceManager.h"

#include "../Manager/Camera.h"

#include "../Object/Player/Player.h"

#include "../Object/Target/TargetBase.h"

#include "../Application.h"

#include "GameScene.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	SceneManager::GetInstance().GetCamera().lock()->ChangeMode(Camera::MODE::FIXED_POINT);

	player_ = std::make_unique<Player>();
	player_->Init();

	float posX = -400.0f;
	for (int i = 0; i < 5; i++)
	{
		auto target = std::make_unique<TargetBase>();
		target->Init();
		target->SetPos({ posX + i * 200.0f, 0.0f,150.0f });
		targets_.push_back(std::move(target));
	}

	// マウスを表示状態にする
	SetMouseDispFlag(false);

	modeUpdate_ = std::bind(&GameScene::PannelRule, this);
}

void GameScene::Update(void)
{
	auto& ins = InputManager::GetInstance();
	Vector2 moPos = ins.GetMousePos();

	player_->Update();
	



	for (auto& target : targets_)
	{
		target->Update();

		if (player_->IsAttrck() && target->InRange(player_->GetReticle()))
		{
			//衝突
			int x = 0;

		}
	}

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
	{
		// マウスを非表示状態にする
		SetMouseDispFlag(true);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::RESULT);
	}


	
}

void GameScene::Draw(void)
{
	DrawBox(0, 0, 100, 100, 0x0000ff, true);

	for (auto& target : targets_)
	{
		target->Draw();
	}

	player_->Draw();

	DrawLine(Application::SCREEN_SIZE_X / 2, 0, Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y, 0x00ff00);

	DrawSphere3D({ 0,0,0 }, 10, 10, 0xff0000, 0xff0000, false);
}

void GameScene::Release(void)
{
}

//パネルゲームモード
void GameScene::PannelRule()
{





}
//缶ゲームモード
void GameScene::CanRule()
{
}
