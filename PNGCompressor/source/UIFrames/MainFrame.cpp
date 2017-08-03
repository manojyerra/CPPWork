#include "MainFrame.h"
#include "SUI/SUIButton.h"
#include "SUI/SUIBox.h"
#include "DefinesAndIncludes.h"

MainFrame::MainFrame(int x, int y, int w, int h)
{
	_frame = new SUIFrame((float)x, (float)y, (float)w, (float)h, SUIFrame::V_ALIGNMENT);
	_frame->SetName("Main Frame", SUIFrame::LEFT);

	_frame->Add(new SUIButton("Load Models", this));
	_frame->Add(new SUIButton("Save Models", this));

	_frame->Add( enablePhysics = new SUICheckBox("Enable Physics (P)", SUICheckBox::LEFT, this));
	_frame->Add( pausePhysics = new SUICheckBox("Pause Physics (Space)", SUICheckBox::LEFT, this));
	
	enablePhysics->SetShortCut(SUIKeyCombi('P'));
	pausePhysics->SetShortCut(SUIKeyCombi(VK_SPACE));

	_frame->Add( showMarkedObjs = new SUICheckBox("Show Marked Objects", SUICheckBox::LEFT, this));
	_frame->Add( showUnmarkedObjs = new SUICheckBox("Show Unmarked Objects", SUICheckBox::LEFT, this));
	_frame->Add( markAllObjs = new SUIButton("Mark all objects", SUIButton::LEFT, this));
	_frame->Add( unmarkAllObjs = new SUIButton("Unmark all objects", SUIButton::LEFT, this));

	_frame->Add( showBoundShapes = new SUICheckBox("Show Bounding Shapes (B)", SUICheckBox::LEFT, this) );
	_frame->Add( showBoundBox = new SUICheckBox("Show Bounding Box", SUICheckBox::LEFT, this) );
	_frame->Add( onBorder = new SUICheckBox("Selected Object Border", SUICheckBox::LEFT, this) );
}

void MainFrame::actionPerformed(SUIActionEvent e)
{
	SUIComponent* com = (SUIComponent*)e.GetComponent();
	string name = com->GetName();
}

void MainFrame::SetMaximize(bool maximize)
{
	_frame->SetMaximized(maximize);
}

MainFrame::~MainFrame()
{
	if(_frame)
	{
		delete _frame;
		_frame = NULL;
	}
}
