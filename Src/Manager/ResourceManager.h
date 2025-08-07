#pragma once
#include <map>
#include <string>
#include "Resource.h"
#include<memory>

class ResourceManager
{

public:
	//�C���X�^���X����
	// �C���X�^���X�𖾎��I�ɐ���
	static void CreateInstance(void);

	// �C���X�^���X�̎擾
	static ResourceManager& GetInstance(void);

	/// <summary>
	/// ���\�[�X��
	/// </summary>
	enum class SRC
	{
		NONE,
		CROSSHAIR,
		PRINCESS,
		BANDIT,
		BACKGROUND_TITLE,
	};

	/// <summary>
	/// ������
	/// </summary>
	/// <param name=""></param>
	void Init(void);

	/// <summary>
	/// ���(�V�[���ؑ֎��Ɉ�U���)
	/// </summary>
	/// <param name=""></param>
	void SceneChangeRelease(void);

	/// <summary>
	/// ���\�[�X�̊��S���
	/// </summary>
	/// <param name=""></param>
	void Release(void);

	/// <summary>
	/// ���\�[�X�̃��[�h
	/// </summary>
	/// <param name="src">�ǂݍ��ރ��\�[�X</param>
	/// <returns>���\�[�X</returns>
	const Resource& Load(SRC src);

	/// <summary>
	/// ���\�[�X�̕������[�h(���f���p)
	/// </summary>
	/// <param name="src">�������������\�[�X</param>
	/// <returns>�����������\�[�X</returns>
	int LoadModelDuplicate(SRC src);

private:

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
// �O�����琶���ł��Ȃ��l�ɂ���
	ResourceManager(void);
	ResourceManager(const ResourceManager& manager) = default;
	~ResourceManager(void) = default;

	// ���\�[�X�Ǘ��̑Ώ�
	std::map<SRC, std::unique_ptr<Resource>> resourcesMap_;

	// �ǂݍ��ݍς݃��\�[�X
	std::map<SRC, Resource&> loadedMap_;

	Resource dummy_;

	// �V���O���g���p�C���X�^���X
	static ResourceManager* instance_;

	// �������[�h
	Resource& _Load(SRC src);

};
