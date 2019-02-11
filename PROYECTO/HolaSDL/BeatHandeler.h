#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
class BeatHandeler
{
protected:
	//int currentBeats ;
	int bmp;
	double beatTime;
public:
	BeatHandeler();
	BeatHandeler(int bmp) :bmp(bmp) {};
	~BeatHandeler();
	//Este es el m�todo que controla cuando y a que velocidad se va a lanzar cada bot�n
	void beatRateButton(int &currentBeats/*aqui deber�a de entrar la cola con los botones y los tiempos*/);
	//Metodo que combierte los bpm a el tiempo transcurrido entre beat y beat
	double translateBmp();
	//Devuelve el beattime
	double getBeatTime() { return beatTime; };

};

