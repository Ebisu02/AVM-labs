#include "../src_headers/myReadKey.h"

termios OldSettings;

int rk_readkey(KEYS & key)
{
	rk_mytermsave();
	rk_mytermregime(0, 0, 0, 0, 1);
	char b[8]{};
	read(fileno(stdin), b, 8);
	if(strcmp(b,"\E[A")==0) 		key=KEYS::Up;
	else if(strcmp(b,"\E[B")==0) 		key=KEYS::Down;
	else if(strcmp(b,"\E[C")==0) 		key=KEYS::Right;
	else if(strcmp(b,"\E[D")==0) 		key=KEYS::Left;
	else if(strcmp(b,"\E[15~")==0) 	key=KEYS::Accumulator;
	else if(strcmp(b,"\E[17~")==0) 	key=KEYS::InstructionCounter;
	else if(b[0]=='l') 			key=KEYS::Load;
	else if(b[0]=='s') 			key=KEYS::Save;
	else if(b[0]=='r') 			key=KEYS::Run;
	else if(b[0]=='t') 			key=KEYS::Step;
	else if(b[0]=='i')		 	key=KEYS::Reset;
	else if(b[0]=='\n')			key=KEYS::Enter;
	else if(b[0]=='q') 			key=KEYS::CloseApplication;
	else 					key=KEYS::None;
	rk_mytermrestore();
	return 0;
}

// tcgetattr() & tcsetattr() - 0 if success, -1 if error
int rk_mytermsave()
{
	return tcgetattr(fileno(stdin), &OldSettings);
}

int rk_mytermrestore()
{
	return tcsetattr(fileno(stdin), TCSANOW, &OldSettings);
}

int rk_mytermregime(int regime, int vtime, int vmin, bool echo, bool sigint)
{
	rk_mytermsave();
	termios NewSettings = OldSettings;
	if(regime == 1)
	{
		NewSettings.c_lflag |= ICANON;
	}
	else
	{
		NewSettings.c_lflag &= ~ICANON;
		echo ? NewSettings.c_lflag |= ECHO : NewSettings.c_lflag &= ~ECHO;
		sigint ? NewSettings.c_lflag |= ISIG : NewSettings.c_lflag &= ~ISIG;
		NewSettings.c_cc[VTIME] = vtime;
		NewSettings.c_cc[VMIN] = vmin;
	}
	return tcsetattr(fileno(stdin), TCSANOW, &NewSettings);
}
