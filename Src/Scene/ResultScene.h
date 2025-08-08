#pragma once
#include "SceneBase.h"
#include<functional>
class ResultScene :
    public SceneBase
{

public:

	// コンストラクタ
	ResultScene(void);

	// デストラクタ
	~ResultScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	void MultiDraw(void);
	void PanelDraw(void);

	int backImg_;
	int* numbersImg_;

	int winImg_;
	int scoreImg_;

	int pAkaImg_;
	int pAoImg_;
	int pKiImg_;
	int pMidoriImg_;

	int winPlyareImg_;

	//各ルールの描画
	std::function<void(void)>ruleDraw_;
};

