#pragma once
#include "TargetBase.h"

class PanelTarget :public TargetBase
{
public:

	// コンストラクタ
	PanelTarget(void);

	// デストラクタ
	virtual ~PanelTarget(void);

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;


private:


};

