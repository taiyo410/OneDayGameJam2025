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

	// �R���X�g���N�^
	Panel(void);

	// �f�X�g���N�^
	~Panel(void)override;

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

private:
	//�o���J�E���g
	float appearCnt_;

	std::vector<TYPE>pannels_;
};

