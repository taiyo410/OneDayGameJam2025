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
	};

	// コンストラクタ
	Panel(void);

	// デストラクタ
	~Panel(void)override;

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

private:
	//出現カウント
	float appearCnt_;

	std::vector<TYPE>pannels_;
};

