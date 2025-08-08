#pragma once
#include <memory>
#include "TargetBase.h"

class Player;

class CanTarget :
    public TargetBase
{

public:

	// コンストラクタ
	CanTarget(std::unique_ptr<Player>& player);

	// デストラクタ
	virtual ~CanTarget(void);

	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;

	void SetHost(int id);

	void Hit(Vector2F mPos)override;

	void ChangeState(const STATE _state)override;

	const int GetId(void)const { return playerId_; }


private:

	VECTOR jumpDir_;
	float jumpStep_;

	std::unique_ptr<Player>& player_;

	VECTOR jumpPow_;
	//落ちた判定
	bool isFall_;
	bool OutXline(void);
};

