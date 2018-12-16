#include "MapStr.h"

MapStr::MapStr()
{
}

MapStr::~MapStr()
{
}

void MapStr::Set(string key, string value)
{
	for(int i=0;i<_keyVec.size();i++)
	{
		//if((_keyVec[i])[0] == key[i])
		{
			if(_keyVec[i].compare(key) == 0)
			{
				_valueVec[i] = value;
				return;
			}
		}
	}

	_keyVec.push_back(key);
	_valueVec.push_back(value);
}

string MapStr::Get(string key)
{
	for(int i=0;i<_keyVec.size();i++)
	{
		//if(_keyVec[i][0] == key[i])
		{
			if(_keyVec[i].compare(key) == 0)
			{
				return _valueVec[i];
			}
		}
	}

	return "";
}
