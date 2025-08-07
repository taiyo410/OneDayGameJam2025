#pragma once
#include <map>
#include <memory>
#include <string>
#include <EffekseerForDXLib.h>


class EffectController
{
public:

	// �A�j���[�V�����f�[�^
	struct EFFECT
	{
		int ResId = -1;
		int PlayId_ = -1;

		~EFFECT() {
			if (PlayId_ != -1 && IsEffekseer3DEffectPlaying(PlayId_) == 0) {
				StopEffekseer3DEffect(PlayId_);
			}

			if (ResId != -1) {
				DeleteEffekseerEffect(ResId);
			}
		}
	};

	EffectController(void);
	~EffectController(void);

	void Add(int type, std::string str);

	void Play(int type);
	void Play(int type, const VECTOR pos, VECTOR rot = { 0.0f,0.0f,0.0f }, float scale = 1.0f);
	void LoopPlay(int type);
	void Stop(int type);

	void LoopUpdate(int type, const VECTOR pos, VECTOR rot = { 0.0f,0.0f,0.0f }, float scale = 1.0f);
	void Update(int type, const VECTOR pos, VECTOR rot = { 0.0f,0.0f,0.0f }, float scale = 1.0f);
	void Update(int type = -1);

private:




	// ��ޕʂ̃A�j���[�V�����f�[�^
	std::map<int, std::unique_ptr<EFFECT>> effects_;

};

