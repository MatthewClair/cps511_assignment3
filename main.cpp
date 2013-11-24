#include <cstdlib>

#include "global.h"

void initDisplay(int *argc, const char *argv[]);

int main(int argc, const char *argv[])
{
	initDisplay(&argc, argv);
	
	return 0;
}

void initDisplay(int *argc, const char *argv[])
{
	for (int i = 0; i < *argc; i++)
	{
		if (argv[i][0] == '-')
		{
			switch (argv[i][1])
			{
				case 'w':
					switch (argv[i][2])
					{
						case '\0':
							window_width = std::atoi(argv[i+1]);
							i++;
							break;
						case '=':
							window_width = std::atoi(&argv[i][3]);
							break;
						case '0':
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
						case '9':
							window_width = std::atoi(&argv[i][2]);
							break;
					}
					break;
				case 'h':
					switch (argv[i][2])
					{
						case '\0':
							window_height = std::atoi(argv[i+1]);
							i++;
							break;
						case '=':
							window_height = std::atoi(&argv[i][3]);
							break;
						case '0':
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
						case '9':
							window_height = std::atoi(&argv[i][2]);
							break;
					}
					break;
			}
		}
	}
}
