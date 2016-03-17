
#pragma once

#include "base/CCRef.h"
#include <vector>

NS_CC_BEGIN

class CC_DLL GamePad : public Ref
{
public:
	static GamePad* create(int id);
	virtual ~GamePad();

	bool isPresent();
	std::vector<unsigned char> getButtons();
	std::vector<float> getAxis();

private:
	bool init(int id);

	int _id;
};

NS_CC_END