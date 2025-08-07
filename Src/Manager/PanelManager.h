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
	// �O�����琶���ł��Ȃ��l�ɂ���
	PanelManager(void);
	PanelManager(const PanelManager& manager) = default;
	~PanelManager(void) = default;

	//�p�l��
	std::vector<std::unique_ptr<Panel>>panels_;

	//

	// �V���O���g���p�C���X�^���X
	static PanelManager* instance_;
};

