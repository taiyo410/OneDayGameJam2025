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
	void EndlessDraw(void);
	void PanelDraw(void);

	int backImg_;
	int* numbersImg_;

	//各ルールの描画
	std::function<void(void)>ruleDraw_;
};

