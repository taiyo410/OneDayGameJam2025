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
	void EndlessDraw(void);
	void PanelDraw(void);

	int backImg_;
	int* numbersImg_;

	//�e���[���̕`��
	std::function<void(void)>ruleDraw_;
};

