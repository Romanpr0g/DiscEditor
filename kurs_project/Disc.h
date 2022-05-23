#pragma once

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string.h>
#include "MyFunction.h" 

#define Wstr "\\\\.\\"
#define endStr ":"
#define PhysDrive "\\\\.\\PHYSICALDRIVE1"

using namespace std;

class Disc
{
private:

	char** DiscsA;
	char** DiscsW;
	int quntityDisks;
	void DiscW();

public:

	Disc();
	int Get_Quntity();
	char** Get_DiscsA();
	void Print_Info();
	char** Get_DiscsW();
	__int64 GetSize(char* path);
};



