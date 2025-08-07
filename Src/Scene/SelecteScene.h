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
		ENDLESS,
		PANEL
	};


	// �R���X�g���N�^
	SelecteScene(void);

	// �f�X�g���N�^
	~SelecteScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	//�Z���N�g�̎擾
	const SELECT_ID GetSelectId(void) { return selectId_; }

private:

	//�Z���N�g
	SELECT_ID selectId_;

	//�n���h��
	int backImg_;
	int multiImg_;
	int endlessImg_;
	int princessImg_;
	int panelImg_;
	int banDitImg_;

	float multiImgScl_;
	float endlessImgScl_;
	float panelImgScl_;

	float sclTime_;
};
