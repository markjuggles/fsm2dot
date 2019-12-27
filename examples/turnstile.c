#include <stdio.h>

typedef enum state { Locked, Unlocked } State;

int main(void)
{
	State	appState;
	
	appState = Locked;
	readInputs();
	
	while(1)
	{
		processInputs();							// block until inputs change
		
		switch(appState)
		{
			case Locked:
				if(senseCoin())
				{
					appState = Unlocked;			// gv: coin
				}
				
				if(sensePush())
				{
					appState = Locked;				// gv: push
				}
				break:
				
			case Unlocked:
				if(senseCoin())
				{
					appState = Unlocked;			// gv: coin
				}
				
				if(sensePush())
				{
					appState = Locked;				// gv: push
				}
				break:
		}
	}
	
	return 0;
}