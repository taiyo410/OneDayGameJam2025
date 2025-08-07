#pragma once
#include "TargetBase.h"
#include<vector>

class Panel :
    public TargetBase
{
public:
	enum class TYPE
	{
		BANDIT
		,PRINCESS
		,MAX
	};

	// コンストラクタ
	Panel(void);

	// デストラクタ
	~Panel(void)override;

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	//バンディッドか姫かを決める
	void DesideTarget(void);

private:
	//出現カウント
	float appearCnt_;
	
	std::vector<TYPE>pannels_;

	//メンバ関数
	//生存している時
	void AliveUpdate(void);



};

