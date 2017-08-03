#include "UtilFuncs.h"
#include "Sui/Sui.h"
#include "math.h"
#include "stdlib.h"
#include "memory.h"

int UtilFuncs::floatToIntBits( float val )
{
	int* intVal = (int*)&val;
	return intVal[0];
}

float* UtilFuncs::AddFloat(float* arr, int arrSize, float addVal)
{
	float* newArr = (float*)malloc((arrSize+1) * sizeof(float));
	memcpy(newArr, arr, arrSize);
	newArr[arrSize] = addVal;
	free(arr);
	return newArr;
}

float UtilFuncs::nearVal(float x)
{
	float dx = x - (int)x;
	
	if(x > 0)
	{
		if(dx > 0.5f)	return (int)x + 1;
		else			return (int)x;
	}
	else
	{
		if(dx < -0.5f)	return (int)x - 1;
		else			return (int)x;
	}

	return x;
}

double UtilFuncs::Exp(double xVal, int nVal, double factor)
{
	xVal *= factor;

	double sum = 0;

	for(int i=0;i<=nVal;i++)
	{
		double up = pow((double)xVal, (int)i);
		double down = factorial(i);
		sum += up/down;
	}

	return sum;
}

double UtilFuncs::factorial(int n)
{
	double sum = 1;
	for(int i=1;i<=n;i++)
		sum *= i;
	return sum;
}

vector<string> UtilFuncs::OpenFileDialog(char *filter, bool allowMultiSel) 
{
	vector<string> filePaths;

	HWND owner = NULL;
	OPENFILENAME ofn;
	#define _MAX_PATH 30000
	char path[_MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	 
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = path;
	ofn.nMaxFile = _MAX_PATH;
	
	if(allowMultiSel)
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR | OFN_ALLOWMULTISELECT;
	else
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;

	ofn.lpstrDefExt = "";

	string folderPath;

	if(GetOpenFileName(&ofn))
		folderPath = path;

    char buf[_MAX_PATH + 1];
    char *p = path + strlen(path) + 1;

	do
    {
      strcpy(buf, path);
      if (*p)   // The case of multiple file selection
      {
        strcat(buf, "\\");
        strcat(buf, p);
	  }

	  string filePath(folderPath);
	  filePath.append("\\");
	  filePath.append(p);
	  filePaths.push_back(filePath);

      // go to next file name
      if (*p)
        p = p + strlen(p) + 1;

    }  while (*p);

	for(int i=0;i<filePaths.size();i++)
	{
		string str = filePaths[i];
		if(str[str.length()-1] == '\\')
		{
			str = str.substr(0, str.length()-1);
			filePaths[i] = str;
		}
	}

	return filePaths;
}

string UtilFuncs::SaveFileDialog(char *filter) 
{
	HWND owner = NULL;

	OPENFILENAME ofn;
	#define _MAX_PATH 30000
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	 
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";

	string fileNameStr;

	if(GetSaveFileNameA(&ofn))
		fileNameStr = fileName;

	return fileNameStr;
}

//string UtilFuncs::OpenFolderDialer()
//{
//	BROWSEINFO bi = { 0 };
//    bi.lpszTitle = _T("Pick a Directory");
//    LPITEMIDLIST pidl = SHBrowseForFolder ( &bi );
//    if ( pidl != 0 )
//    {
//        // get the name of the folder
//        TCHAR path[MAX_PATH];
//        if ( SHGetPathFromIDList ( pidl, path ) )
//        {
//            _tprintf ( _T("Selected Folder: %s\n"), path );
//        }
//
//        // free memory used
//        IMalloc * imalloc = 0;
//        if ( SUCCEEDED( SHGetMalloc ( &imalloc )) )
//        {
//            imalloc->Free ( pidl );
//            imalloc->Release ( );
//        }
//
//		return string(path);
//    }
//
//	return string();
//}
