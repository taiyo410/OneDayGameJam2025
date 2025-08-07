#pragma once
#include <memory>
#include<functional>
#include "SceneBase.h"

class Player;
class TargetBase;

class GameScene :
    public SceneBase
{

public:

	// �R���X�g���N�^
	GameScene(void);

	// �f�X�g���N�^
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	//�w�i
	int fenceModel_;
	int backGroundImg_;

	std::unique_ptr<Player> player_;
	std::function<void(void)> modeUpdate_;

	std::vector<std::unique_ptr<TargetBase>> targets_;


	void PannelRule();
	void CanRule();

};

