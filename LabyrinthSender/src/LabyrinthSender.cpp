
#include "Sender.h"


int main()
{
	Sender s;
	s.callNewLab();
	s.callStart(10, 10);
	s.callEnd(90, 90);
	s.callWall(0, 0, 100, 0);
	s.callWall(0, 0, 0, 100);
	s.callWall(100, 100, 100, 0);
	s.callWall(100, 100, 0, 100);
	s.callWall(90, 10, 10, 90);
	s.callApply();
}
