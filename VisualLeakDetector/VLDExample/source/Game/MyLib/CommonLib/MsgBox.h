#ifndef MSGBOX_H
#define MSGBOX_H

#include "ButtonNew.h"
#include <vector>
#include <string>
using namespace std;

class MsgBox
{
private:
	ButtonNew* _bg;
	vector<ButtonNew*> _btnVec;
	bool _isActive;
	int _btnW;
	int _btnH;
	string _msg;

	int _buttonIndex;
	bool _inActiveOnBackPress;

public:
	MsgBox(string msg);
	~MsgBox();

	void SetMsg(string msg);
	void SetBgSize(int w, int h);
	void SetBtnSize(int w, int h);

	void SetActive(bool isActive);
	bool IsActive();

	void Update();
	void Draw();

	int GetButtonIndex_OnClick();
	void SetInActiveOnBackPress(bool inActive);
	void AddButton(string text);
};

#endif