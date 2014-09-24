#ifndef __GAMEMAIN_SCENE_H__
#define __GAMEMAIN_SCENE_H__

#include "cocos2d.h"
#include "ui\UIWidget.h"
#include "editor-support\cocostudio\CCSGUIReader.h"
#include "ui\UIHelper.h"
#include "editor-support\cocostudio\CCArmatureDataManager.h"
#include "editor-support\cocostudio\CCArmature.h"
#include "ui\UILoadingBar.h"
#include "ui\UITextAtlas.h"
#include "ui\UIButton.h"
#include "Particles.h"
#include "resource.h"
#include "PopupLayer.h"
using namespace cocos2d::ui;
class GameMain : public cocos2d::Layer
{
public:
	GameMain();
	static cocos2d::Scene* createScene();
    virtual bool init();  
    

    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuPauseCallback(cocos2d::Ref* pSender);
	//touch button event
	void touchButton(cocos2d::Object* ,cocos2d::ui::TouchEventType);

	//up and down functions
	void upforce();
	void downforce();

	//next task and game over
	void newtask();
	void gameover();

	//void jniupforce();
	//void jnidownforce();

    //add central
	void addcentral();
	//update central and excute update around
	void update(float time);
	void autoremove();
    CREATE_FUNC(GameMain);

	static GameMain* fundlayer;
	Particles* particles;
	//state ,25,50,75
	static int state;
	//game_status
	static int GAME_STATUS;
	//gravity + - 0.1
	static float gravity;
	//score
	static int score;

	int life;
	//page 1-9
	static int page;
	//central kind 1-3
	static int centralkind;
};

#endif // __HELLOWORLD_SCENE_H__
