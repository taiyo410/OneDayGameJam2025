#pragma once
#include <memory>
#include "TargetBase.h"

class Player;

class CanTarget :
    public TargetBase
{

public:

	// �R���X�g���N�^
	CanTarget(std::unique_ptr<Player>& player);

	// �f�X�g���N�^
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
	//����������
	bool isFall_;
	bool OutXline(void);
};

