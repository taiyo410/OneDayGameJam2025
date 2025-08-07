#include <cmath>
#include <DxLib.h>
#include "../Application.h"
#include "../Common/Vector2.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/DataBank.h"
#include "SelectScene.h"

SelectScene::SelectScene(void)
{
	Init();
	isMultiSelect_ = false;
	selectId_ = SELECT_ID::MULTI;
	multiImgScl_ = 0.25f;
	endlessImgScl_ = 0.25f;
	panelImgScl_ = 0.25f;
	sclTime_ = 0.0f;
	playerNum_ = 0;
}

SelectScene::~SelectScene(void)
{
}

void SelectScene::Init(void)
{
	//リソースマネージャのインスタンス 
	ResourceManager& res = ResourceManager::GetInstance();

	backImg_ = res.Load(ResourceManager::SRC::BACKSELECT).handleId_;
	multiImg_ = res.Load(ResourceManager::SRC::SELECT_MELTI).handleId_;
	endlessImg_ = res.Load(ResourceManager::SRC::SELECT_ENDLESS).handleId_;
	princessImg_ = res.Load(ResourceManager::SRC::PRINCESS).handleId_;
	banDitImg_ = res.Load(ResourceManager::SRC::BANDIT).handleId_;
	panelImg_ = res.Load(ResourceManager::SRC::SELECT_PANEL).handleId_;
	playerNum_ = 1;
	sclTime_ = 0.0f;
	isMultiSelect_ = false;
	selectId_ = SELECT_ID::MULTI;
}

void SelectScene::Update(void)
{

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
	{
		//選択されたIDに応じてシーンを変更
		if(selectId_ == SELECT_ID::MULTI&&!isMultiSelect_)
		{
			isMultiSelect_ = true;
			return;
		}
		else
		{
			DataBank::GetInstance().SetSelectId(selectId_);
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
		}
	}

	if (isMultiSelect_)
	{
		if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_LEFT))
		{
			if(playerNum_ > 1)
			{
				playerNum_--;
			}
			else if(playerNum_)
			{
				playerNum_ = PLAYER_MAX;
			}
		}
		else if(InputManager::GetInstance().IsTrgDown(KEY_INPUT_RIGHT))
		{
			if (playerNum_ < PLAYER_MAX)
			{
				playerNum_++;
			}
			else if (playerNum_ == PLAYER_MAX)
			{
				playerNum_ = 1;
			}
		}
		if(InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
		{
			DataBank::GetInstance().SetPlayerNum(playerNum_);
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
		}
	}

	multiImgScl_ = 0.4f;
	endlessImgScl_ = 0.4f;
	panelImgScl_ = 0.4f;

	int selectIdCnt_ = static_cast<int>(selectId_);

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_DOWN)
		&& selectIdCnt_ < 3)
	{
		selectIdCnt_++;
	}

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_UP)
		&& selectIdCnt_ > 1)
	{
		selectIdCnt_--;
	}

	SELECT_ID newselectId = static_cast<SELECT_ID>(selectIdCnt_);
	selectId_ = newselectId;


	if(selectId_ == SELECT_ID::MULTI)
	{
		multiImgScl_ = (std::sin(sclTime_) * 0.5f + 0.5f) * (1.8f - 1.5f) + 1.5f;
		multiImgScl_ *= 0.25f;
		sclTime_ += 0.05f;
	}

	if (selectId_ == SELECT_ID::PANEL)
	{
		panelImgScl_ = (std::sin(sclTime_) * 0.5f + 0.5f) * (1.8f - 1.5f) + 1.5f;
		panelImgScl_ *= 0.25f;
		sclTime_ += 0.05f;
	}

	if (selectId_ == SELECT_ID::ENDLESS)
	{
		endlessImgScl_ = (std::sin(sclTime_) * 0.5f + 0.5f) * (1.8f - 1.5f) + 1.5f;
		endlessImgScl_ *= 0.25f;
		sclTime_ += 0.05f;
	}
}

void SelectScene::Draw(void)
{

	//画面中心座標
	Vector2 basePos = { Application::SCREEN_SIZE_X / 2 ,Application::SCREEN_SIZE_Y / 2 };

	//ボードの描画
	DrawRotaGraph((Application::SCREEN_SIZE_X / 2), Application::SCREEN_SIZE_Y / 2, 1.2f, 0.0f, backImg_, true);

	if (!isMultiSelect_)
	{
		DrawRotaGraph(basePos.x, basePos.y - 170, multiImgScl_, 0.0f, multiImg_, true);
		DrawRotaGraph(basePos.x, basePos.y, endlessImgScl_, 0.0f, endlessImg_, true);
		DrawRotaGraph(basePos.x, basePos.y + 170, panelImgScl_, 0.0f, panelImg_, true);
	}


	DrawRotaGraph(basePos.x - 375, basePos.y, 0.4, -0.25f, princessImg_, true);
	DrawRotaGraph(basePos.x + 375, basePos.y, 0.4, 0.25f, banDitImg_, true);


	if (isMultiSelect_)
	{
		DrawFormatString(50, 50, 0xFFFFFFFF, "PlayerNum(%d)", playerNum_);
	}
	
}

void SelectScene::Release(void)
{
	DeleteGraph(backImg_);
	DeleteGraph(multiImg_);
	DeleteGraph(endlessImg_);
	DeleteGraph(panelImg_);
	DeleteGraph(princessImg_);
	DeleteGraph(banDitImg_);
}
