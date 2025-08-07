#include <DxLib.h>

#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"

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
	reticleHndle_ = LoadGraph((Application::PATH_IMAGE + "crosshair184.png").c_str());
}

void GameScene::Update(void)
{
	auto& ins = InputManager::GetInstance();
	Vector2 moPos = ins.GetMousePos();



	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::RESULT);
	}
}

void GameScene::Draw(void)
{
	DrawBox(0, 0, 100, 100, 0x0000ff, true);

	auto& ins = InputManager::GetInstance();
	Vector2 moPos = ins.GetMousePos();


	DrawRotaGraph(moPos.x, moPos.y, 1.0f, 1.0f, reticleHndle_, false);

}

void GameScene::Release(void)
{
}
