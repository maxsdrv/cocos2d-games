#include "LearnSpriteSheets.h"

USING_NS_CC;

cocos2d::Scene *LearnSpriteSheets::createScene()
{
    auto scene = Scene::create();
    auto layer = LearnSpriteSheets::create();
    scene->addChild(layer);

    return scene;
}
cocos2d::Vector<cocos2d::SpriteFrame *> LearnSpriteSheets::getAnimation(const char *format, int count)
{
    return cocos2d::Vector<cocos2d::SpriteFrame *>();
}
bool LearnSpriteSheets::init()
{
    if (!Layer::init())
    {
        return false;
    }

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("scene1.plist");

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 visible_size = Director::getInstance()->getVisibleSize();

    //background
    auto background = Sprite::createWithSpriteFrameName("Cartoon_Forest_BG_02.png");
    background->setPosition(origin.x + visible_size.x / 2, origin.y + visible_size.y / 2);
    this->addChild(background);

    return true;
}
