#pragma once
#include<functional>
#include "../../Manager/InputManager.h"

class Player
{

public:

	// コンストラクタ
	Player(const int _playerNo);

	// デストラクタ
	~Player(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void DrawUI(int i);
	void Release(void);

	const Vector2F GetReticle(void)const { return reticlePos_; }
	const bool IsAttrck(void)const { return isAttrck_; }

	//ポイント取得
	const int GetPoint(void)const { return point_; }

	const int GetId(void)const { return playerNo_; }

	void AddPoint(int point);

private:
	//定数
	static constexpr float RETICLE_HALF_SIZE = 50.0f/2.0f; //レティクル画像のサイズ半分
	int reticleHndle_;
	Vector2F reticlePos_;
	Vector2F reticlePrePos_;
	Vector2 agoMousePos_;

	//ポイント
	int point_;

	//プレイヤー番号
	int playerNo_;

	//コントローラー番号
	InputManager::JOYPAD_NO joyPadNo_;

	//操作方法別の更新
	std::function<void(void)> typeUpdate_;
	bool isAttrck_;

	bool isClick_;

	void UpdateMouse(void);
	void UpdateController(void);

	//レティクルの移動
	void MoveReticle(void);

	/// <summary>
	/// レティクルが画面外に行ったかどうか
	/// </summary>
	/// <param name=""></param>
	/// <returns>true:画面外に行った false:画面内</returns>
	void LimitReticle(void);

	bool IsMoveableReticle(void) const;
};

