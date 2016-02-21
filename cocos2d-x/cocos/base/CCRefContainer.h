
#pragma once

#include "base/CCRef.h"
#include <vector>

NS_CC_BEGIN

class CC_DLL RefContainer : public Ref
{
public:
	static RefContainer* create();
	virtual ~RefContainer();

	void add(Ref* ref);

private:
	std::vector<Ref*> refs;
};

NS_CC_END