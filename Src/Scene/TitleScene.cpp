#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/ResourceManager.h"
#include "../Application.h"
#include "TitleScene.h"
#include <cmath>

TitleScene::TitleScene(void)
{
	//�w�i�摜�p�n���h��
	backGroundImg_ = -1;

	//���P�l�֘A
	princessImg_ = -1;

	//�����֘A
	banDitImg_ = -1;

	//�^�C�g�����p�n���h��
	titleNameImg_ = -1;
	
	//���摜�n���h��
	boxImg_ = -1;

	//�{�^���p�n���h��
	buttonImg_ = -1;

	//�{�^���̑傫����ύX����
	buttonScl_ = 0.f;
	buttonSclTime_ = 0.f;

	//���ԍX�V
	princessMoveTime_ = 0.f;
	banDitMoveTime_ = 0.f;

	//���P�l�̍��W��ݒ�
	princessPos_ = { PRINCESS_POS_X,PRINCESS_POS_Y };

	//�����̍��W��ݒ�
	banDitPos_ = { BANDIT_POS_X,BANDIT_POS_Y };

	//�^�C�g���l�[�����W
	titleNamePos_ = { TITLENAME_POS_X,DEFAULT_SCREEN_SIZE_Y / 2 };

	//�����W
	boxPos_ = { BOX_POS_X,BOX_POS_Y };

	//�{�^�����W
	buttonPos_ = { BUTTON_POS_X,BUTTON_POS_Y };
}

TitleScene::~TitleScene(void)
{
	
}

void TitleScene::Init(void)
{
	//���\�[�X�}�l�[�W���̃C���X�^���X 
	ResourceManager& res = ResourceManager::GetInstance();

	//���P�l�摜���[�h
	princessImg_ = res.Load(ResourceManager::SRC::PRINCESS).handleId_;

	//�����摜���[�h
	banDitImg_ = res.Load(ResourceManager::SRC::BANDIT).handleId_;
	
	//�w�i�摜���[�h
	backGroundImg_ = res.Load(ResourceManager::SRC::BACKGROUND_TITLE).handleId_;

	//�^�C�g���l�[�����[�h
	titleNameImg_ = res.Load(ResourceManager::SRC::TITLENAME).handleId_;

	//���̃��[�h
	boxImg_ = res.Load(ResourceManager::SRC::BOX).handleId_;

	//�{�^���摜���[�h
	buttonImg_ = res.Load(ResourceManager::SRC::PUSH_BUTTON).handleId_;

}

void TitleScene::Update(void)
{
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}

	

	//�{�^���̊g��k������// ��FTitleScene::Update()
	buttonScl_ = (std::sin(buttonSclTime_) * 0.5f + 0.5f) * (1.2f - 0.8f) + 0.8f;  // 0.8�`1.2 ������
	buttonScl_ *= 0.25f;
	buttonSclTime_ += 0.05f;

	//���Ԃ̍X�V
	princessMoveTime_ += 0.05f;
	banDitMoveTime_ += 0.045f;

	// ���P�l�̓����F���E�ɗh��{�����㉺�ɂ���
	princessPos_.x = PRINCESS_POS_X + static_cast<int>(std::sin(princessMoveTime_) * 10); // X�����
	princessPos_.y = PRINCESS_POS_Y + static_cast<int>(std::cos(princessMoveTime_ * 0.5f) * 3); // Y���ӂ�ӂ�

	// �����̓����F�������������炵�āA�t�����ɗh�炷
	banDitPos_.x = BANDIT_POS_X + static_cast<int>(std::sin(banDitMoveTime_ + 1.0f) * 12);  // X���h��i�t�ʑ��j
	banDitPos_.y = BANDIT_POS_Y + static_cast<int>(std::cos(banDitMoveTime_ * 0.6f) * 2);   // Y�������ӂ����

}

void TitleScene::Draw(void)
{
	//DrawBox(0, 0, 100, 100, 0xff0000, true);

	DrawGraph(0, 0, backGroundImg_, true);
	DrawRotaGraph(titleNamePos_.x, titleNamePos_.y, 0.5f, 0.0f, titleNameImg_, true);
	DrawRotaGraph(princessPos_.x, princessPos_.y, PRINCESS_RATE, PRINCESS_ANGLE, princessImg_, true);
	DrawRotaGraph(banDitPos_.x, banDitPos_.y, BANDIT_RATE, BANDIT_ANGLE, banDitImg_, true);

	for (int i = 1; i <= 5; i++)
	{
		DrawRotaGraph(boxPos_.x * i , boxPos_.y, BOX_RATE, BOX_ANGLE, boxImg_, true);
	}

	DrawRotaGraph(buttonPos_.x, buttonPos_.y, buttonScl_, BUTTON_ANGLE, buttonImg_, true);
	
}

void TitleScene::Release(void)
{
	DeleteGraph(princessImg_);
	DeleteGraph(backGroundImg_);
	DeleteGraph(banDitImg_);
	DeleteGraph(boxImg_);
}


