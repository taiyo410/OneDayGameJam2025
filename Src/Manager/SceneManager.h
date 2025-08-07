#pragma once
#include <chrono>
#include <memory>
#include <DxLib.h>


class Fader;
class SceneBase;
class Camera;

class SceneManager
{

public:

	// �V�[���Ǘ��p
	enum class SCENE_ID
	{
		NONE,
		TITLE,	//�^�C�g��
		SELECT,
		GAME,	//�Q�[��
		RESULT,	//���U���g
	};


	// �C���X�^���X�̐���
	static void CreateInstance(void);

	// �C���X�^���X�̎擾
	static SceneManager& GetInstance(void);

	void Init(void);
	void Init3D(void);
	void Update(void);
	void Draw(void);
	void Destroy(void);

	// �V�[���J�ږ���
	void ChangeScene(SCENE_ID nextId);

	// �V�[��ID�̎擾
	SCENE_ID GetSceneID(void);

	// �f���^�^�C���̎擾
	float GetDeltaTime(void) const;

	// �J�����̎擾
	//std::weak_ptr<Camera> GetCamera(void) const;
	//�X�N���[���̎擾
	const int& GetMainScreen(void);

private:

	// �ÓI�C���X�^���X
	static SceneManager* instance_;

	SCENE_ID sceneId_;
	SCENE_ID waitSceneId_;
	
	//�`��X�N���[��
	int mainScreen_;
	int capturedScreenGraph_ = -1; // ���������摜�̃n���h��

	// �t�F�[�h
	std::unique_ptr<Fader> fader_;

	// �e��V�[��
	std::unique_ptr<SceneBase> scene_;

	// �J����
	//std::shared_ptr<Camera> camera_;

	// �V�[���J�ڒ�����
	bool isSceneChanging_;

	// �f���^�^�C��
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;

	// �Q�[���̑�����
	float totalGameTime_;

	// �R���X�g���N�^
	SceneManager(void);

	// �f�X�g���N�^
	~SceneManager(void);

	// �V�[���J��
	void DoChangeScene(SCENE_ID sceneId);

	// �t�F�[�h����
	void Fade(void);

};