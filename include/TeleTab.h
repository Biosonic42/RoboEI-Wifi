
#ifndef _game_TeleTab_h
#define _game_TeleTab_h

#include "Controller.h"

#include "model.h"

#include "tab.h"
#include "checkbox.h"
#include "NumberSprite.h"

class TeleTabController : public Controller {

public:
	
	TeleTabController(Controller* superController);
	
	~TeleTabController();
	
	void handleKey();
	
	void loadData(const TeleData& TeleInfo);
	
	void saveData(TeleData* TeleInfo);
	
	void set_Disabled(CheckBox* cb);
	
	void set_LowerBridge(CheckBox* cb);
	
	void set_TravelBar(CheckBox* cb);
	
	void set_BallsPU(NumberSprite* ns);
	
	void set_TScore(NumberSprite* ns);
	
	void set_MScore(NumberSprite* ns);
	
	void set_LScore(NumberSprite* ns);
	
private:

	Controller* mSuperController;
	
	CheckBox* Disabled;
	CheckBox* LowerBridge;
	CheckBox* TravelBar;
	
	NumberSprite* BallsPU;
	NumberSprite* TScore;
	NumberSprite* MScore;
	NumberSprite* LScore;
};

Tab* InitTeleTab(Controller* superController);

#endif