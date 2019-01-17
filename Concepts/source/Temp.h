#ifndef Temp_H
#define Temp_H

class Temp
{
private:
	int a;
	int b;
	int c;

public:
	Temp();
	Temp(int param1, int param2);
	//Temp(const Temp& temp);


	~Temp();
	
	void tempFunc();
};

#endif