#include <EffekseerForDXLib.h>
#include "EffectController.h"

EffectController::EffectController(void)
{
	/*auto effec = std::make_unique<EFFECT>();
	effec->ResId = ResourceManager::GetInstance().Load(
		ResourceManager::SRC::FOOT_SMOKE).handleId_;

	effects_.emplace(0, std::move(effec));*/
}

EffectController::~EffectController(void)
{
	effects_.clear();
}

void EffectController::Add(int type, std::string str)
{

	auto effec = std::make_unique<EFFECT>();
	effec->ResId  = LoadEffekseerEffect(str.c_str());

	effects_.emplace(type, std::move(effec));
}

void EffectController::Play(int type)
{
	// �w�肳�ꂽ�G�t�F�N�g�����݂��Ȃ��ꍇ�͏������Ȃ�
	auto it = effects_.find(type);
	if (it == effects_.end()) {
		return;
	}

	// �G�t�F�N�g���Đ�����
	effects_[type]->PlayId_ = PlayEffekseer3DEffect(effects_[type]->ResId);

	SetScalePlayingEffekseer3DEffect(effects_[type]->PlayId_, 1.0f, 1.0f, 1.0f);
	SetRotationPlayingEffekseer3DEffect(effects_[type]->PlayId_, 0.0f, 0.0f, 0.0f);
	SetPosPlayingEffekseer3DEffect(effects_[type]->PlayId_, 1.0f, 1.0f, 1.0f);

	
}
void EffectController::Play(int type, const VECTOR pos, VECTOR rot, float scale)
{
	// �w�肳�ꂽ�G�t�F�N�g�����݂��Ȃ��ꍇ�͏������Ȃ�
	auto it = effects_.find(type);
	if (it == effects_.end()) {
		return;
	}

	// �G�t�F�N�g���Đ�����
	effects_[type]->PlayId_ = PlayEffekseer3DEffect(effects_[type]->ResId);

	SetScalePlayingEffekseer3DEffect(effects_[type]->PlayId_, scale, scale, scale);
	SetRotationPlayingEffekseer3DEffect(effects_[type]->PlayId_, rot.x, rot.y, rot.z);
	SetPosPlayingEffekseer3DEffect(effects_[type]->PlayId_, pos.x, pos.y, pos.z);

}
//�A�j���[�V�������I��Ă�����Đ�
void EffectController::LoopPlay(int type)
{
	// �w�肳�ꂽ�G�t�F�N�g�����݂��Ȃ��ꍇ�͏������Ȃ�
	auto it = effects_.find(type);
	if (it == effects_.end()) {
		return;
	}

	int ret = IsEffekseer3DEffectPlaying(effects_[type]->PlayId_);
	if (ret == -1)
	{
		// �G�t�F�N�g���Đ�����
		effects_[type]->PlayId_ = PlayEffekseer3DEffect(effects_[type]->ResId);

		/*SetScalePlayingEffekseer3DEffect(effects_[type]->PlayId_, 1.0f, 1.0f, 1.0f);
		SetRotationPlayingEffekseer3DEffect(effects_[type]->PlayId_, 0.0f, 0.0f, 0.0f);
		SetPosPlayingEffekseer3DEffect(effects_[type]->PlayId_, 1.0f, 1.0f, 1.0f);*/
	}
}

void EffectController::Stop(int type)
{
	StopEffekseer3DEffect(effects_[type]->PlayId_);
}

void EffectController::LoopUpdate(int type, const VECTOR pos, VECTOR rot, float scale)
{
	// �w�肳�ꂽ�G�t�F�N�g�����݂��Ȃ��ꍇ�͏������Ȃ�
	auto it = effects_.find(type);
	if (it == effects_.end()) {
		return;
	}

	SetScalePlayingEffekseer3DEffect(effects_[type]->PlayId_, scale, scale, scale);
	SetRotationPlayingEffekseer3DEffect(effects_[type]->PlayId_, rot.x, rot.y, rot.z);
	SetPosPlayingEffekseer3DEffect(effects_[type]->PlayId_, pos.x, pos.y, pos.z);
}
void EffectController::Update(int type, const VECTOR pos, VECTOR rot, float scale)
{
	// �w�肳�ꂽ�G�t�F�N�g�����݂��Ȃ��ꍇ�͏������Ȃ�
	auto it = effects_.find(type);
	if (it == effects_.end()) {
		return;
	}

	SetScalePlayingEffekseer3DEffect(effects_[type]->PlayId_, scale, scale, scale);
	SetRotationPlayingEffekseer3DEffect(effects_[type]->PlayId_, rot.x, rot.y, rot.z);
	SetPosPlayingEffekseer3DEffect(effects_[type]->PlayId_, pos.x, pos.y, pos.z);

	// �G�t�F�N�g�Đ��`�F�b�N
	// 0:�Đ����A-1:�Đ�����Ă��Ȃ��A�������͍Đ��I��
	int ret = IsEffekseer3DEffectPlaying(effects_[type]->PlayId_);
	if (ret == -1)
	{
		StopEffekseer3DEffect(effects_[type]->PlayId_);
	}
}

void EffectController::Update(int type)
{
	// �w�肳�ꂽ�G�t�F�N�g�����݂��Ȃ��ꍇ�͏������Ȃ�
	auto it = effects_.find(type);
	if (it == effects_.end()) {
		return;
	}

	// �G�t�F�N�g�Đ��`�F�b�N
	// 0:�Đ����A-1:�Đ�����Ă��Ȃ��A�������͍Đ��I��
	int ret = IsEffekseer3DEffectPlaying(effects_[type]->PlayId_);
	if (ret == -1)
	{
		StopEffekseer3DEffect(effects_[type]->PlayId_);
	}
}
