#pragma once
#include<functional>

class Player
{

public:

	// �R���X�g���N�^
	Player(void);

	// �f�X�g���N�^
	~Player(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	const Vector2F GetReticle(void)const { return reticlePos_; }
	const bool IsAttrck(void)const { return isAttrck_; }

	void AddPoint(int point) { point_ += point; }

private:

	int reticleHndle_;
	Vector2F reticlePos_;
	Vector2 agoMousePos_;

	//�|�C���g
	int point_;

	//������@�ʂ̍X�V
	std::function<void(void)> typeUpdate_;
	bool isAttrck_;

	void UpdateMouse(void);
	void UpdateController(void);

	//���e�B�N���̈ړ�
	void MoveReticle(void);

};

