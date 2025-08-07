#pragma once
#include<memory>
#include<vector>
class Panel;
class PanelManager
{
public:
	static void CreateInstance(void);
	static PanelManager& GetInstance(void);

	static constexpr int PANNEL_NUM_MAX = 5;

	void Init(void);
	void Update(void);
	void Draw(void);

private:
	// 外部から生成できない様にする
	PanelManager(void);
	PanelManager(const PanelManager& manager) = default;
	~PanelManager(void) = default;

	//パネル
	std::vector<std::unique_ptr<Panel>>panels_;

	//

	// シングルトン用インスタンス
	static PanelManager* instance_;
};

