#pragma once
#include "TargetBase.h"


class CanTarget :
    public TargetBase
{

public:

	// �R���X�g���N�^
	CanTarget(void);

	// �f�X�g���N�^
	virtual ~CanTarget(void);

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;

private:

};

