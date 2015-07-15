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
USING_NS_CC;

class GameBaseScene : public Layer
{
public:
    static Scene* createScene();
    
private:
    bool init() override;
    CREATE_FUNC(GameBaseScene);
};

#endif /* defined(__demo__GameBaseScene__) */
