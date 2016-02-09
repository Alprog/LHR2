
#include "manager.h"

Manager::Manager()
{
	manager = FbxManager::Create();
	FbxIOSettings* settings = FbxIOSettings::Create(manager, IOSROOT);
	manager->SetIOSettings(settings);
}

FbxScene* Manager::Import(const char* fileName)
{
	FbxScene* scene = FbxScene::Create(manager, "myScene");
	FbxImporter* importer = FbxImporter::Create(manager, "");
	bool result = importer->Initialize(fileName, -1, manager->GetIOSettings());
	if (!result)
	{
		printf("Error returned: %s\n\n", importer->GetStatus().GetErrorString()); 
	}
	importer->Import(scene);
	importer->Destroy();
	return scene;
}

void Manager::Export(FbxScene* scene, const char* fileName, bool textFormat)
{
	FbxExporter* exporter = FbxExporter::Create(manager, "");

	auto fileFormat = 0;
	if (textFormat)
	{ 
		fileFormat = manager->GetIOPluginRegistry()->GetNativeWriterFormat();
		int lFormatIndex, lFormatCount = manager->GetIOPluginRegistry()->GetWriterFormatCount();
		for (lFormatIndex = 0; lFormatIndex<lFormatCount; lFormatIndex++)
		{
			if (manager->GetIOPluginRegistry()->WriterIsFBX(lFormatIndex))
			{
				FbxString lDesc = manager->GetIOPluginRegistry()->GetWriterFormatDescription(lFormatIndex);
				const char *lASCII = "ascii";
				if (lDesc.Find(lASCII) >= 0)
				{
					fileFormat = lFormatIndex;
					break;
				}
			}
		}
	}

	exporter->Initialize(fileName, fileFormat, manager->GetIOSettings());

	exporter->SetFileExportVersion(FBX_2014_00_COMPATIBLE);
	exporter->Export(scene);
	exporter->Destroy();
}
