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

	// �R���X�g���N�^
	Panel(void);

	// �f�X�g���N�^
	~Panel(void)override;

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	//�o���f�B�b�h���P�������߂�
	void DesideTarget(void);

private:
	//�o���J�E���g
	float appearCnt_;
	
	std::vector<TYPE>pannels_;

	//�����o�֐�
	//�������Ă��鎞
	void AliveUpdate(void);



};

