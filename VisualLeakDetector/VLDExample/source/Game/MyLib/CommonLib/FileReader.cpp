#include "FileReader.h"
#include "Platform.h"

FileReader::FileReader()
{
	_pos = 0;
	_fileData = "";
}

bool FileReader::LoadFileFromAssets(const char* filePath)
{
	int fileSize = 0;
	char* data = Platform::GetPlatform()->GetFileData(filePath, &fileSize, Platform::READ_FROM_ASSETS);

	if(data)
	{
		_fileData = std::string(data);
		free(data);

		_fileData.clear();
		_pos = 0;

		return true;
	}

	return false;
}

bool FileReader::LoadFileFromSaveFolder(string path)
{
	string filePath = Platform::GetPlatform()->GetSaveFolderPath()+"/";
	filePath.append(path);

	FILE* fp = fopen(filePath.c_str(), "rb");
	
	bool readSuccess = false;

	if(fp)
	{
		fseek(fp, 0, SEEK_END);
		unsigned int fileSize = (unsigned int)ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char* _arrData = (char*)malloc(fileSize+1);
		memset(_arrData, '\0', fileSize+1);

		_fileData.clear();
		_pos = 0;
	
		if(fread(_arrData, 1, fileSize, fp) == fileSize)
		{
			_fileData = string(_arrData);
			readSuccess = true;
		}
		else
		{
			_fileData.clear();
			readSuccess = false;
		}

		free(_arrData);
		_arrData = NULL;

		if(fp)
			fclose(fp);
	}

	return readSuccess;
}


void FileReader::Reset()
{
	_pos = 0;
}

int FileReader::Read()
{
	if(_pos < (int)_fileData.length())
	{
		int charValue = (int)_fileData[_pos];
		_pos++;
		return charValue;
	}

	return -1;
}

string FileReader::ReadLine()
{
	if(_pos < (int)_fileData.length())
	{
		string line="";

		int i = _pos;

		for(; i<(int)_fileData.length(); i++)
		{
			if(_fileData[i] == '\n')
			{
				int temp = _pos;
				_pos = i+1;
				return _fileData.substr(temp, i-temp);
			}
		}

		int temp = _pos;
		_pos = i+1;
		return _fileData.substr(temp, i-temp);

	}
	return "null";
}

string FileReader::ReadLineAndTrim()
{
	return (Trim(ReadLine()));
}


vector<string> FileReader::ReadLine(char ch)
{
	vector<string> vec;

	string line = ReadLine();
	
	int arrCount = -1;
	bool enteredNow = false;

	for(int i=0;i<(int)line.length();i++)
	{
		char strChar = line[i];

		if(strChar != ch) 
		{
			if(enteredNow == false)			
			{
				enteredNow = true;
				arrCount++;
				string word;
				vec.push_back(word);
			}

			vec[arrCount] += strChar;
		}
		else { enteredNow = false; }

	}

	return vec;
}

string FileReader::GetAttribute(string attribute, string line)
{
	int index = -1;
	int count = 0;
	do
	{
		if(count > 4) { return ""; }
		if(count == 0) attribute.append("=");
		else if(count == 1) attribute.append(" =");
		else if(count == 2) attribute.append("  =");
		else if(count == 3) attribute.append("   =");
		else if(count == 4) attribute.append("    =");

		index =(int) line.find(attribute);
		count++;

	}while(index == -1);

	int start = -1;
	int end = -1;

	char ch = '\"';

	for(unsigned int i=index;i<line.length();i++)
	{
		if(line[i] == ch)
		{
			if(start == -1)
			{
				start = i;
			}
			else
			{
				end = i;
				break;
			}
		}
	}

	start++;
	string returnStr = line.substr(start, end-start);
	return returnStr;
}

int FileReader::GetTagIntData(string tag)
{
	vector<string> strVec = GetTagData(tag, true);

	if(strVec.size() != 1)
	{
		int a=1,b=0,c;
		c = a/b;
	}

	return atoi(strVec[0].c_str());
}

float FileReader::GetTagFloatData(string tag)
{
	vector<string> strVec = GetTagData(tag, true);

	if(strVec.size() != 1)
	{
		int a=1,b=0,c;
		c = a/b;
	}

	return atof(strVec[0].c_str());
}

string FileReader::GetTagStringData(string tag)
{
	vector<string> strVec = GetTagData(tag, true);
	if(strVec.size() != 1)
	{
		int a=1,b=0,c;
		c = a/b;
	}
	return strVec[0];
}


vector<string> FileReader::GetTagData(string tag, bool trim)
{
	vector<string> vec;
	Reset();
	
	string beginTag = "<";
	beginTag += Trim(tag);
	beginTag += ">";

	string endTag = "</";
	endTag += Trim(tag);
	endTag += ">";

	if(GoTo(beginTag) == false)
	{
		return vec;
	}

	string line="";

	do
	{
		if(trim) { line = ReadLineAndTrim(); } else { line = ReadLine(); }

		if(line.find(endTag) != -1)
			return vec;

		vec.push_back(line);

	}while( line.compare("null") != 0 );

	vec.clear();

	return vec;
}


bool FileReader::GoTo(string tag)
{
	Reset();
	string line;

	do
	{
		line = Trim(ReadLine()) ;

		if( line.find(tag) != -1)
			return true;
	}while(line.compare("null") != 0);

	return false;
}


string FileReader::Trim(string line)
{
	string retStr="";

	int start = 0;
	int end = 0;

	for(int i=0; i<(int)line.length(); i++) { if( line[i] != ' ')  {	start = i; break; } }

	for(int j= line.length()-1; j>=0; j--) { if( line[j] != ' ')  {	end = j; break; } }

	for(int k=start; k<=end; k++)
	{
		retStr += line[k];
	}
	return retStr;
}


vector<string> FileReader::Split(string line, char ch)
{
	vector<string> vec;
	
	int arrCount = -1;
	bool enteredNow = false;

	for(int i=0;i<(int)line.length();i++)
	{
		char strChar = line[i];

		if(strChar != ch) 
		{
			if(enteredNow == false)			
			{
				enteredNow = true;
				arrCount++;
				string word;
				vec.push_back(word);
			}
			vec[arrCount] += strChar;
		}
		else { enteredNow = false; }
	}

	return vec;
}

void FileReader::Close()
{
	_fileData = "";
	_fileData.clear();
	_pos = 0;
}

FileReader::~FileReader()
{
}