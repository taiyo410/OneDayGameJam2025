#include <DxLib.h>
#include "../Application.h"
#include "SoundManager.h"

SoundManager* SoundManager::instance_ = nullptr;

void SoundManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new SoundManager();
	}
	instance_->Init();
}

SoundManager& SoundManager::GetInstance(void)
{
	return *instance_;
}

void SoundManager::Init(void)
{
	Sound res;

	/*res = Sound(Sound::TYPE::SOUND_2D, Application::PATH_SOUND + "TitleBGM.mp3");
	res.ChengeMaxVolume(0.8f);
	soundMap_.emplace(SRC::TITLE_BGM, res);

	res = Sound(Sound::TYPE::SOUND_2D, Application::PATH_SOUND + "SelectBGM.mp3");
	res.ChengeMaxVolume(1.0f);
	soundMap_.emplace(SRC::SELECT_BGM, res);
	*/

	//�o�g���a�f�l
	res = Sound(Sound::TYPE::SOUND_2D, Application::PATH_SOUND + "game_bgm.mp3");
	res.ChengeMaxVolume(0.4f);
	soundMap_.emplace(SRC::GAME_BGM, res);



	res = Sound(Sound::TYPE::SOUND_2D, Application::PATH_SOUND + "SowrdDamage.mp3");//����g���̂͂���
	res.ChengeMaxVolume(0.6f);
	
	//�R�l�N�g�V�[���Ŏg�p
	res = Sound(Sound::TYPE::SOUND_2D, Application::PATH_SOUND + "Conect/Start.mp3");
	res.ChengeMaxVolume(0.8f);


	//SESelect.mp3
	res = Sound(Sound::TYPE::SOUND_2D, Application::PATH_SOUND + "Deffult/Select.mp3");
	res.ChengeMaxVolume(1.0f);
	soundMap_.emplace(SRC::SELECT, res);
	res = Sound(Sound::TYPE::SOUND_2D, Application::PATH_SOUND + "Deffult/Enter.mp3");
	res.ChengeMaxVolume(1.0f);
	soundMap_.emplace(SRC::ENTER, res);
	res = Sound(Sound::TYPE::SOUND_2D, Application::PATH_SOUND + "Deffult/Start.mp3");
	res.ChengeMaxVolume(0.8f);
	soundMap_.emplace(SRC::START, res);
	res = Sound(Sound::TYPE::SOUND_2D, Application::PATH_SOUND + "Deffult/GameStart.mp3");
	res.ChengeMaxVolume(0.6f);
	

	//�����������̉�
 	res = Sound(Sound::TYPE::SOUND_2D, Application::PATH_SOUND + "Hit.mp3");
	res.ChengeMaxVolume(0.2f);
	soundMap_.emplace(SRC::HIT, res);
	

	//res = Sound(Sound::TYPE::SOUND_2D, Application::PATH_SOUND + "TitleBGM.mp3");
	//soundMap_.emplace(SRC::TITLE_BGM, res);
}

void SoundManager::Release(void)
{
	for (auto& p : soundMap_)
	{
		p.second.Release();  // �T�E���h�̃��\�[�X�����

		// p.second �����I�Ɋm�ۂ��ꂽ�I�u�W�F�N�g�ł���΁A�ȉ��̂悤�Ƀ��������
		// delete p.second; // �K�v�ɉ����āA���������������

	}

	soundMap_.clear();  // �}�b�v���N���A
}

void SoundManager::Destroy(void)
{
	Release();
	soundMap_.clear();
	delete instance_;
}

//���̍Đ�
bool SoundManager::Play(SRC src, Sound::TIMES times, bool isForce)
{
	const auto& lPair = soundMap_.find(src);
	if (lPair != soundMap_.end())
	{
		if (!lPair->second.CheckLoad())
		{
			lPair->second.Load();
		}
		return lPair->second.Play(times, isForce);
	}
	return false;
}
bool SoundManager::Play(SRC src, Sound::TIMES times, VECTOR pos, float radius)
{
	const auto& lPair = soundMap_.find(src);
	if (lPair != soundMap_.end())
	{
		if (!lPair->second.CheckLoad())
		{
			lPair->second.Load();
		}
		return lPair->second.Play(pos, radius, times);
	}
	return false;
}

void SoundManager::Stop(SRC src)
{
	const auto& lPair = soundMap_.find(src);
	if (lPair != soundMap_.end())//�w��̂��̂����݂��邩�H
	{
		return lPair->second.Stop();
	}
}
void SoundManager::AllStop(void)
{
	// soundMap_ �̂��ׂĂ̗v�f�ɑ΂��� Stop() ���Ăяo��
	for (auto& lPair : soundMap_)
	{
		lPair.second.Stop();
	}
}

bool SoundManager::Pause(SRC src, Sound::TIMES times)
{
	const auto& lPair = soundMap_.find(src);
	if (lPair != soundMap_.end())
	{
		if (!lPair->second.CheckLoad())
		{
			lPair->second.Load();
		}
		lPair->second.Pause(times);
		return true;
	}
	return false;
}
bool SoundManager::Resume(SRC src, Sound::TIMES times)
{
	const auto& lPair = soundMap_.find(src);
	if (lPair != soundMap_.end())
	{
		if (!lPair->second.CheckLoad())
		{
			lPair->second.Load();
		}
		lPair->second.Resume(times);
		return true;

	}
	return false;
}
//�Đ�����?
bool SoundManager::CheckMove(SRC src)
{
	const auto& lPair = soundMap_.find(src);
	if (lPair != soundMap_.end())
	{
		return lPair->second.CheckMove();
	}
	return false;
}
//����
void SoundManager::ChengeVolume(SRC src, float per)
{
	const auto& lPair = soundMap_.find(src);
	if (lPair != soundMap_.end())
	{
		return lPair->second.ChengeVolume(per);
	}
}
