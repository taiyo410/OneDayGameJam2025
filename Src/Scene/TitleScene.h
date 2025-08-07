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
	static constexpr float BANDIT_ANGLE = -0.8f;
	static constexpr int BANDIT_POS_X = 950;
	static constexpr int BANDIT_POS_Y = 170;


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


};

