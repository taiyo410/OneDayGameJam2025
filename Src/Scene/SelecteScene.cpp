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
	backimg_ = LoadGraph((Application::PATH_IMAGE + "BackGround.png").c_str());
	img_ = LoadGraph((Application::PATH_IMAGE + "select.png").c_str());
}

void SelecteScene::Update(void)
{
}

void SelecteScene::Draw(void)
{
	Vector2 boxPos1 = { Application::SCREEN_SIZE_X / 2 - 50, Application::SCREEN_SIZE_Y / 2 - 20 };
	Vector2 boxPos2 = { Application::SCREEN_SIZE_X / 2 + 50, Application::SCREEN_SIZE_Y / 2 + 20 };
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1.0f, 0.0f, backimg_, true);
	DrawBox(
		boxPos1.x,
		boxPos1.y,
		boxPos2.x,
		boxPos2.y,
		GetColor(255, 255, 255),
		true);
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 0.1f, 0.0f, img_, true);
}

void SelecteScene::Release(void)
{
	DeleteGraph(img_);
}
