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
	joyPadNo_ = static_cast<InputManager::JOYPAD_NO>(static_cast<int>(InputManager::JOYPAD_NO::PAD1) + playerNo_); // デフォルトのジョイパッド番号を設定
}

Player::~Player(void)
{
	DeleteGraph(reticleHndle_);
}

void Player::Init(void)
{
	reticleHndle_ = LoadGraph((Application::PATH_IMAGE + "crosshair184.png").c_str());

	typeUpdate_ = std::bind(&Player::UpdateMouse, this);

	auto& ins = InputManager::GetInstance();
	Vector2 moPos = ins.GetMousePos();
	agoMousePos_ = moPos;
	reticlePos_ = moPos;
	reticlePos_.x += playerNo_ * 300.0f;

	isAttrck_ = false;
	isClick_ = false;
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

void Player::DrawUI(int i)
{
	Application::SCREEN_SIZE_Y / 2;

	int ii = 0;
	if (i >= 2)
	{
		ii = 1;
	}

	//DrawFormatString(100, 100 + i * 20, 0xffffff, "%d", isAttrck_);
	DrawFormatString((Application::SCREEN_SIZE_X / 2 - 300) + i * 150 + (150 * ii), Application::SCREEN_SIZE_Y - 30, 0xffffff, "%d", point_);
	//DrawFormatString(100, 500, 0xffffff, "%d,%d", reticlePos_.x, reticlePos_.y);
	//DrawFormatString(100, 500 + i * 20, 0xffffff, "%2.f,%2.f", reticlePos_.x, reticlePos_.y);
}

void Player::Release(void)
{
}

void Player::AddPoint(int point)
{
	if (point_ + point <= 0)
	{
		point_ = 0;
		return; //ポイントが0以下にならないようにする
	}
	point_ += point;

}

//マウスかコントローラーの更新
void Player::UpdateMouse(void)
{
	auto& ins = InputManager::GetInstance();
	Vector2 moPos = ins.GetMousePos();

	//InputManager::JOYPAD_NO jno = static_cast<InputManager::JOYPAD_NO>(DX_INPUT_PAD1);
	//InputManager::JOYPAD_NO jno = InputManager::JOYPAD_NO::PAD1;

	//移動前のレティクル位置を保存
	reticlePrePos_ = reticlePos_;

	// 左スティックの横軸取得
	const auto& leftStickX = ins.GetJPadInputState(joyPadNo_).AKeyLX;
	// 左スティックの縦軸取得
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
	//攻撃
	if (ins.IsClickMouseLeft() && !isClick_)
	{
		isAttrck_ = true;
	}
	else
	{
		isAttrck_ = false;
	}

	isClick_ = ins.IsClickMouseLeft();
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
	//移動前のレティクル位置を保存
	reticlePrePos_ = reticlePos_;
	MoveReticle();
	InputManager::JOYPAD_NO jno = static_cast<InputManager::JOYPAD_NO>(joyPadNo_);

	//攻撃
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
	//パッドの状態取得
	int padState = GetJoypadInputState(playerNo_);
	InputManager::JOYPAD_NO jno = static_cast<InputManager::JOYPAD_NO>(joyPadNo_);
	// 左スティックの横軸取得
	const auto& leftStickX = InputManager::GetInstance().GetJPadInputState(jno).AKeyLX;
	// 左スティックの縦軸取得
	const auto& leftStickY = InputManager::GetInstance().GetJPadInputState(jno).AKeyLY;
	VECTOR norm = AsoUtility::Normalize({ leftStickX,leftStickY });
	Vector2F moveDir = { 0,0 };
	if (IsMoveableReticle())
	{
		moveDir = { norm.x,norm.y };
		float movePow = 10.0f;
		if (InputManager::GetInstance().IsPadBtnNew(jno, InputManager::JOYPAD_BTN::R_BTN))
		{
			movePow = 15.0f; // 移動速度の調整
		}
		moveDir *= movePow;
	}
	else
	{
		moveDir *= -1.0f; // 移動不可なら移動方向を反転
	}
	
	reticlePos_.x += moveDir.x;
	reticlePos_.y += moveDir.y;

	//LimitReticle();
}

void Player::LimitReticle(void)
{
	if (reticlePos_.x < RETICLE_HALF_SIZE || reticlePos_.x > Application::SCREEN_SIZE_X - RETICLE_HALF_SIZE
		|| reticlePos_.y< RETICLE_HALF_SIZE || reticlePos_.y > Application::SCREEN_SIZE_Y - RETICLE_HALF_SIZE)
	{
		reticlePos_ = reticlePrePos_;
	}
}

bool Player::IsMoveableReticle(void) const
{
	// 左スティックの横軸取得
	const auto& leftStickX = InputManager::GetInstance().GetJPadInputState(joyPadNo_).AKeyLX;
	// 左スティックの縦軸取得
	const auto& leftStickY = InputManager::GetInstance().GetJPadInputState(joyPadNo_).AKeyLY;

	static const int DEAD_ZONE = 200; // デッドゾーンの閾値

	return (leftStickX <= -DEAD_ZONE || leftStickX >= DEAD_ZONE
		|| leftStickY <= -DEAD_ZONE || leftStickY >= DEAD_ZONE);
}
