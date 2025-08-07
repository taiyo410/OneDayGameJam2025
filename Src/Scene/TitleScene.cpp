#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/ResourceManager.h"
#include "../Application.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	//リソースマネージャのインスタンス 
	ResourceManager& res = ResourceManager::GetInstance();
	//背景画像ロード
	princessImg_ = res.Load(ResourceManager::SRC::PRINCESS).handleId_;
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
	//DrawBox(0, 0, 100, 100, 0xff0000, true);

	DrawGraph(100, 100, princessImg_, true);
}

void TitleScene::Release(void)
{
}
