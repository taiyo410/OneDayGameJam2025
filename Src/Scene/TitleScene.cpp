#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/ResourceManager.h"
#include "../Application.h"
#include "TitleScene.h"
#include <cmath>

TitleScene::TitleScene(void)
{
	//背景画像用ハンドル
	backGroundImg_ = -1;

	//お姫様関連
	princessImg_ = -1;

	//盗賊関連
	banDitImg_ = -1;

	//タイトル名用ハンドル
	titleNameImg_ = -1;
	
	//箱画像ハンドル
	boxImg_ = -1;

	//ボタン用ハンドル
	buttonImg_ = -1;

	//ボタンの大きさを変更する
	buttonScl_ = 0.f;
	buttonSclTime_ = 0.f;

	//時間更新
	princessMoveTime_ = 0.f;
	banDitMoveTime_ = 0.f;

	//お姫様の座標を設定
	princessPos_ = { PRINCESS_POS_X,PRINCESS_POS_Y };

	//盗賊の座標を設定
	banDitPos_ = { BANDIT_POS_X,BANDIT_POS_Y };

	//タイトルネーム座標
	titleNamePos_ = { TITLENAME_POS_X,DEFAULT_SCREEN_SIZE_Y / 2 };

	//箱座標
	boxPos_ = { BOX_POS_X,BOX_POS_Y };

	//ボタン座標
	buttonPos_ = { BUTTON_POS_X,BUTTON_POS_Y };
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

	//タイトルネームロード
	titleNameImg_ = res.Load(ResourceManager::SRC::TITLENAME).handleId_;

	//箱のロード
	boxImg_ = res.Load(ResourceManager::SRC::BOX).handleId_;

	//ボタン画像ロード
	buttonImg_ = res.Load(ResourceManager::SRC::PUSH_BUTTON).handleId_;

}

void TitleScene::Update(void)
{
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}

	

	//ボタンの拡大縮小処理// 例：TitleScene::Update()
	buttonScl_ = (std::sin(buttonSclTime_) * 0.5f + 0.5f) * (1.2f - 0.8f) + 0.8f;  // 0.8～1.2 を往復
	buttonScl_ *= 0.25f;
	buttonSclTime_ += 0.05f;

	//時間の更新
	princessMoveTime_ += 0.05f;
	banDitMoveTime_ += 0.045f;

	// お姫様の動き：左右に揺れ＋少し上下にゆれる
	princessPos_.x = PRINCESS_POS_X + static_cast<int>(std::sin(princessMoveTime_) * 10); // X軸ゆれ
	princessPos_.y = PRINCESS_POS_Y + static_cast<int>(std::cos(princessMoveTime_ * 0.5f) * 3); // Y軸ふわふわ

	// 盗賊の動き：少し周期をずらして、逆向きに揺らす
	banDitPos_.x = BANDIT_POS_X + static_cast<int>(std::sin(banDitMoveTime_ + 1.0f) * 12);  // X軸揺れ（逆位相）
	banDitPos_.y = BANDIT_POS_Y + static_cast<int>(std::cos(banDitMoveTime_ * 0.6f) * 2);   // Y軸少しふわっと

}

void TitleScene::Draw(void)
{
	//DrawBox(0, 0, 100, 100, 0xff0000, true);

	DrawGraph(0, 0, backGroundImg_, true);
	DrawRotaGraph(titleNamePos_.x, titleNamePos_.y, 0.5f, 0.0f, titleNameImg_, true);
	DrawRotaGraph(princessPos_.x, princessPos_.y, PRINCESS_RATE, PRINCESS_ANGLE, princessImg_, true);
	DrawRotaGraph(banDitPos_.x, banDitPos_.y, BANDIT_RATE, BANDIT_ANGLE, banDitImg_, true);

	for (int i = 1; i <= 5; i++)
	{
		DrawRotaGraph(boxPos_.x * i , boxPos_.y, BOX_RATE, BOX_ANGLE, boxImg_, true);
	}

	DrawRotaGraph(buttonPos_.x, buttonPos_.y, buttonScl_, BUTTON_ANGLE, buttonImg_, true);
	
}

void TitleScene::Release(void)
{
	DeleteGraph(princessImg_);
	DeleteGraph(backGroundImg_);
	DeleteGraph(banDitImg_);
	DeleteGraph(boxImg_);
}


