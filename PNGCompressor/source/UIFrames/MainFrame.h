#ifndef MainFrame_H
#define MainFrame_H

#include "SUI/SUIFrame.h"
#include "SUI/SUIActionListener.h"
#include "SUI/SUIRadioButton.h"
#include "SUI/SUICheckBox.h"
#include "SUI/SUIButton.h"
#include "SUI/SUILabel.h"
#include "SUI/SUIChoice.h"
#include "SUI/SUITextField.h"
#include "SUI/SUIBox.h"

class MainFrame : public SUIActionListener
{
private:
	SUIFrame* _frame;
	
	SUIRadioButton* projRadio;
	SUIRadioButton* pivot;

	SUICheckBox* floorVisible;
	SUICheckBox* showAxis;
	SUICheckBox* showGrid;
	SUICheckBox* showGridLines;

	SUICheckBox* enablePhysics;
	SUICheckBox* pausePhysics;
	SUICheckBox* showMarkedObjs;
	SUICheckBox* showUnmarkedObjs;
	SUIButton* markAllObjs;
	SUIButton* unmarkAllObjs;
	SUICheckBox* showBoundShapes;
	SUICheckBox* showBoundBox;
	SUICheckBox* onBorder;
	SUIButton* changeViewBtn;

public:
	MainFrame(int x, int y, int w, int h);
	~MainFrame();

	void actionPerformed(SUIActionEvent e);
	void SetMaximize(bool maximize);
};

#endif
