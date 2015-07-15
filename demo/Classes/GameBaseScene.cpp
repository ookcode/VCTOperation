//
//  GameBaseScene.cpp
//  demo
//
//  Created by Vincent on 15/7/15.
//
//

#include "GameBaseScene.h"
#include "VCTChannel.h"
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
    return true;
}