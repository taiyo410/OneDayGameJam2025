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
		ENDLESS
	};


	// コンストラクタ
	SelecteScene(void);

	// デストラクタ
	~SelecteScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	//ハンドル
	int backImg_;
	int MultiImg_;
	int endlessImg_;
};
