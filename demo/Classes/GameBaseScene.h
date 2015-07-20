//
//  GameBaseScene.h
//  demo
//
//  Created by Vincent on 15/7/15.
//
//

#ifndef __demo__GameBaseScene__
#define __demo__GameBaseScene__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
class GameBaseScene : public Layer
{
public:
    static Scene* createScene();
    
private:
    bool init() override;
    void showAlert(Ref*, Widget::TouchEventType);
    void turnJsScene(Ref*, Widget::TouchEventType);
    CREATE_FUNC(GameBaseScene);
};

#endif /* defined(__demo__GameBaseScene__) */
