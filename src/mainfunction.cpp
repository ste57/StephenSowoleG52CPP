#include "header.h"

#include "templates.h"

// Needs one of the following #includes, to include the class definition
#include "MyProjectMain.h"
#include "MainGameFile.h"

#define BASE_SCREEN_WIDTH 800
#define BASE_SCREEN_HEIGHT 600



int main(int argc, char *argv[])
{
	int iResult;

	// Needs just one of the two following lines:
	//BouncingBallMain oMain;
	//MyProjectMain oMain;
	//Demo2Main oMain;
	//Demo2aMain oMain;
	//Demo3Main oMain;

	MainGameFile oMain;

	char buf[1024];
	sprintf( buf, "My Demonstration Program : Size %d x %d", BASE_SCREEN_WIDTH, BASE_SCREEN_HEIGHT );
	iResult = oMain.Initialise( buf, BASE_SCREEN_WIDTH, BASE_SCREEN_HEIGHT, "Cornerstone Regular.ttf", 24 );
	iResult = oMain.MainLoop();
	oMain.Deinitialise();

	return iResult;
}
