#pragma once
// �|�C���^�n���̑O�ɁAVector2��Vector2F�̏z�Q�Ƃ������邱��
class Vector2;

class Vector2F
{
public:

	float x;
	float y;

	// �f�t�H���g�R���X�g���N�^
	Vector2F(void);

	// �R���X�g���N�^
	Vector2F(float vX, float vY);

	// �R���X�g���N�^
	Vector2F(Vector2 value);

	// Vector2 �֕ϊ�
	Vector2 ToVector2(void);

};

