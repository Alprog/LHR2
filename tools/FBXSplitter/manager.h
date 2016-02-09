
#pragma once

#include <fbxsdk.h>

class Manager
{
	FbxManager* manager;

public:
	Manager();

	FbxScene* Import(const char* fileName);
	void Export(FbxScene* scene, const char* fileName, bool textFormat = false);
};
