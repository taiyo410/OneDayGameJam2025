#include <DxLib.h>

#include "../../Manager/SceneManager.h"
#include "../../Manager/InputManager.h"

#include "../../Application.h"

#include "Player.h"

Player::Player(void)
{
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

	DrawRotaGraph(reticlePos_.x, reticlePos_.y, 1.0f, 0.0f, reticleHndle_, true);

	DrawFormatString(100, 100, 0xffffff, "%d", isAttrck_);
	DrawFormatString(100, 500, 0xffffff, "%d,%d", reticlePos_.x, reticlePos_.y);
}

void Player::Release(void)
{
}

//�}�E�X���R���g���[���[�̍X�V
void Player::UpdateMouse(void)
{

	auto& ins = InputManager::GetInstance();
	Vector2 moPos = ins.GetMousePos();

	InputManager::JOYPAD_NO jno = static_cast<InputManager::JOYPAD_NO>(DX_INPUT_PAD1);

	// ���X�e�B�b�N�̉����擾
	const auto& leftStickX = ins.GetJPadInputState(jno).AKeyLX;
	// ���X�e�B�b�N�̏c���擾
	const auto& leftStickY = ins.GetJPadInputState(jno).AKeyLY;

	if (leftStickX <= -500 || leftStickX >= 500
		|| leftStickY <= -500 || leftStickY >= 500)
	{
		SetMousePoint(reticlePos_.x, reticlePos_.y);
		typeUpdate_ = std::bind(&Player::UpdateController, this);
		return;
	}

	reticlePos_ = moPos;

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

	//�p�b�h�̏�Ԏ擾
	int padState = GetJoypadInputState(DX_INPUT_PAD1);
	InputManager::JOYPAD_NO jno = static_cast<InputManager::JOYPAD_NO>(DX_INPUT_PAD1);

	// ���X�e�B�b�N�̉����擾
	const auto& leftStickX = InputManager::GetInstance().GetJPadInputState(jno).AKeyLX;
	// ���X�e�B�b�N�̏c���擾
	const auto& leftStickY = InputManager::GetInstance().GetJPadInputState(jno).AKeyLY;

	Vector2 moveDir = { 0,0 };

	if (leftStickX <= -500)
	{
		moveDir.x += -1;
	}
	if (leftStickX >= 500)
	{
		moveDir.x += 1;
	}
	if (leftStickY <= -500)
	{
		moveDir.y += -1;
	}
	if (leftStickY >= 500)
	{
		moveDir.y += 1;
	}

	reticlePos_.x += moveDir.x;
	reticlePos_.y += moveDir.y;


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
