#ifndef MAPSTR_H
#define MAPSTR_H

#include <vector>
#include <string>
using namespace std;

class MapStr
{
private:
	vector<string> _keyVec;
	vector<string> _valueVec;

public:
	MapStr();
	~MapStr();

	void Set(string key, string value);
	string Get(string key);
};

#endif