#pragma once
#include<functional>

class Player
{

public:

	// コンストラクタ
	Player(void);

	// デストラクタ
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

	//ポイント
	int point_;

	//操作方法別の更新
	std::function<void(void)> typeUpdate_;
	bool isAttrck_;

	void UpdateMouse(void);
	void UpdateController(void);

	//レティクルの移動
	void MoveReticle(void);

};

