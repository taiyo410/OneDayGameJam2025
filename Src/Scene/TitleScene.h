#pragma once
#include "SceneBase.h"

class TitleScene :
    public SceneBase
{

public:

	// �R���X�g���N�^
	TitleScene(void);

	// �f�X�g���N�^
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	//�w�i�摜�p�n���h��
	int backGroundImg_ = -1;

	//���P�l�֘A
	//int prins

};

