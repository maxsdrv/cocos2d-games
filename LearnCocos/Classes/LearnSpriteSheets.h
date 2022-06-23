#ifndef LEARNSPRITESHEETS_H
#define LEARNSPRITESHEETS_H

#include "cocos2d.h"

class LearnSpriteSheets : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    bool init() override;
    CREATE_FUNC(LearnSpriteSheets);

private:
    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char *format, int count);
};


#endif //LEARNSPRITESHEETS_H
