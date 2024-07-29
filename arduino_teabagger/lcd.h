#define rs 7
#define en 6
#define d4 5
#define d5 4
#define d6 3
#define d7 2

void setupLCD();
void printLCDText();
void printTime(long min, long sec);
void printTemp(int t);
void flashTextOn(char text[], int locationX, int locationY, int time);
void flashTextOff(char text[], int locationX, int locationY);
void clearDisplay();
void printTeaBaggerTxt();
void printWelcomeTxt();