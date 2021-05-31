#pragma once
#include"LevelEvent.h"
class LostLevelEvent: public LevelEvent
{
public:
	LostLevelEvent(string timeStamp);
	void setLastNote(int last_note);
	virtual string toJson();
	virtual string toXML();

private:
	int last_note_;
};

