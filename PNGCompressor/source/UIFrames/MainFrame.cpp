#include "MainFrame.h"
#include "SUI/SUIButton.h"
#include "SUI/SUIBox.h"
#include "DefinesAndIncludes.h"
#include "Util/UtilFuncs.h"
#include "Util/StringUtils.h"
#include "ImageBuffer.h"

MainFrame::MainFrame(int x, int y, int w, int h)
{
	_frame = new SUIFrame((float)x, (float)y, (float)w, (float)h, SUIFrame::V_ALIGNMENT);

	_browseSingle = new SUIButton("Browse", this);
	_browseMulti = new SUIButton("Browse PNG images", this);
	_browseFolder = new SUIButton("Browse", this);

	_level1 = new SUICheckBox("1", SUICheckBox::LEFT);
	_level2 = new SUICheckBox("2", SUICheckBox::LEFT);

	_level1->SetSelect(true);

	SUIBox* levelBox = new SUIBox(SUIBox::V_ALIGNMENT);
	levelBox->SetMargin(2,2,3,0);
	levelBox->SetName("Compression Level", SUIBox::LEFT);
	levelBox->AddCheckBox(_level1);
	levelBox->AddCheckBox(_level2);
	levelBox->SetOnOffEnable(true);

	//_frame->Add(_browseSingle);
	_frame->Add(_browseMulti);
	//_frame->Add(_browseFolder);

	_frame->Add(levelBox);
	_frame->SetRemoveCloseOption(true);
}

void MainFrame::actionPerformed(SUIActionEvent e)
{
	SUIComponent* com = (SUIComponent*)e.GetComponent();
	string name = com->GetName();

	if(com == _browseSingle)
	{
		vector<string> vecPaths = UtilFuncs::OpenFileDialog(".png\0*.png\0", false);

		if(vecPaths.size() > 0 && vecPaths[0].length() > 0)
		{	
			ImageBuffer* imgBuffer = new ImageBuffer(vecPaths[0]);
			imgBuffer->MakeFeasibleToCompress(1);

			string savePath = StringUtils::insertAt(vecPaths[0].length() - 4, vecPaths[0], "_compressed");
			imgBuffer->Write(savePath);
			delete imgBuffer;
		}
	}
	else if(com == _browseMulti)
	{
		vector<string> vecPaths = UtilFuncs::OpenFileDialog(".png\0*.png\0", true);

		bool level1Compression = _level1->IsSelected();
		bool level2Compression = _level2->IsSelected();

		for(int i=0; i<vecPaths.size(); i++)
		{
			if( vecPaths[i].length() > 0)
			{
				if(level1Compression)
				{
					ImageBuffer* imgBuffer = new ImageBuffer(vecPaths[i]);
					imgBuffer->MakeFeasibleToCompress(1);
					string savePath = StringUtils::insertAt(vecPaths[i].length() - 4, vecPaths[i], "_compressionLevel_1");
					imgBuffer->Write(savePath);
					delete imgBuffer;
				}
				
				if(level2Compression)
				{
					ImageBuffer* imgBuffer = new ImageBuffer(vecPaths[i]);
					imgBuffer->MakeFeasibleToCompress(2);
					string savePath = StringUtils::insertAt(vecPaths[i].length() - 4, vecPaths[i], "_compressionLevel_2");
					imgBuffer->Write(savePath);
					delete imgBuffer;
				}
			}
		}
	}
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
