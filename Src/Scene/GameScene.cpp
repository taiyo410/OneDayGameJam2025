#include <DxLib.h>

#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/ResourceManager.h"

#include "../Application.h"

#include "GameScene.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
	DeleteGraph(reticleHndle_);
}

void GameScene::Init(void)
{

	//reticleHndle_ = LoadGraph((Application::PATH_IMAGE + "crosshair184.png").c_str());
	reticleHndle_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::CROSSHAIR).handleId_;

	// マウスを表示状態にする
	SetMouseDispFlag(false);
}

void GameScene::Update(void)
{
	auto& ins = InputManager::GetInstance();
	Vector2 moPos = ins.GetMousePos();



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

	auto& ins = InputManager::GetInstance();
	Vector2 moPos = ins.GetMousePos();


	DrawRotaGraph(moPos.x, moPos.y, 1.0f, 0.0f, reticleHndle_, true);

}

void GameScene::Release(void)
{
}
