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

	void Hit(Vector2F mPos)override;

	void ChangeState(const STATE _state)override;
private:

	VECTOR jumpDir_;
	float jumpStep_;

	VECTOR jumpPow_;
	//����������
	bool isFall_;
	bool OutXline(void);
};

