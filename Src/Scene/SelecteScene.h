#pragma once
#include "SceneBase.h"
class SelecteScene :
    public SceneBase
{
public:

	//セレクト管理
	enum class SELECT_ID
	{
		NOME,
		MULTI,
		ENDLESS,
		PANEL
	};


	// コンストラクタ
	SelecteScene(void);

	// デストラクタ
	~SelecteScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	//セレクトの取得
	const SELECT_ID GetSelectId(void) { return selectId_; }

private:

	//セレクト
	SELECT_ID selectId_;

	//ハンドル
	int backImg_;
	int multiImg_;
	int endlessImg_;
	int princessImg_;
	int panelImg_;
	int banDitImg_;

	float multiImgScl_;
	float endlessImgScl_;
	float panelImgScl_;

	float sclTime_;
};
