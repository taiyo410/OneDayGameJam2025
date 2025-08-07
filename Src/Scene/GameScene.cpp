#include <DxLib.h>

#include "../Manager/SceneManager.h"

#include "GameScene.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
}

void GameScene::Update(void)
{

	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::RESULT);

}

void GameScene::Draw(void)
{
	DrawBox(0, 0, 100, 100, 0x0000ff, true);
}

void GameScene::Release(void)
{
}
