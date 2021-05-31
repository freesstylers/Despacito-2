#pragma once
#include "Persistence.h"
#include <iostream>
#include <fstream>
class FilePersistence : public Persistence
{
public:
	FilePersistence(string filePath);
	virtual void Send(Event* e);
	virtual void Flush();
	virtual void Open();
	virtual void Close();
private:
	ofstream file_;
	string filepath_;
};