#pragma once
#include "./Common/Transform.h"

class ResourceManager;
class SceneManager;

class ObjectBase
{
	//��

public:

	// �R���X�g���N�^
	ObjectBase(void);

	// �f�X�g���N�^
	virtual ~ObjectBase(void);

	virtual void Load(void) = 0;
	virtual void Init(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	inline const Transform& GetTransform(void) const { return trans_; }

protected:

	// �V���O���g���Q��
	ResourceManager& resMng_;
	SceneManager& scnMng_;

	// ���f������̊�{���
	Transform trans_;

};

