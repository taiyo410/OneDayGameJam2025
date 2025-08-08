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

	//バトルＢＧＭ
	res = Sound(Sound::TYPE::SOUND_2D, Application::PATH_SOUND + "game_bgm.mp3");
	res.ChengeMaxVolume(0.4f);
	soundMap_.emplace(SRC::GAME_BGM, res);



	res = Sound(Sound::TYPE::SOUND_2D, Application::PATH_SOUND + "SowrdDamage.mp3");//今回使うのはこれ
	res.ChengeMaxVolume(0.6f);
	
	//コネクトシーンで使用
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
	

	//あたった時の音
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
		p.second.Release();  // サウンドのリソースを解放

		// p.second が動的に確保されたオブジェクトであれば、以下のようにメモリ解放
		// delete p.second; // 必要に応じて、メモリを解放する

	}

	soundMap_.clear();  // マップをクリア
}

void SoundManager::Destroy(void)
{
	Release();
	soundMap_.clear();
	delete instance_;
}

//音の再生
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
	if (lPair != soundMap_.end())//指定のものが存在するか？
	{
		return lPair->second.Stop();
	}
}
void SoundManager::AllStop(void)
{
	// soundMap_ のすべての要素に対して Stop() を呼び出す
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
//再生中か?
bool SoundManager::CheckMove(SRC src)
{
	const auto& lPair = soundMap_.find(src);
	if (lPair != soundMap_.end())
	{
		return lPair->second.CheckMove();
	}
	return false;
}
//音量
void SoundManager::ChengeVolume(SRC src, float per)
{
	const auto& lPair = soundMap_.find(src);
	if (lPair != soundMap_.end())
	{
		return lPair->second.ChengeVolume(per);
	}
}
