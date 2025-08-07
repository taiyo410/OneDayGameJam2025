#pragma once
#include<functional>
#include"../../Common/Vector2.h"
#include"../ObjectBase.h"

class TargetBase :public ObjectBase
{

public:

	enum class STATE
	{
		POP_UP,		//����,
		POP_DOWN,	//�|���
		ALIVE,		//�����AHIT����//�ʂ̎��͂���ŌŒ�H

		DEATH,		//�|��Ă���
	};

	// �R���X�g���N�^
	TargetBase(void);

	// �f�X�g���N�^
	virtual ~TargetBase(void);
	
	virtual void Load(void)override;

	virtual void Init(void)override;
	virtual void Update(void)override;
	virtual void Draw(void)override;
	void DebugDraw(void);

	virtual void Release(void);

	void SetPos(const VECTOR pos);

	bool InRange(const Vector2 mPos);
	const bool IsState(const STATE state)const { return state_ == state; }

	void ChangeState(STATE state);

	void CharChange();

protected:

	Vector2 size_;	

	STATE state_;


	Quaternion goalQua_;
	float limitTime_;
	float stepTime_;


};
