#pragma once
#include "SceneBase.h"
#include "../Common/Vector2.h"

class TitleScene :
    public SceneBase
{

public:

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
	int banBitIng_;
	//初期座標
	Vector2 banBitPos_;


};

