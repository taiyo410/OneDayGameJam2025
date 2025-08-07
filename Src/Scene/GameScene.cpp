#include <DxLib.h>

#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/ResourceManager.h"

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
	player_ = std::make_unique<Player>();
	player_->Init();


	for (int i = 0; i < 5; i++)
	{
		auto target = std::make_unique<TargetBase>();
		target->Init();
		targets_.push_back(std::move(target));
	}

	// マウスを表示状態にする
	SetMouseDispFlag(false);
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

}

void GameScene::Release(void)
{
}
