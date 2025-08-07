#pragma once
#include <memory>
#include "SceneBase.h"

class Player;

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


	std::unique_ptr<Player> player_;


};

