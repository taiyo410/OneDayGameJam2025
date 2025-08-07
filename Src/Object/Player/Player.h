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

	const Vector2 GetReticle(void)const { return reticlePos_; }
	const bool IsAttrck(void)const { return IsAttrck_; }

private:

	int reticleHndle_;
	Vector2 reticlePos_;
	Vector2 agoMousePos_;

	//������@�ʂ̍X�V
	std::function<void(void)> typeUpdate_;
	bool IsAttrck_;

	void UpdateMouse(void);
	void UpdateController(void);

};

