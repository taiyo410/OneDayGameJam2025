#include <DxLib.h>
#include "../Application.h"
#include "../Common/Vector2.h"
#include "../Manager/ResourceManager.h"
#include "SelecteScene.h"

SelecteScene::SelecteScene(void)
{
}

SelecteScene::~SelecteScene(void)
{
}

void SelecteScene::Init(void)
{
	//リソースマネージャのインスタンス 
	ResourceManager& res = ResourceManager::GetInstance();
	backImg_ = res.Load(ResourceManager::SRC::BACKSELECT).handleId_;
	MultiImg_ = res.Load(ResourceManager::SRC::SELECT_MELTI).handleId_;
	endlessImg_ = res.Load(ResourceManager::SRC::SELECT_ENDLESS).handleId_;
}

void SelecteScene::Update(void)
{
}

void SelecteScene::Draw(void)
{
	
	//画面中心座標
	Vector2 basePos = { Application::SCREEN_SIZE_X / 2 ,Application::SCREEN_SIZE_Y / 2 };

	//box補正値
	int boxX = 50;
	int boxY = 20;

	/*ボックス座標*/
	//左
	Vector2 boxPos1 = { basePos.x - boxX, basePos.y - boxY };
	//右
	Vector2 boxPos2 = { basePos.x + boxX, basePos.y + boxY };

	//ボードの描画
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1.15f, 0.0f, backImg_, true);

	//選択
	DrawBox(
		boxPos1.x,
		boxPos1.y,
		boxPos2.x,
		boxPos2.y,
		GetColor(255, 255, 255),
		true);

	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 0.5f, 0.0f, MultiImg_, true);
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 0.5f, 0.0f, endlessImg_, true);
}

void SelecteScene::Release(void)
{
	DeleteGraph(backImg_);
	DeleteGraph(MultiImg_);
	DeleteGraph(endlessImg_);
}
