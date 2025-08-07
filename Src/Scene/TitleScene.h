#pragma once
#include "SceneBase.h"
#include "../Common/Vector2.h"

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

	//�摜�̒��S���W���擾����֐�
	void GetCenterPos(int CenterPosX, int CenterPosY);

private:

	//�w�i�摜�p�n���h��
	int backGroundImg_;

	//���P�l�֘A
	int princessImg_;
	//�������W�ʒu
	Vector2 princessPos_;

	//�����֘A
	int banBitIng_;
	//�������W
	Vector2 banBitPos_;


};

