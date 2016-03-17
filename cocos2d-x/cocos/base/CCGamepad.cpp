
#include "CCGamePad.h"
#include "glfw3.h"

NS_CC_BEGIN

GamePad* GamePad::create(int id)
{
	GamePad * ret = new GamePad();
	if (ret->init(id))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

GamePad::~GamePad()
{
}

bool GamePad::init(int id)
{
	this->_id = id;
	return true;
}

bool GamePad::isPresent()
{
	return glfwJoystickPresent(_id) !=  0;
}

std::vector<unsigned char> GamePad::getButtons()
{
	std::vector<unsigned char> result;

	int count;
	auto values = glfwGetJoystickButtons(_id, &count);
	if (count > 0)
	{
		result.insert(std::begin(result), values, values + count);
	}
	return result;
}

std::vector<float> GamePad::getAxis()
{
	std::vector<float> result;

	int count;
	auto values = glfwGetJoystickAxes(_id, &count);
	if (count > 0)
	{
		result.insert(std::begin(result), values, values + count);
	}
	return result;
}

NS_CC_END