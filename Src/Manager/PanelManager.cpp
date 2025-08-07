#include"../Object/Target/Panel.h"
#include "PanelManager.h"

PanelManager* PanelManager::instance_ = nullptr;
void PanelManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new PanelManager();
	}
}

PanelManager& PanelManager::GetInstance(void)
{
	return *instance_;
}

void PanelManager::Init(void)
{
	for (int i = 0; i < PANNEL_NUM_MAX; i++)
	{
		std::unique_ptr<Panel> panel;
		panel = std::make_unique<Panel>();
		panel->Init();
		panels_.emplace_back(std::move(panel));
	}
}

void PanelManager::Update(void)
{
	for (auto& panel : panels_)
	{
		panel->Update();
	}
}

void PanelManager::Draw(void)
{
	for (auto& panel : panels_)
	{
		panel->Draw();
	}
}
