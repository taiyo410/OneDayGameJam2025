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
	void Update(void) ;
	void Draw(void) ;
	void Release(void) ;

private:

	int reticleHndle_;
	Vector2 reticlePos_;
	Vector2 agoMousePos_;

	//操作方法別の更新
	std::function<void(void)> typeUpdate_;

	void UpdateMouse(void);
	void UpdateController(void);

};

