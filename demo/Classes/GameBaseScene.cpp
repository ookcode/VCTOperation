//
//  GameBaseScene.cpp
//  demo
//
//  Created by Vincent on 15/7/15.
//
//

#include "GameBaseScene.h"
#include "VCTChannel.h"

#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

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
    
    Size winSize = Director::getInstance()->getWinSize();
    {
        Text* text = Text::create("show alert", "Marker Felt.ttf", 28);
        text->setTouchEnabled(true);
        text->setPosition(Size(winSize.width / 2,winSize.height / 2 - 100));
        text->addTouchEventListener(CC_CALLBACK_2(GameBaseScene::showAlert, this));
        this->addChild(text);
    }
    
    {
        Text* text = Text::create("run js scene", "Marker Felt.ttf", 28);
        text->setTouchEnabled(true);
        text->setPosition(Size(winSize.width / 2,winSize.height / 2 + 100));
        text->addTouchEventListener(CC_CALLBACK_2(GameBaseScene::turnJsScene, this));
        this->addChild(text);
    }
    
    VCT::Channel::Request("handlemodule", "register", "tocppscene",[](const std::string& args)
    {
        Director::getInstance()->replaceScene(GameBaseScene::createScene());
    });
    return true;
}

void GameBaseScene::showAlert(Ref*, Widget::TouchEventType type)
{
    if (Widget::TouchEventType::ENDED != type) return ;
    rapidjson::Document doc;
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    rapidjson::Value object(rapidjson::kObjectType);
    object.AddMember("title", "Welcome", allocator);
    object.AddMember("message", "this is a cpp scene", allocator);
    object.AddMember("leftbtn", "Ok", allocator);
    object.AddMember("rightbtn", "Cancel", allocator);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> write(buffer);
    object.Accept(write);
    std::string jsonstr = buffer.GetString();
    
    VCT::Channel::Request("alertmodule", "show", jsonstr,[](const std::string& args)
    {
        log("you click : %s",args.c_str());
    });
}

void GameBaseScene::turnJsScene(Ref*, Widget::TouchEventType type)
{
    if (Widget::TouchEventType::ENDED != type) return ;
    VCT::Channel::Request("handlemodule", "trigger","tojsscene");
}