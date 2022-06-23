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
    auto sprite_cache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> anim_frames;
    char str[100];
    for (int i = 0; i <= count; ++i)
    {
        sprintf(str, format, i);
        anim_frames.pushBack(sprite_cache->getSpriteFrameByName(str));
    }
    return anim_frames;
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

    //sprite
    auto frames = getAnimation("sprite-sheet-test/tile%03d.png", 3);
    auto sprite = Sprite::createWithSpriteFrame(frames.front());
    background->addChild(sprite);
    sprite->setPosition(100, 120);

    auto animation = Animation::createWithSpriteFrames(frames, 1.0f/4);
    sprite->runAction(RepeatForever::create(Animate::create(animation)));

    //move to
    auto movement = MoveTo::create(10, Vec2(1500, 100));
    auto resetPosition = MoveTo::create(0, Vec2(-150, 120));
    auto sequence = Sequence::create(movement, resetPosition, nullptr);
    sprite->runAction(RepeatForever::create(sequence));

    return true;
}
