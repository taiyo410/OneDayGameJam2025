#include "InputManager.h"
#include "DataBank.h"

DataBank* DataBank::instance_ = nullptr;

void DataBank::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new DataBank();
	}
	instance_->Init();
}

DataBank& DataBank::GetInstance(void)
{
    return *instance_;
}

void DataBank::Init(void)
{
	playerNum_ = 0;
	maxPlayerNum_ = GetJoypadNum();
}

void DataBank::Destroy(void)
{
	if (instance_ != nullptr)
	{
		delete instance_;
		instance_ = nullptr;
	}
}

bool DataBank::SetPlayerNum(int _num)
{
	playerNum_ = _num;
	return true;
	return false;
}

int DataBank::GetPlayerNum(void)
{
	return playerNum_;
}

const SelectScene::SELECT_ID DataBank::GetSelectId(void)const
{
	return selectId_;
}

void DataBank::SetSelectId(const SelectScene::SELECT_ID _id)
{
	selectId_ = _id;
}


DataBank::DataBank(void)
{
	maxPlayerNum_ = 0;
	playerNum_ = 0;
}

DataBank::~DataBank(void)
{
}
