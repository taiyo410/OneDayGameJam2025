#pragma once
#include "TargetBase.h"

class PanelTarget :public TargetBase
{
public:

	// �R���X�g���N�^
	PanelTarget(void);

	// �f�X�g���N�^
	virtual ~PanelTarget(void);

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;


private:


};

