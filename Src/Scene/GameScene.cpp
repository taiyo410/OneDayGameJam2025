#include <DxLib.h>

#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/ResourceManager.h"

#include "../Manager/Camera.h"
#include "../Manager/DataBank.h"

#include "../Object/Common/EffectController.h"

#include "../Object/Player/Player.h"

#include "../Object/Target/TargetBase.h"
#include "../Object/Target/PanelTarget.h"
#include "../Object/Target/CanTarget.h"

#include"../Scene/SelectScene.h"
#include "../Application.h"

#include "GameScene.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
	DeleteGraph(backGroundImg_);
	MV1DeleteModel(fenceModel_);
}

void GameScene::Init(void)
{
	SceneManager::GetInstance().GetCamera().lock()->ChangeMode(Camera::MODE::FIXED_POINT);

	//リソースマネージャのインスタンス 
	ResourceManager& res = ResourceManager::GetInstance();
	backGroundImg_ = res.Load(ResourceManager::SRC::BACKGROUND_TITLE).handleId_;
	fenceModel_ = MV1LoadModel((Application::PATH_MODEL + "fence.mv1").c_str());


	SelectScene::SELECT_ID selectId = DataBank::GetInstance().GetSelectId();
	float posX = -500.0f;
	switch (selectId)
	{
	case SelectScene::SELECT_ID::NOME:
		break;
	case SelectScene::SELECT_ID::MULTI:
	{
		//プレイヤー人数の取得
		int pNum = DataBank::GetInstance().GetPlayerNum();
		for (int i = 0; i < pNum; i++)
		{
			auto player = std::make_unique<Player>(i);
			player->Init();
			players_.push_back(std::move(player));
		}
		for (int i = 0; i < pNum; i++)
		{
			auto target = std::make_unique<CanTarget>();
			target->Init();
			target->SetPos({ posX + i * 250.0f, 0.0f,150.0f });
			targets_.push_back(std::move(target));
		}
		modeUpdate_ = std::bind(&GameScene::CanRule, this);
	}
		break;
	case SelectScene::SELECT_ID::ENDLESS:
		for (int i = 0; i < 1; i++)
		{
			auto player = std::make_unique<Player>(i);
			player->Init();
			players_.push_back(std::move(player));
		}
		
		for (int i = 0; i < 1; i++)
		{
			auto target = std::make_unique<CanTarget>();
			target->Init();
			target->SetPos({ posX + i * 250.0f, 0.0f,150.0f });
			targets_.push_back(std::move(target));
		}
		modeUpdate_ = std::bind(&GameScene::CanRule, this);
		break;
	case SelectScene::SELECT_ID::PANEL:
		for (int i = 0; i < 1; i++)
		{
			auto player = std::make_unique<Player>(i);
			player->Init();
			players_.push_back(std::move(player));
		}
		for (int i = 0; i < 5; i++)
		{
			auto target = std::make_unique<PanelTarget>();
			target->Init();
			target->SetPos({ posX + i * 250.0f, 0.0f,150.0f });
			targets_.push_back(std::move(target));
		}
		modeUpdate_ = std::bind(&GameScene::PannelRule, this);
		break;
	default:
		break;
	}
	effec_ = std::make_unique<EffectController>();
	effec_->Add(0, (Application::PATH_EFFECT + "Hit.efkefc"));

	
#ifdef _DEBUG




#endif // _DEBUG
	
#ifdef NDEBUG 
	// 処理
	float posX = -500.0f;
	for (int i = 0; i < 5; i++)
	{
		auto target = std::make_unique<PanelTarget>();
		target->Init();
		target->SetPos({ posX + i * 250.0f, 0.0f,150.0f });
		targets_.push_back(std::move(target));
	}

	
#endif // NDEBUG

	// マウスを非表示状態にする
	SetMouseDispFlag(false);
	//modeUpdate_ = std::bind(&GameScene::PannelRule, this);
	//modeUpdate_ = std::bind(&GameScene::PannelRule, this);
}

void GameScene::Update(void)
{
	effec_->Update(0);

	for (auto& player : players_)
	{
		player->Update();
	}

	modeUpdate_();


#ifdef _DEBUG

	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
	{
		// マウスを表示状態にする
		SetMouseDispFlag(true);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::RESULT);
	}

#endif // DEBUG

	
}

void GameScene::Draw(void)
{
	DrawGraph(0, 0, backGroundImg_, true);

	DrawBox(0, 0, 100, 100, 0x0000ff, true);

	for (auto& target : targets_)
	{
		target->Draw();
	}


#ifdef _DEBUG

	MV1DrawModel(fenceModel_);

#endif // NDEBUG

	for (auto& player : players_)
	{
		player->Draw();
	}

	DrawLine(Application::SCREEN_SIZE_X / 2, 0, Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y, 0x00ff00);

	DrawSphere3D({ 0,0,0 }, 10, 10, 0xff0000, 0xff0000, false);

}

void GameScene::Release(void)
{
}

//パネルゲームモード
void GameScene::PannelRule()
{
	auto& ins = InputManager::GetInstance();
	Vector2 moPos = ins.GetMousePos();

	bool isWipeOut = true;
	for (auto& target : targets_)
	{
		target->Update();

		//ターゲットが全滅しているか
		if (target->IsState(TargetBase::STATE::ALIVE) || target->IsState(TargetBase::STATE::POP_UP)
			|| target->IsState(TargetBase::STATE::POP_DOWN))
		{
			isWipeOut = false;
		}

		for (auto& player : players_)
		{
			if (player->IsAttrck() && target->InRange(player->GetReticle())
				&& (target->IsState(TargetBase::STATE::ALIVE) || target->IsState(TargetBase::STATE::POP_UP)))
			{
				//衝突
				target->ChangeState(TargetBase::STATE::POP_DOWN);
				effec_->Play(0, target->GetCenter(), { 0.0f,0.0f,0.0f }, 10.0f);

				//ポイント計算
				if (target->IsScore())//ポイント加算
				{
					player->AddPoint(1);
				}
				else if (!target->IsScore())//ポイント減算
				{
					player->AddPoint(-2);
				}

			}
		}
	}

	//全滅していたなら
	if (isWipeOut)
	{
		for (auto& target : targets_)
		{
			target->CharChange();
			target->ChangeState(TargetBase::STATE::POP_UP);
		}
	}

}
//缶ゲームモード
void GameScene::CanRule()
{
	auto& ins = InputManager::GetInstance();
	Vector2 moPos = ins.GetMousePos();

	bool isWipeOut = true;
	for (auto& target : targets_)
	{
		target->Update();

		//ターゲットが全滅しているか
		if (target->IsState(TargetBase::STATE::ALIVE))
		{
			isWipeOut = false;
		}

		for (auto& player : players_)
		{
			if (player->IsAttrck() && target->InRange(player->GetReticle())
				&& (target->IsState(TargetBase::STATE::ALIVE)))
			{
				//衝突
				target->Hit(player->GetReticle());
				effec_->Play(0, target->GetCenter(), { 0.0f,0.0f,0.0f }, 10.0f);

				//ポイント計算
				if (target->IsScore())//ポイント加算
				{
					player->AddPoint(ADD_POINT);
				}

			}
		}
	}


}
