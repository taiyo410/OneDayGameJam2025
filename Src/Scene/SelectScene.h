#pragma once
#include "SceneBase.h"
class SelectScene :
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
	SelectScene(void);

	// デストラクタ
	~SelectScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	//セレクトの取得
	const SELECT_ID GetSelectId(void) { return selectId_; }

private:
	static constexpr int PLAYER_MAX = 4; //プレイヤー最大人数
	//セレクト
	SELECT_ID selectId_;

	//マルチ選択中かどうか
	bool isMultiSelect_;

	//プレイヤー人数
	int playerNum_;

	//ハンドル
	int backImg_;
	int multiImg_;
	int endlessImg_;
	int princessImg_;
	int panelImg_;
	int banDitImg_;
	int* numbersImg_;

	float multiImgScl_;
	float endlessImgScl_;
	float panelImgScl_;

	float sclTime_;
};
