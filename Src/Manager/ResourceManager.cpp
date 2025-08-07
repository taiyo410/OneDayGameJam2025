#include <DxLib.h>
#include "../Application.h"
#include "Resource.h"
#include "ResourceManager.h"


ResourceManager* ResourceManager::instance_ = nullptr;

void ResourceManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new ResourceManager();
	}
	instance_->Init();
}

ResourceManager& ResourceManager::GetInstance(void)
{
	return *instance_;
}

void ResourceManager::Init(void)
{
	static std::string PATH_IMG = Application::PATH_IMAGE;
	static std::string PATH_OBJ = Application::PATH_OBJECT;
	static std::string PATH_MDL = Application::PATH_MODEL;
	static std::string PATH_EFF = Application::PATH_EFFECT;

	std::unique_ptr<Resource> res;

	res = std::make_unique<Resource>(Resource::TYPE::IMG, PATH_IMG + "crosshair184.png");
	resourcesMap_.emplace(SRC::CROSSHAIR, std::move(res));

	res = std::make_unique<Resource>(Resource::TYPE::IMG, PATH_OBJ+"Princess.png");
	resourcesMap_.emplace(SRC::PRINCESS, std::move(res));

	res = std::make_unique<Resource>(Resource::TYPE::IMG, PATH_OBJ + "BanDit.png");
	resourcesMap_.emplace(SRC::BANDIT, std::move(res));

	res = std::make_unique<Resource>(Resource::TYPE::IMG, PATH_IMG + "BackGround.png");
	resourcesMap_.emplace(SRC::BACKGROUND_TITLE, std::move(res));

	res = std::make_unique<Resource>(Resource::TYPE::IMG, PATH_IMG + "Title.png");
	resourcesMap_.emplace(SRC::TITLENAME, std::move(res));

	res = std::make_unique<Resource>(Resource::TYPE::IMG, PATH_OBJ + "Box.png");
	resourcesMap_.emplace(SRC::BOX, std::move(res));

	res = std::make_unique<Resource>(Resource::TYPE::IMG, PATH_OBJ + "Button.png");
	resourcesMap_.emplace(SRC::PUSH_BUTTON, std::move(res));

	res = std::make_unique<Resource>(Resource::TYPE::IMG, PATH_IMG + "Player_Select.png");
	resourcesMap_.emplace(SRC::PLAYER_SELECT_NUM_IMG, std::move(res));

	res = std::make_unique<Resource>(Resource::TYPE::IMGS, PATH_IMG + "Numbers.png",NUMBERS_DIV_X,NUMBERS_DIV_Y,NUMBERS_SIZE, NUMBERS_SIZE);
	resourcesMap_.emplace(SRC::NUMBER_IMG, std::move(res));


	//セレクトシーン画像
	res = std::make_unique<Resource>(Resource::TYPE::IMG, PATH_IMG + "SelectEneless.png");
	resourcesMap_.emplace(SRC::SELECT_ENDLESS, std::move(res));
	res = std::make_unique<Resource>(Resource::TYPE::IMG, PATH_IMG + "SelectMalti.png");
	resourcesMap_.emplace(SRC::SELECT_MELTI, std::move(res));
	res = std::make_unique<Resource>(Resource::TYPE::IMG, PATH_IMG + "BackSelect.png");
	resourcesMap_.emplace(SRC::BACKSELECT, std::move(res));
	res = std::make_unique<Resource>(Resource::TYPE::IMG, PATH_IMG + "SelectPanel.png");
	resourcesMap_.emplace(SRC::SELECT_PANEL, std::move(res));
}

void ResourceManager::SceneChangeRelease(void)
{
	for (auto& p : loadedMap_)
	{
		p.second.Release();
	}

	loadedMap_.clear();
}

void ResourceManager::Release(void)
{
	SceneChangeRelease();
	resourcesMap_.clear();
}

const Resource& ResourceManager::Load(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return dummy_;
	}
	return res;
}

int ResourceManager::LoadModelDuplicate(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return -1;
	}

	int duId = MV1DuplicateModel(res.handleId_);
	res.duplicateModelIds_.push_back(duId);

	return duId;
}

ResourceManager::ResourceManager(void)
{
}

Resource& ResourceManager::_Load(SRC src)
{

	// ロード済みチェック
	const auto& lPair = loadedMap_.find(src);
	if (lPair != loadedMap_.end())
	{
		return lPair->second;
	}

	// リソース登録チェック
	const auto& rPair = resourcesMap_.find(src);
	if (rPair == resourcesMap_.end())
	{
		// 登録されていない
		return dummy_;
	}

	// ロード処理
	rPair->second->Load();

	// 念のためコピーコンストラクタ
	loadedMap_.emplace(src, *rPair->second);

	return *rPair->second;

}
