#include <DxLib.h>

#include "../../Manager/SceneManager.h"
#include "../../Manager/InputManager.h"
#include "../../Utility/AsoUtility.h"
#include "../../Application.h"

#include "Player.h"

Player::Player(const int _playerNo)
	: playerNo_(_playerNo)
{
	point_ = 0;
	joyPadNo_ = static_cast<InputManager::JOYPAD_NO>(static_cast<int>(InputManager::JOYPAD_NO::PAD1)+playerNo_); // �f�t�H���g�̃W���C�p�b�h�ԍ���ݒ�
}

Player::~Player(void)
{
	DeleteGraph(reticleHndle_);
}

void Player::Init(void)
{
	reticleHndle_ = LoadGraph((Application::PATH_IMAGE + "crosshair184.png").c_str());
	reticlePos_ = { 0,0 };

	typeUpdate_ = std::bind(&Player::UpdateMouse, this);

	auto& ins = InputManager::GetInstance();
	Vector2 moPos = ins.GetMousePos();
	agoMousePos_ = moPos;

	isAttrck_ = false;
}

void Player::Update(void)
{
	auto& ins = InputManager::GetInstance();
	Vector2 moPos = ins.GetMousePos();

	//����
	typeUpdate_();

	agoMousePos_ = moPos;
}

void Player::Draw(void)
{
	DrawRotaGraph(reticlePos_.x+playerNo_*300.0f, reticlePos_.y, 1.0f, 0.0f, reticleHndle_, true);

	DrawFormatString(100, 100, 0xffffff, "%d", point_);
	//DrawFormatString(100, 500, 0xffffff, "%d,%d", reticlePos_.x, reticlePos_.y);
	DrawFormatString(100, 500, 0xffffff, "%d,%d", reticlePos_.x, reticlePos_.y);
}

void Player::Release(void)
{
}

void Player::AddPoint(int point)
{
	if (point_+point<=0)
	{
		point_ = 0; 
		return; //�|�C���g��0�ȉ��ɂȂ�Ȃ��悤�ɂ���
	}
	point_ += point;

}

//�}�E�X���R���g���[���[�̍X�V
void Player::UpdateMouse(void)
{
	auto& ins = InputManager::GetInstance();
	Vector2 moPos = ins.GetMousePos();

	//InputManager::JOYPAD_NO jno = static_cast<InputManager::JOYPAD_NO>(DX_INPUT_PAD1);
	//InputManager::JOYPAD_NO jno = InputManager::JOYPAD_NO::PAD1;

	//�ړ��O�̃��e�B�N���ʒu��ۑ�
	reticlePrePos_ = reticlePos_;
	
	// ���X�e�B�b�N�̉����擾
	const auto& leftStickX = ins.GetJPadInputState(joyPadNo_).AKeyLX;
	// ���X�e�B�b�N�̏c���擾
	const auto& leftStickY = ins.GetJPadInputState(joyPadNo_).AKeyLY;

	if (leftStickX <= -500 || leftStickX >= 500
		|| leftStickY <= -500 || leftStickY >= 500)
	{
		SetMousePoint(reticlePos_.x, reticlePos_.y);
		typeUpdate_ = std::bind(&Player::UpdateController, this);
		return;
	}
	
	reticlePos_ = moPos;
	MoveReticle();
	//�U��
	if (ins.IsClickMouseLeft())
	{
		isAttrck_ = true;
	}
	else
	{
		isAttrck_ = false;
	}

}
void Player::UpdateController(void)
{
	auto& ins = InputManager::GetInstance();
	Vector2 moPos = ins.GetMousePos();

	if (agoMousePos_.x != moPos.x && agoMousePos_.y != moPos.y)
	{
		SetMousePoint(reticlePos_.x, reticlePos_.y);
		typeUpdate_ = std::bind(&Player::UpdateMouse, this);
		return;
	}
	//�ړ��O�̃��e�B�N���ʒu��ۑ�
	reticlePrePos_ = reticlePos_;
	MoveReticle();
	InputManager::JOYPAD_NO jno = static_cast<InputManager::JOYPAD_NO>(DX_INPUT_PAD1);

	//�U��
	if (ins.IsPadBtnTrgDown(jno, InputManager::JOYPAD_BTN::RIGHT))
	{
		isAttrck_ = true;
	}
	else
	{
		isAttrck_ = false;
	}
}

void Player::MoveReticle(void)
{
	//�p�b�h�̏�Ԏ擾
	int padState = GetJoypadInputState(DX_INPUT_PAD1);
	InputManager::JOYPAD_NO jno = static_cast<InputManager::JOYPAD_NO>(DX_INPUT_PAD1);
	// ���X�e�B�b�N�̉����擾
	const auto& leftStickX = InputManager::GetInstance().GetJPadInputState(jno).AKeyLX;
	// ���X�e�B�b�N�̏c���擾
	const auto& leftStickY = InputManager::GetInstance().GetJPadInputState(jno).AKeyLY;
	VECTOR norm = AsoUtility::Normalize({ leftStickX,leftStickY });
	Vector2F moveDir = { 0,0 };
	if (IsMoveableReticle())
	{
		moveDir = { norm.x,norm.y };
		float movePow = 10.0f;
		if (InputManager::GetInstance().IsPadBtnNew(jno, InputManager::JOYPAD_BTN::R_BTN))
		{
			movePow = 15.0f; // �ړ����x�̒���
		}
		moveDir *= movePow;
	}
	else
	{
		moveDir *= -1.0f; // �ړ��s�Ȃ�ړ������𔽓]
	}
	
	reticlePos_.x += moveDir.x;
	reticlePos_.y += moveDir.y;

	LimitReticle();
}

void Player::LimitReticle(void)
{
	if (reticlePos_.x < RETICLE_HALF_SIZE|| reticlePos_.x > Application::SCREEN_SIZE_X-RETICLE_HALF_SIZE
		||reticlePos_.y< RETICLE_HALF_SIZE|| reticlePos_.y > Application::SCREEN_SIZE_Y - RETICLE_HALF_SIZE)
	{
		reticlePos_=reticlePrePos_;
	}
}

bool Player::IsMoveableReticle(void) const
{
	// ���X�e�B�b�N�̉����擾
	const auto& leftStickX = InputManager::GetInstance().GetJPadInputState(joyPadNo_).AKeyLX;
	// ���X�e�B�b�N�̏c���擾
	const auto& leftStickY = InputManager::GetInstance().GetJPadInputState(joyPadNo_).AKeyLY;

	static const int DEAD_ZONE = 200; // �f�b�h�]�[����臒l

	return (leftStickX <= -DEAD_ZONE || leftStickX >= DEAD_ZONE
		|| leftStickY <= -DEAD_ZONE || leftStickY >= DEAD_ZONE);
}
