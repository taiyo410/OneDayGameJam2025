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

	void Hit(Vector2F mPos)override;

	void ChangeState(const STATE _state)override;
private:

	VECTOR jumpDir_;
	float jumpStep_;

	VECTOR jumpPow_;
	//落ちた判定
	bool isFall_;
	bool OutXline(void);
};

