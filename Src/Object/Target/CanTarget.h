#pragma once
#include "TargetBase.h"


class CanTarget :
    public TargetBase
{

public:

	// コンストラクタ
	CanTarget(void);

	// デストラクタ
	virtual ~CanTarget(void);

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;

private:

};

