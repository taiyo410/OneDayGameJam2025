#pragma once
class Vector2F;

class Vector2
{
public:

	int x;
	int y;

	// �f�t�H���g�R���X�g���N�^
	Vector2(void);

	// �R���X�g���N�^
	Vector2(int vX, int vY);

	// �R���X�g���N�^
	Vector2(Vector2F value);

	// Vector2F �֕ϊ�
	Vector2F ToVector2F(void);

};

