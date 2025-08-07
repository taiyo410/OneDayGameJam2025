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
	case SelectScene::SELECT_ID::MULTI:
		ruleDraw_ = [this]() {MultiDraw(); };
		break;
	case SelectScene::SELECT_ID::ENDLESS:
		ruleDraw_ = [this]() {EndlessDraw(); };
		break;
	case SelectScene::SELECT_ID::PANEL:
		ruleDraw_ = [this]() {PanelDraw(); };
		break;
	default:
		break;
	}

	backImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::BACKSELECT).handleId_;
	numbersImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::NUMBER_IMG).handleIds_;
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
	ruleDraw_();
}

void ResultScene::Release(void)
{

}

void ResultScene::MultiDraw(void)
{

}

void ResultScene::EndlessDraw(void)
{

}

void ResultScene::PanelDraw(void)
{
	std::vector<int>playerPoints = DataBank::GetInstance().GetPlayerScores();
	int numberDigit = AsoUtility::GetDigitCount(playerPoints[0]);

	//ècç¿ïWÇå≈íË
	constexpr int ROUND_POS_X = Application::SCREEN_SIZE_X / 2 - 100;
	constexpr int NUMBER_POS_X = Application::SCREEN_SIZE_X / 2 + 230;
	constexpr int NUMBER_OFFSET_X = 70;
	constexpr int POS_Y = Application::SCREEN_SIZE_X / 2;


	for (int i = 0; i < numberDigit; i++)
	{
		int index = AsoUtility::GetDigit(playerPoints[0], numberDigit - 1 - i);
		DrawRotaGraph(
			NUMBER_POS_X + NUMBER_OFFSET_X * i,
			POS_Y,
			1.0f,
			0.0f,
			numbersImg_[index],
			true,
			false
		);
	}
}
