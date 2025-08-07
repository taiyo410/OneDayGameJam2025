#include <DxLib.h>

#include "../Manager/SceneManager.h"

#include "ResultScene.h"

ResultScene::ResultScene(void)
{
}

ResultScene::~ResultScene(void)
{
}

void ResultScene::Init(void)
{
}

void ResultScene::Update(void)
{

	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);

}

void ResultScene::Draw(void)
{
	DrawBox(0, 0, 100, 100, 0x00ff00, true);
}

void ResultScene::Release(void)
{
}
