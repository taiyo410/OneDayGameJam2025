#pragma once
#include "SceneBase.h"
#include "../Common/Vector2.h"

class TitleScene :
    public SceneBase
{

public:
	
	//お姫様関連
	static constexpr int PRINCESS_POS_X = 100;
	static constexpr int PRINCESS_POS_Y = 170;
	static constexpr float PRINCESS_ANGLE = 1.0f;
	static constexpr float PRINCESS_RATE = 0.5f;

	//盗賊関連
	static constexpr float BANDIT_RATE = 0.5f;
	static constexpr float BANDIT_ANGLE = -1.0f;
	static constexpr int BANDIT_POS_X = 900;
	static constexpr int BANDIT_POS_Y = 170;

	//タイトル画像
	static constexpr int TITLENAME_POS_X = 515;

	//箱関連
	static constexpr int BOX_POS_X = 170;
	static constexpr int BOX_POS_Y = 500;
	static constexpr float BOX_RATE = 0.5f;
	static constexpr float BOX_ANGLE = 0.f;

	//ボタン
	static constexpr int BUTTON_POS_X = 515;
	static constexpr int BUTTON_POS_Y = 515;
	static constexpr float BUTTON_RATE = 0.3f;
	static constexpr float BUTTON_ANGLE = 0.f;

	// コンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	

private:

	//背景画像用ハンドル
	int backGroundImg_;

	//お姫様関連
	int princessImg_;
	//初期座標位置
	Vector2 princessPos_;

	//盗賊関連
	int banDitImg_;
	//初期座標
	Vector2 banDitPos_;

	//タイトル名用ハンドル
	int titleNameImg_;
	//タイトル表示位置
	Vector2 titleNamePos_;

	//箱画像ハンドル
	int boxImg_;

	//箱表示位置
	Vector2 boxPos_;
	
	//ボタン用ハンドル
	int buttonImg_;
	Vector2 buttonPos_;

	//ボタンの大きさを変更する
	float buttonScl_;
	float buttonSclTime_;

	//時間更新
	float princessMoveTime_;
	float banDitMoveTime_;

};

