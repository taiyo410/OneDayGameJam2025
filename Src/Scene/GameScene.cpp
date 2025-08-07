#include <DxLib.h>

#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/ResourceManager.h"

#include "../Object/Player/Player.h"

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


	// マウスを表示状態にする
	SetMouseDispFlag(false);
}

void GameScene::Update(void)
{
	auto& ins = InputManager::GetInstance();
	Vector2 moPos = ins.GetMousePos();

	player_->Update();

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

	player_->Draw();

}

void GameScene::Release(void)
{
}
