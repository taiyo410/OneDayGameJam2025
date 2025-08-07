#include <DxLib.h>

#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"

#include "TitleScene.h"

TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
}

void TitleScene::Update(void)
{
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}
}

void TitleScene::Draw(void)
{
	DrawBox(0, 0, 100, 100, 0xff0000, true);
}

void TitleScene::Release(void)
{
}
