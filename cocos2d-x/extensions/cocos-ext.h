#ifndef __COCOS2D_EXT_H__
#define __COCOS2D_EXT_H__

#include "ExtensionMacros.h"


#include "GUI/CCControlExtension/CCControlExtensions.h"
#include "GUI/CCScrollView/CCScrollView.h"
#include "GUI/CCScrollView/CCTableView.h"

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT && _MSC_VER < 1900)
// Window 10 UWP does not yet support CURL
#endif

#include "ExtensionDeprecated.h"

#endif /* __COCOS2D_EXT_H__ */
