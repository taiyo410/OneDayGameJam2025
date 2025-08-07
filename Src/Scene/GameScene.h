#pragma once
#include <memory>
#include<functional>
#include "SceneBase.h"

class Player;
class TargetBase;

class EffectController;

class GameScene :
    public SceneBase
{

public:

	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	//追加ポイント
	static constexpr int ADD_POINT = 2;

	//減らすポイント
	static constexpr int SUB_POINT = -1;
	//背景
	int fenceModel_;
	int backGroundImg_;

	std::vector<std::unique_ptr<Player>> players_;
	std::function<void(void)> modeUpdate_;
	std::function<void(void)> modeDraw_;

	std::vector<std::unique_ptr<TargetBase>> targets_;

	std::unique_ptr<EffectController> effec_;

	void PannelRule();
	void CanRule();

};

