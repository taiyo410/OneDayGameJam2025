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

	// �R���X�g���N�^
	GameScene(void);

	// �f�X�g���N�^
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	//�ǉ��|�C���g
	static constexpr int ADD_POINT = 2;

	//���炷�|�C���g
	static constexpr int SUB_POINT = -1;
	//�w�i
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

