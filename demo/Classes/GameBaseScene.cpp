//
//  GameBaseScene.cpp
//  demo
//
//  Created by Vincent on 15/7/15.
//
//

#include "GameBaseScene.h"
#include "VCTChannel.h"
#include "ScriptingCore.h"
#include "ui/CocosGUI.h"
using namespace ui;

Scene* GameBaseScene::createScene()
{
    auto scene = Scene::create();
    scene->addChild(GameBaseScene::create());
    return scene;
}

bool GameBaseScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    VCT::Channel::Request("testModule", "testMethod", "testArgs",[](const std::string& args)
    {
        log("response : %s",args.c_str());
    });
    Size winSize = Director::getInstance()->getWinSize();
    Text* text = Text::create("touch to run js scene", "", 36);
    text->setTouchEnabled(true);
    text->setPosition(winSize / 2);
    text->addTouchEventListener([](Ref *,Widget::TouchEventType type)
    {
        if (Widget::TouchEventType::ENDED != type) return ;
        ScriptEngineProtocol *engine = ScriptingCore::getInstance();
        ScriptEngineManager::getInstance()->setScriptEngine(engine);
        ScriptingCore::getInstance()->runScript("main.js");
    });
    this->addChild(text);
    return true;
}