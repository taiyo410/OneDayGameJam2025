#pragma once
#include "SceneBase.h"
class SelectScene :
    public SceneBase
{
public:

	//�Z���N�g�Ǘ�
	enum class SELECT_ID
	{
		NOME,
		MULTI,
		ENDLESS,
		PANEL
	};


	// �R���X�g���N�^
	SelectScene(void);

	// �f�X�g���N�^
	~SelectScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	//�Z���N�g�̎擾
	const SELECT_ID GetSelectId(void) { return selectId_; }

private:
	static constexpr int PLAYER_MAX = 4; //�v���C���[�ő�l��
	//�Z���N�g
	SELECT_ID selectId_;

	//�}���`�I�𒆂��ǂ���
	bool isMultiSelect_;

	//�v���C���[�l��
	int playerNum_;

	//�n���h��
	int backImg_;
	int multiImg_;
	int endlessImg_;
	int princessImg_;
	int panelImg_;
	int banDitImg_;
	int* numbersImg_;

	float multiImgScl_;
	float endlessImgScl_;
	float panelImgScl_;

	float sclTime_;
};
