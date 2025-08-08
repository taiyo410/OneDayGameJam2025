#include <DxLib.h>
#include"../Application.h"
#include"../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/Databank.h"
#include"SelectScene.h"
#include "ResultScene.h"

ResultScene::ResultScene(void)
{
}

ResultScene::~ResultScene(void)
{
}

void ResultScene::Init(void)
{
	SelectScene::SELECT_ID selectId = DataBank::GetInstance().GetSelectId();
	switch (selectId)
	{
	case SelectScene::SELECT_ID::NOME:
		break;
	case SelectScene::SELECT_ID::CAN:
		ruleDraw_ = [this]() {MultiDraw(); };
		break;
	case SelectScene::SELECT_ID::PANEL:
		ruleDraw_ = [this]() {PanelDraw(); };
		break;
	default:
		break;
	}

	backImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::BACKSELECT).handleId_;
	numbersImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::NUMBER_IMG).handleIds_;
	scoreImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::SCORE).handleId_;
	winImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::WIN).handleId_;

	pAkaImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::PLYER_AKA).handleId_;
	pAoImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::PLYER_AO).handleId_;
	pKiImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::PLYER_KI).handleId_;
	pMidoriImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::PLYER_MIDORI).handleId_;

	winPlyareImg_ = -1;
}

void ResultScene::Update(void)
{
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void ResultScene::Draw(void)
{
	DrawBox(0, 0, 100, 100, 0x00ff00, true);
	//É{Å[ÉhÇÃï`âÊ
	DrawRotaGraph((Application::SCREEN_SIZE_X / 2), Application::SCREEN_SIZE_Y / 2, 1.2f, 0.0f, backImg_, true);
	DrawRotaGraph((Application::SCREEN_SIZE_X / 2), Application::SCREEN_SIZE_Y / 3 - 75, 0.25f, 0.0f, winImg_, true);
	DrawRotaGraph((Application::SCREEN_SIZE_X / 2- 150), Application::SCREEN_SIZE_X / 2, 0.25f, 0.0f, scoreImg_, true);

	ruleDraw_();
}

void ResultScene::Release(void)
{

}

void ResultScene::MultiDraw(void)
{
	std::vector<int>playerPoints = DataBank::GetInstance().GetPlayerScores();
	int numberDigit = AsoUtility::GetDigitCount(playerPoints[0]);

	//ècç¿ïWÇå≈íË
	constexpr int ROUND_POS_X = Application::SCREEN_SIZE_X / 2 - 100;
	constexpr int NUMBER_POS_X = Application::SCREEN_SIZE_X / 2 +230;
	constexpr int NUMBER_OFFSET_X = 40;
	constexpr int POS_Y = Application::SCREEN_SIZE_X / 2;


	for (int i = 0; i < numberDigit; i++)
	{
		int index = AsoUtility::GetDigit(playerPoints[0], numberDigit - 1 - i);

		if (index == 0)
		{
			winPlyareImg_ = pAkaImg_;
		}
		if (index == 1)
		{
			winPlyareImg_ = pAoImg_;
		}
		if (index == 2)
		{
			winPlyareImg_ = pKiImg_;
		}
		if (index == 3)
		{
			winPlyareImg_ = pMidoriImg_;
		}


		DrawRotaGraph(
			NUMBER_POS_X + NUMBER_OFFSET_X * i,
			POS_Y,
			1.0f,
			0.0f,
			numbersImg_[index],
			true,
			false
		);

		DrawRotaGraph((Application::SCREEN_SIZE_X / 2), Application::SCREEN_SIZE_Y / 2, 0.2f, 0.0f, winPlyareImg_, true);
	}
}

void ResultScene::PanelDraw(void)
{
	std::vector<int>playerPoints = DataBank::GetInstance().GetPlayerScores();
	int numberDigit = AsoUtility::GetDigitCount(playerPoints[0]);

	//ècç¿ïWÇå≈íË
	constexpr int ROUND_POS_X = Application::SCREEN_SIZE_X / 2 - 100;
	constexpr int NUMBER_POS_X = Application::SCREEN_SIZE_X / 2 + 230;
	constexpr int NUMBER_OFFSET_X = 40;
	constexpr int POS_Y = Application::SCREEN_SIZE_X / 2;


	for (int i = 0; i < numberDigit; i++)
	{
		int index = AsoUtility::GetDigit(playerPoints[0], numberDigit - 1 - i);


		if (index == 0)
		{
			winPlyareImg_ = pAkaImg_;
		}
		if (index == 1)
		{
			winPlyareImg_ = pAoImg_;
		}
		if (index == 2)
		{
			winPlyareImg_ = pKiImg_;
		}
		if (index == 3)
		{
			winPlyareImg_ = pMidoriImg_;
		}

		DrawRotaGraph(
			NUMBER_POS_X + NUMBER_OFFSET_X * i,
			POS_Y,
			1.0f,
			0.0f,
			numbersImg_[index],
			true,
			false
		);

		DrawRotaGraph((Application::SCREEN_SIZE_X / 2), Application::SCREEN_SIZE_Y / 2, 0.2f, 0.0f, winPlyareImg_, true);
	}
}
