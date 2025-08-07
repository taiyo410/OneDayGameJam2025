#pragma once
#include<functional>
#include"../ObjectBase.h"
class TargetBase :public ObjectBase
{

public:

	// �R���X�g���N�^
	TargetBase(void);

	// �f�X�g���N�^
	virtual ~TargetBase(void);

	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Release(void);

protected:
	enum class STATE
	{
		ALIVE
		,DEATH
	};

	STATE state_;
private:

};
