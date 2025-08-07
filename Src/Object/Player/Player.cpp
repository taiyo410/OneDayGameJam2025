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

	typeUpdate_= std::bind(&Player::UpdateMouse, this);

	auto& ins = InputManager::GetInstance();
	Vector2 moPos = ins.GetMousePos();
	agoMousePos_ = moPos;
}

void Player::Update(void)
{
	auto& ins = InputManager::GetInstance();
	Vector2 moPos = ins.GetMousePos();

	//操作
	typeUpdate_();


	agoMousePos_ = moPos;
}

void Player::Draw(void)
{

	DrawRotaGraph(reticlePos_.x, reticlePos_.y, 1.0f, 0.0f, reticleHndle_, true);
}

void Player::Release(void)
{
}

//マウスかコントローラーの更新
void Player::UpdateMouse(void)
{

	auto& ins = InputManager::GetInstance();
	Vector2 moPos = ins.GetMousePos();

	InputManager::JOYPAD_NO jno = static_cast<InputManager::JOYPAD_NO>(DX_INPUT_PAD1);

	// 左スティックの横軸取得
	const auto& leftStickX = InputManager::GetInstance().GetJPadInputState(jno).AKeyLX;
	// 左スティックの縦軸取得
	const auto& leftStickY = InputManager::GetInstance().GetJPadInputState(jno).AKeyLY;

	if (leftStickX <= -500 || leftStickX >= 500 
		|| leftStickY <= -500 || leftStickY >= 500 )
	{
		SetMousePoint(reticlePos_.x, reticlePos_.y);
		typeUpdate_ = std::bind(&Player::UpdateController, this);
		return;
	}

	reticlePos_ = moPos;

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

	//パッドの状態取得
	int padState = GetJoypadInputState(DX_INPUT_PAD1);
	InputManager::JOYPAD_NO jno = static_cast<InputManager::JOYPAD_NO>(DX_INPUT_PAD1);

	// 左スティックの横軸取得
	const auto& leftStickX = InputManager::GetInstance().GetJPadInputState(jno).AKeyLX;
	// 左スティックの縦軸取得
	const auto& leftStickY = InputManager::GetInstance().GetJPadInputState(jno).AKeyLY;

	Vector2 moveDir = { 0,0 };

	if (leftStickX <= -500 )
	{
		moveDir.x += -1;
	}
	if (leftStickX >= 500 )
	{
		moveDir.x += 1;
	}
	if (leftStickY <= -500 )
	{
		moveDir.y += -1;
	}
	if (leftStickY >= 500 )
	{
		moveDir.y += 1;
	}

	reticlePos_.x += moveDir.x;
	reticlePos_.y += moveDir.y;

}
