#pragma once
#include<functional>
#include"../../Common/Vector2.h"
#include"../ObjectBase.h"

class TargetBase :public ObjectBase
{

public:

	// コンストラクタ
	TargetBase(void);

	// デストラクタ
	virtual ~TargetBase(void);
	
	virtual void Load(void)override;

	virtual void Init(void)override;
	virtual void Update(void)override;
	virtual void Draw(void)override;

	void SetPos(VECTOR pos);

	virtual void Release(void);

	bool InRange(Vector2 mPos);

protected:
	enum class STATE
	{
		ALIVE
		,DEATH
	};

	STATE state_;
private:

	float mRot_;
	float goalRot_;


};
