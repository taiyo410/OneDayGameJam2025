#pragma once
#include "SceneBase.h"
#include "../Common/Vector2.h"

class TitleScene :
    public SceneBase
{

public:
	
	//���P�l�֘A
	static constexpr int PRINCESS_POS_X = 100;
	static constexpr int PRINCESS_POS_Y = 170;
	static constexpr float PRINCESS_ANGLE = 1.0f;
	static constexpr float PRINCESS_RATE = 0.5f;

	//�����֘A
	static constexpr float BANDIT_RATE = 0.5f;
	static constexpr float BANDIT_ANGLE = -0.8f;
	static constexpr int BANDIT_POS_X = 950;
	static constexpr int BANDIT_POS_Y = 170;


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
	int backGroundImg_;

	//���P�l�֘A
	int princessImg_;
	//�������W�ʒu
	Vector2 princessPos_;

	//�����֘A
	int banDitImg_;
	//�������W
	Vector2 banDitPos_;


};

