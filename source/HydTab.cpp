
#include <PA9.h>
#include "all_gfx.h"

#include "raguna.h"

#include "HydTab.h"
#include "model.h"

#include "Controller.h"
#include "NumberSprite.h"
#include "checkbox.h"
#include "RadioButton.h"


HydTabController::HydTabController(Controller* superController)
: Controller(superController)
{
	mSuperController = superController;
}

HydTabController::~HydTabController()
{
}

void HydTabController::handleKey()
{
	
	if(Pad.Held.L && Pad.Newpress.X)
	{
		TScore->dec_mFrame();
		if(TScore->get_mFrame() < 0)
			TScore->set_mFrame(0);
	}
	else if(Pad.Newpress.X)
	{
		TScore->inc_mFrame();
	}
	
	if(Pad.Held.L && Pad.Newpress.A)
	{
		MScore->dec_mFrame();
		if(MScore->get_mFrame() < 0)
			MScore->set_mFrame(0);
	}
	else if(Pad.Newpress.A)
	{
		MScore->inc_mFrame();
	}
	
	if(Pad.Held.L && Pad.Newpress.B)
	{
		LScore->dec_mFrame();
		if(LScore->get_mFrame() < 0)
			LScore->set_mFrame(0);
	}
	else if(Pad.Newpress.B)
	{
		LScore->inc_mFrame();
	}
		
	if(HasHybrid->get_mFrame() == false)
	{
		ScoreType->disable();
		UsesKINECT->set_mFrame(false);
		TScore->set_mFrame(0);
		MScore->set_mFrame(0);
		LScore->set_mFrame(0);
	}
	
	if (mSuperController)
		mSuperController->handleKey();
}

void HydTabController::loadData(const HydData& HydInfo)
{
	HasHybrid->set_mFrame(HydInfo.HasHybrid);
	UsesKINECT->set_mFrame(HydInfo.UsesKINECT);
	ScoreType->set_CurRB(HydInfo.ScoreType);
	TScore->set_mFrame(HydInfo.TopP);
	MScore->set_mFrame(HydInfo.MidP);
	LScore->set_mFrame(HydInfo.LowP);
	
}

void HydTabController::saveData(HydData* HydInfo)
{
	HydInfo->HasHybrid = HasHybrid->get_mFrame();
	HydInfo->UsesKINECT = UsesKINECT->get_mFrame();
	HydInfo->ScoreType = ScoreType->get_CurRB();
	HydInfo->TopP = TScore->get_mFrame();
	HydInfo->MidP = MScore->get_mFrame();
	HydInfo->LowP = LScore->get_mFrame();
	
}
	

void HydTabController::set_HasHybrid(CheckBox* cb)
{
	HasHybrid = cb;
}

void HydTabController::set_UsesKINECT(CheckBox* cb)
{
	UsesKINECT = cb;
}

void HydTabController::set_ScoreType(RBGroup* rbg)
{
	ScoreType = rbg;
}

void HydTabController::set_TScore(NumberSprite* ns)
{
	TScore = ns;
}

void HydTabController::set_MScore(NumberSprite* ns)
{
	MScore = ns;
}

void HydTabController::set_LScore(NumberSprite* ns)
{
	LScore = ns;
}

Tab* InitHydTab(Controller* superController)
{
	HydTabController HTController(superController);
	
	Tab HydTab(kBottomScreen, 0, 0, HybridTab_Sprite, &BGHybrid, &HTController);
	
		// checkboxes (Hybrid Type)
		CheckBox HasHybrid(kBottomScreen, 88, 40, HasHybrid_Sprite);
		
			HydTab.add(&HasHybrid);
				HTController.set_HasHybrid(&HasHybrid);
		
		CheckBox UsesKINECT(kBottomScreen, 224, 40, UsesKINECT_Sprite);
		
			HydTab.add(&UsesKINECT);
				HTController.set_UsesKINECT(&UsesKINECT);
		
		// radiobuttons (Score Type)
		RBGroup ScoreType;
		
		RadioButton LowerBridge(kBottomScreen, 32, 64, LwrBrdg_Sprite);
		RadioButton HybridAssist(kBottomScreen, 96, 64, HybAssist_Sprite);
		RadioButton Other(kBottomScreen, 160, 64, Other_Sprite);
		
		ScoreType.add(&LowerBridge);
		ScoreType.add(&HybridAssist);
		ScoreType.add(&Other);
		
			HydTab.add(&ScoreType);
				HTController.set_ScoreType(&ScoreType);
		
		// number_sprites (Score Locations)
		NumberSprite TopScore(kBottomScreen, 140, 106, Top_Sprite);
		NumberSprite MidScore(kBottomScreen, 140, 128, Mid_Sprite);
		NumberSprite LowScore(kBottomScreen, 140, 150, Low_Sprite);
		
			HydTab.add(&TopScore);
				HTController.set_TScore(&TopScore);
			
			HydTab.add(&MidScore);
				HTController.set_MScore(&MidScore);
			
			HydTab.add(&LowScore);
				HTController.set_LScore(&LowScore);
	
	return &HydTab;
}