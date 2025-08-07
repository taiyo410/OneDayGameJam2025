#pragma once
#include "SceneBase.h"

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
	int backGroundImg_ = -1;

	//お姫様関連
	//int prins

};

