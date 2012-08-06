
#include <PA9.h>
#include "all_gfx.h"

#include "raguna.h"

#include "BrdgTab.h"
#include "model.h"

#include "Controller.h"
#include "RadioButton.h"

BridgeTabController::BridgeTabController(Controller* superController)
: Controller(superController)
{
	mSuperController = superController;
}

BridgeTabController::~BridgeTabController()
{
}

void BridgeTabController::handleKey()
{
	if(BalanceType->get_CurRB() == 4)
	{
		BalanceAmount->disable();
	}
	
	if (mSuperController)
		mSuperController->handleKey();
}

void BridgeTabController::loadData(const BrdgData& BrdgInfo)
{
	BalanceType->set_CurRB(BrdgInfo.BalanceType);
	BalanceAmount->set_CurRB(BrdgInfo.BalanceAmount);
	
	// if new match
	// set all radiobuttons to false (disable)
}

void BridgeTabController::saveData(BrdgData* BrdgInfo)
{
	BrdgInfo->BalanceType = BalanceType->get_CurRB();
	BrdgInfo->BalanceAmount = BalanceAmount->get_CurRB();
}

void BridgeTabController::set_BalanceType(RBGroup* rbg)
{
	BalanceType = rbg;
}

void BridgeTabController::set_BalanceAmount(RBGroup* rbg)
{
	BalanceAmount = rbg;
}

Tab* InitBrdgTab(Controller* superController)
{
	BridgeTabController BTController(superController);
	
	Tab BrdgTab(kBottomScreen, 128, 0, BridgeTab_Sprite, &BGBridge, &BTController);
	
		RBGroup BalanceType;
		
			RadioButton Balance(kBottomScreen, 31, 36, Balanc_Sprite);
			RadioButton BalanCO(kBottomScreen, 31, 65, BalanCO_Sprite);
			RadioButton AttBal(kBottomScreen, 31, 96, AttBal_Sprite);
			RadioButton AttBalCO(kBottomScreen, 31, 125, AttBalCO_Sprite);
			RadioButton None(kBottomScreen, 31, 156, none_Sprite);
		
		BalanceType.add(&Balance);
		BalanceType.add(&BalanCO);
		BalanceType.add(&AttBal);
		BalanceType.add(&AttBalCO);
		BalanceType.add(&None);
		
		BrdgTab.add(&BalanceType);
			BTController.set_BalanceType(&BalanceType);
		
		RBGroup BalanceAmount;
		
			RadioButton OneBot(kBottomScreen, 153, 68, One_Sprite);
			RadioButton TwoBot(kBottomScreen, 153, 100, Two_Sprite);
			RadioButton ThreeBot(kBottomScreen, 153, 132, Three_Sprite);
		
		BalanceAmount.add(&OneBot);
		BalanceAmount.add(&TwoBot);
		BalanceAmount.add(&ThreeBot);
		
		BrdgTab.add(&BalanceAmount);
			BTController.set_BalanceAmount(&BalanceAmount);
		
	return &BrdgTab;
}