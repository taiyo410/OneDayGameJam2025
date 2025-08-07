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
	static constexpr float BANDIT_ANGLE = -1.0f;
	static constexpr int BANDIT_POS_X = 900;
	static constexpr int BANDIT_POS_Y = 170;

	//�^�C�g���摜
	static constexpr int TITLENAME_POS_X = 515;

	//���֘A
	static constexpr int BOX_POS_X = 170;
	static constexpr int BOX_POS_Y = 500;
	static constexpr float BOX_RATE = 0.5f;
	static constexpr float BOX_ANGLE = 0.f;

	//�{�^��
	static constexpr int BUTTON_POS_X = 515;
	static constexpr int BUTTON_POS_Y = 515;
	static constexpr float BUTTON_RATE = 0.3f;
	static constexpr float BUTTON_ANGLE = 0.f;

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

	//�^�C�g�����p�n���h��
	int titleNameImg_;
	//�^�C�g���\���ʒu
	Vector2 titleNamePos_;

	//���摜�n���h��
	int boxImg_;

	//���\���ʒu
	Vector2 boxPos_;
	
	//�{�^���p�n���h��
	int buttonImg_;
	Vector2 buttonPos_;

	//�{�^���̑傫����ύX����
	float buttonScl_;
	float buttonSclTime_;

	//���ԍX�V
	float princessMoveTime_;
	float banDitMoveTime_;

};

