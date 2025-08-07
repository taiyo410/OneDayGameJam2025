#include <EffekseerForDXLib.h>
#include <DxLib.h>

#include <string>
#include <fstream>

#include "../Application.h"
#include "../Common/Fader.h"

#include "../Scene/SceneBase.h"
#include "../Scene/TitleScene.h"
#include "../Scene/GameScene.h"
#include "../Scene/ResultScene.h"

#include "SceneManager.h"

SceneManager* SceneManager::instance_ = nullptr;

SceneManager::SceneManager(void)
{

	sceneId_ = SCENE_ID::NONE;
	waitSceneId_ = SCENE_ID::NONE;

	

	isSceneChanging_ = false;

	//camera_ = nullptr;


}

SceneManager::~SceneManager(void)
{
	delete instance_;
}

void SceneManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();
	}
	instance_->Init();
}

SceneManager& SceneManager::GetInstance(void)
{
	return *instance_;
}

void SceneManager::Init(void)
{

	sceneId_ = SCENE_ID::TITLE;
	waitSceneId_ = SCENE_ID::NONE;

	fader_ = std::make_unique<Fader>();
	fader_->Init();

	// �J����
	/*camera_ = std::make_shared<Camera>();
	camera_->Init();*/

	isSceneChanging_ = false;

	totalGameTime_ = 0.0f;

	// 3D�p�̐ݒ�
	Init3D();

	// �����V�[���̐ݒ�
	DoChangeScene(SCENE_ID::TITLE);

}
void SceneManager::Init3D(void)
{

	// �w�i�F�ݒ�
	SetBackgroundColor(0, 139, 139);

	// Z�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(true);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(true);

	// �o�b�N�J�����O��L���ɂ���
	SetUseBackCulling(true);

	// ���C�g�̐ݒ�
	SetUseLighting(true);

	// ���C�g�̐ݒ�
	ChangeLightTypeDir({ 0.3f, -0.7f, 0.8f });
	//ChangeLightTypePoint({ 0.0f, -100.0f, 0.0f },20000.0f, 0.0f, 0.0006f, 0.0f);


	// �t�H�O�ݒ�
	SetFogEnable(true);
	SetFogColor(5, 5, 5);
	SetFogStartEnd(10000.0f, 20000.0f);

	mainScreen_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y);
}

void SceneManager::Update(void)
{

	// �f���^�^�C��
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	preTime_ = nowTime;

	// �t�F�[�h�X�V
	fader_->Update();
	if (isSceneChanging_)
	{
		Fade();
	}
	else
	{
		// �X�V
		scene_->Update();
	}

	// �J�����X�V
	//camera_->Update();
}

void SceneManager::Draw(void)
{

	// �`���O���t�B�b�N�̈�̎w��
	// (�R�c�`��Ŏg�p����J�����̐ݒ�Ȃǂ����Z�b�g�����)
	SetDrawScreen(mainScreen_);

	// ��ʂ�������
	ClearDrawScreen();

	// �J�����ݒ�
	//camera_->SetBeforeDraw();

	// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	UpdateEffekseer3D();

	// �`��
	scene_->Draw();

	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	DrawEffekseer3D();

	// �Ō�
	fader_->Draw();

	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraph(0, 0, mainScreen_, true);

}

void SceneManager::Destroy(void)
{
	DeleteGraph(mainScreen_);

	if (capturedScreenGraph_ != -1)
	{
		DeleteGraph(capturedScreenGraph_);
		capturedScreenGraph_ = -1;
	}
}

void SceneManager::ChangeScene(SCENE_ID nextId)
{

	// �t�F�[�h�������I����Ă���V�[����ς���ꍇ�����邽�߁A
	// �J�ڐ�V�[���������o�ϐ��ɕێ�
	waitSceneId_ = nextId;

	// �t�F�[�h�A�E�g(�Ó])���J�n����
	fader_->SetFade(Fader::NET_STATE::FADE_OUT);
	isSceneChanging_ = true;

}

SceneManager::SCENE_ID SceneManager::GetSceneID(void)
{
	return sceneId_;
}

float SceneManager::GetDeltaTime(void) const
{
	//return 1.0f / DEFAULT_FPS;
	return deltaTime_;
}


//std::weak_ptr<Camera> SceneManager::GetCamera(void) const
//{
//	return camera_;
//}

const int& SceneManager::GetMainScreen(void)
{
	return mainScreen_;
}

void SceneManager::DoChangeScene(SCENE_ID sceneId)
{


	// ���\�[�X�̉��
	//ResourceManager::GetInstance().Release();

	// �V�[����ύX����
	sceneId_ = sceneId;

	// ���݂̃V�[�������
	if (scene_ != nullptr)
	{
		scene_.reset();
	}

	switch (sceneId_)
	{
	case SCENE_ID::TITLE:
		scene_ = std::make_unique<TitleScene>();
		break;
	case SCENE_ID::GAME:
		scene_ = std::make_unique<GameScene>();
		break;
	case SCENE_ID::RESULT:
		scene_ = std::make_unique<ResultScene>();
		break;
	}

	scene_->Init();

	//ResetDeltaTime();

	waitSceneId_ = SCENE_ID::NONE;


	// �t�H���g�T�C�Y�����ɖ߂�
	SetFontSize(16);

}

void SceneManager::Fade(void)
{

	Fader::NET_STATE fState = fader_->GetState();
	switch (fState)
	{
	case Fader::NET_STATE::FADE_OUT:
		if (fader_->IsEnd())
		{
			// �Ó]��A�V�[���ύX
			DoChangeScene(waitSceneId_);
			fader_->SetFade(Fader::NET_STATE::FADE_IN);
		}
		break;
	case Fader::NET_STATE::FADE_IN:
		if (fader_->IsEnd())
		{
			// ���]��A�V�[���J�ڏI��
			fader_->SetFade(Fader::NET_STATE::NONE);
			isSceneChanging_ = false;
		}
		break;
	}

}
