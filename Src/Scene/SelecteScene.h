#pragma once
#include "SceneBase.h"
class SelecteScene :
    public SceneBase
{
public:

	//�Z���N�g�Ǘ�
	enum class SELECT_ID
	{
		NOME,
		MULTI,
		ENDLESS
	};


	// �R���X�g���N�^
	SelecteScene(void);

	// �f�X�g���N�^
	~SelecteScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	//�n���h��
	int backImg_;
	int MultiImg_;
	int endlessImg_;
};
