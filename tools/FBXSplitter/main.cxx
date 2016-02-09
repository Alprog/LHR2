
#include <fbxsdk.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "manager.h"

struct AnimationInfo
{
	std::string name;
	int startFrame;
	int stopFrame;
};

void DeleteEmptyNodes(FbxAnimLayer* layer)
{
	auto count = layer->GetSrcObjectCount<FbxAnimCurveNode>();
	for (int i = count - 1; i >= 0; i--)
	{
		auto curveNode = layer->GetSrcObject<FbxAnimCurveNode>(i);
		auto channelCount = curveNode->GetChannelsCount();
		int curveCount = 0;
		for (int j = 0; j < channelCount; j++)
		{
			curveCount += curveNode->GetCurveCount(j);
		}
		if (curveCount == 0)
		{
			layer->RemoveMember(curveNode);
		}
	}
}

void ClearLayer(FbxAnimLayer* layer)
{
	auto count = layer->GetSrcObjectCount<FbxAnimCurveNode>();
	for (int i = count - 1; i >= 0; i--)
	{
		auto curveNode = layer->GetSrcObject<FbxAnimCurveNode>(i);
		auto channelCount = curveNode->GetChannelsCount();
		for (int j = 0; j < channelCount; j++)
		{
			auto curveCount = curveNode->GetCurveCount(j);
			for (auto k = 0; k < curveCount; k++)
			{
				auto curve = curveNode->GetCurve(j, k);
				curve->KeyClear();
				curveNode->DisconnectFromChannel(curve, j);
			}
		}
		layer->RemoveMember(curveNode);
	}
}

FbxAnimCurve* CloneCurve(FbxAnimCurve* original, AnimationInfo& info)
{
	auto clone = FbxAnimCurve::Create(original->GetFbxManager(), original->GetName());

	auto keyCount = original->KeyGetCount();

	bool start = false;
	for (int i = 0; i < keyCount; i++)
	{
		auto key = original->KeyGet(i);
		auto time = key.GetTime();
		auto frame = time.GetFrameCount();

		if (!start)
		{
			if (frame >= info.startFrame)
			{
				start = true;
				i = frame == info.startFrame ? i - 1 : i - 2;
			}
		}
		else
		{
			time.SetFrame(frame - info.startFrame);
			clone->KeyAdd(time, key);
			if (frame >= info.stopFrame)
			{
				break;
			}
		}
	}

	return clone;
}

FbxAnimCurveNode* CloneNode(FbxAnimCurveNode* original, AnimationInfo& info)
{
	auto clone = (FbxAnimCurveNode*)original->Clone();
	auto count = original->GetDstPropertyCount();
	for (int i = 0; i < count; i++)
	{
		auto prop = original->GetDstProperty(i);
		clone->ConnectDstProperty(prop);
	}

	int channelCount = original->GetChannelsCount();
	for (int chIndex = 0; chIndex < channelCount; chIndex++)
	{
		int curveCount = original->GetCurveCount(chIndex);
		for (int crvIndex = 0; crvIndex < curveCount; crvIndex++)
		{
			auto originalCurve = original->GetCurve(chIndex, crvIndex);
			auto curve = CloneCurve(originalCurve, info);
			clone->ConnectToChannel(curve, chIndex);
		}
	}

	return clone;
}

void CreateAnimation(FbxScene* scene, FbxAnimLayer* srcLayer, AnimationInfo info)
{
	auto stack = FbxAnimStack::Create(scene, info.name.c_str());

	auto layer = FbxAnimLayer::Create(stack, "BaseLayer");
	auto count = srcLayer->GetSrcObjectCount<FbxAnimCurveNode>();
	for (int i = 0; i < count; i++)
	{
		auto srcNode = srcLayer->GetSrcObject<FbxAnimCurveNode>(i);
		auto node = CloneNode(srcNode, info);
		layer->AddMember(node);
	}
	stack->AddMember(layer);

	FbxTime time;
	time.SetFrame(info.stopFrame - info.startFrame);
	stack->LocalStop = time;
}

void PressEnterToContinue()
{
	printf("Press ENTER to continue... ");
	char c;
	do
	{
		c = getchar();
	} 
	while ((c != '\n') && (c != EOF));
}

std::vector<AnimationInfo> GetAnimations(std::string txtFile)
{
	std::vector<AnimationInfo> vector;

	std::ifstream stream;
	stream.open(txtFile);
	std::vector<std::string> words;
	std::string word;
	while (stream >> word)
	{
		words.push_back(word);
		if (words.size() == 3)
		{
			AnimationInfo info;
			info.name = words[0];
			info.startFrame = std::atoi(words[1].c_str());
			info.stopFrame = std::atoi(words[2].c_str());
			vector.push_back(info);
			words.clear();
		}
	}

	return vector;
}

void Process(std::string fbxFile, std::string txtFile, bool textFormat)
{
	if (fbxFile.empty())
	{
		printf("no fbx file specify\n");
		return;
	}
	if (txtFile.empty())
	{
		printf("no .txt file specify\n");
		return;
	}

	auto len = fbxFile.size();
	auto outputFile = fbxFile.substr(0, len - 4) + ".fix";

	Manager* manager = new Manager();
	FbxScene* scene = manager->Import(fbxFile.c_str());
	auto mode = scene->GetGlobalSettings().GetTimeMode();
	FbxTime::SetGlobalTimeMode(mode);

	auto stack = scene->GetCurrentAnimationStack();
	auto layer = stack->GetMember<FbxAnimLayer>(0);
	DeleteEmptyNodes(layer);
	scene->RemoveAnimStack(stack->GetName());

	auto animations = GetAnimations(txtFile);
	for (auto& animationInfo : animations)
	{
		CreateAnimation(scene, layer, animationInfo);
	}

	ClearLayer(layer);

	manager->Export(scene, outputFile.c_str(), textFormat);

	printf("done\n");
}

int main(int argc, char** argv)
{

	std::string fbxFile;
	std::string txtFile;
	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];
		auto len = arg.size();
		auto extension = arg.substr(len - 4, 4);
		std::transform(std::begin(extension), std::end(extension), std::begin(extension), ::tolower);
		if (extension == ".fbx")
		{
			fbxFile = arg;
		}
		else if (extension == ".txt")
		{
			txtFile = arg;
		}
	}

	//fbxFile = "C:\\Users\\Alexander.ALPROGPC\\Desktop\\tortuga_gears_export\\tortuga_gears_export\\tortuga_gears_done.fbx";
	//txtFile = "C:\\Users\\Alexander.ALPROGPC\\Desktop\\tortuga_gears_export\\tortuga_gears_export\\time.txt";

	Process(fbxFile, txtFile, true);

	PressEnterToContinue();
	return 0;
}