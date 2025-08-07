#pragma once
#include<functional>
#include"../../Common/Vector2F.h"
#include"../../Common/Vector2.h"
#include"../ObjectBase.h"

class TargetBase :public ObjectBase
{

public:

	enum class STATE
	{
		POP_UP,		//発生,
		POP_DOWN,	//倒れる
		ALIVE,		//生存、HITする//缶の時はこれで固定？

		DEATH,		//倒れている
	};

	// コンストラクタ
	TargetBase(void);

	// デストラクタ
	virtual ~TargetBase(void);
	
	virtual void Load(void)override;

	virtual void Init(void)override;
	virtual void Update(void)override;
	virtual void Draw(void)override;
	void DebugDraw(void);

	virtual void Release(void);

	void SetPos(const VECTOR pos);

	
	bool InRange(Vector2F mPos);
	const bool IsState(STATE state)const { return state_ == state; }

	const bool IsScore(void)const { return isScorePlus_; }

	virtual void ChangeState(const STATE state);
	
	//弾が当たった時の処理
	virtual void Hit(Vector2F mPos);

	void CharChange();

	const VECTOR GetCenter(void);

protected:

	Vector2 size_;	

	STATE state_;

	bool isScorePlus_;

	Quaternion goalQua_;
	float limitTime_;
	float stepTime_;

	
};
