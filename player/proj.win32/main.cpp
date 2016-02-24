#include "main.h"
#include "AppDelegate.h"

USING_NS_CC;

std::vector<std::string> GetArgs(LPTSTR lpCmdLine)
{
	std::vector<std::string> args;

	int len = _tcslen(lpCmdLine);
	char* argv = new char[len + 1];
	wcstombs(argv, lpCmdLine, len);
	argv[len] = 0;
	
	for (int i = len - 1; i >= 0; i--)
	{
		if (argv[i] == ' ')
		{
			argv[i] = '\0';
			args.push_back(&argv[i + 1]);
		}
	}
	args.push_back(&argv[0]);
	delete argv;
	return args;
}
 
int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
	 
	AppDelegate application;
	application.args = GetArgs(lpCmdLine);

	for (auto& arg : application.args)
	{
		if (arg == "-console")
		{
			AllocConsole();
			freopen("CONIN$", "r", stdin);
			freopen("CONOUT$", "w", stdout);
			freopen("CONOUT$", "w", stderr);
		}
	}

    return application.run();
}
