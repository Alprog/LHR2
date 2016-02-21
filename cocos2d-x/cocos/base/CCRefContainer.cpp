
#include "CCRefContainer.h"

NS_CC_BEGIN

RefContainer* RefContainer::create()
{
	RefContainer * ret = new RefContainer();
	if (ret)
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

RefContainer::~RefContainer()
{
	for (auto& ref : refs)
	{
		ref->release();
	}
	refs.clear();
}

void RefContainer::add(Ref* ref)
{
	refs.push_back(ref);
	ref->retain();
}

NS_CC_END