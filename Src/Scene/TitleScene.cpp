#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/ResourceManager.h"
#include "../Application.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
	princessPos_ = { 0,0 };
}

TitleScene::~TitleScene(void)
{
	
}

void TitleScene::Init(void)
{
	//リソースマネージャのインスタンス 
	ResourceManager& res = ResourceManager::GetInstance();

	//お姫様画像ロード
	princessImg_ = res.Load(ResourceManager::SRC::PRINCESS).handleId_;

	//盗賊画像ロード
	banDitImg_ = res.Load(ResourceManager::SRC::BANDIT).handleId_;
	
	//背景画像ロード
	backGroundImg_ = res.Load(ResourceManager::SRC::BACKGROUND_TITLE).handleId_;


}

void TitleScene::Update(void)
{
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}

	//お姫様の座標を設定
	princessPos_ = { PRINCESS_POS_X,PRINCESS_POS_Y };

	//盗賊の座標を設定
	banDitPos_ = { BANDIT_POS_X,BANDIT_POS_Y };

}

void TitleScene::Draw(void)
{
	//DrawBox(0, 0, 100, 100, 0xff0000, true);

	DrawGraph(0, 0, backGroundImg_, true);
	DrawRotaGraph(princessPos_.x, princessPos_.y, PRINCESS_RATE, PRINCESS_ANGLE, princessImg_, true);
	DrawRotaGraph(banDitPos_.x, banDitPos_.y, BANDIT_RATE, BANDIT_ANGLE, banDitImg_, true);
}

void TitleScene::Release(void)
{
	DeleteGraph(princessImg_);
	DeleteGraph(backGroundImg_);
}


