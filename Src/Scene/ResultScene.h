#pragma once
#include "SceneBase.h"
#include<functional>
class ResultScene :
    public SceneBase
{

public:

	// �R���X�g���N�^
	ResultScene(void);

	// �f�X�g���N�^
	~ResultScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	void MultiDraw(void);
	void PanelDraw(void);

	int backImg_;
	int* numbersImg_;

	int winImg_;
	int scoreImg_;

	int pAkaImg_;
	int pAoImg_;
	int pKiImg_;
	int pMidoriImg_;

	int winPlyareImg_;

	//�e���[���̕`��
	std::function<void(void)>ruleDraw_;
};

