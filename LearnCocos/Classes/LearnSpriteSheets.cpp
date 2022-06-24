#include <iostream>

#include "LearnSpriteSheets.h"

USING_NS_CC;

namespace Actions
{
struct SomeActions
{
    static JumpBy *jumpAction()
    {
        auto jump = JumpBy::create(0.5, Vec2(0, 0), 100, 1);

        return jump;
    }
    static RotateTo *rotateAction()
    {
        auto rotate = RotateTo::create(2.0f, 10);

        return rotate;
    }

};
}

static void problemLoading(const char* filename)
{
    std::cerr << "Error while loading: " << filename << '\n';
    std::cerr << "Depending on how you compiled you might have to add 'Resources/' in front of filenames in LearnSpriteSheets.cpp\n";
}

Scene *LearnSpriteSheets::createScene()
{
    auto scene = Scene::create();
    auto layer = LearnSpriteSheets::create();
    scene->addChild(layer);

    return scene;
}
Vector<cocos2d::SpriteFrame *> LearnSpriteSheets::getAnimation(const char *format, int count)
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
    /*********************/
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 vec_visible_size = Director::getInstance()->getVisibleSize();
    auto visible_size = Director::getInstance()->getVisibleSize();

    /******************/
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto close_item = MenuItemImage::create("CloseNormal.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(LearnSpriteSheets::menuCloseCallback, this));
    if (close_item == nullptr ||
        close_item->getContentSize().width <= 0 ||
        close_item->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visible_size.width  - close_item->getContentSize().width / 2;
        float y = origin.y + close_item->getContentSize().height / 2;
        close_item->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(close_item, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // Sequence
    auto callback_jump = CallFunc::create([](){
        log("Jumped");
    });
    auto callback_rotate = CallFunc::create([](){
        log("Rotate");
    });

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("scene1.plist"); //main character
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemies.plist"); //enemies character
    //background
    auto background = Sprite::createWithSpriteFrameName("Cartoon_Forest_BG_02.png");
    background->setPosition(origin.x + vec_visible_size.x / 2, origin.y + vec_visible_size.y / 2);
    this->addChild(background);

    //sprite main character
    auto frames = getAnimation("sprite-sheet-test/tile%03d.png", 3);
    auto sprite = Sprite::createWithSpriteFrame(frames.front());
    background->addChild(sprite);
    sprite->setPosition(100, 120);
    //sprite enemies
    auto enemies_frames = getAnimation("e%03d.png", 3);
    auto sprite_enemies = Sprite::createWithSpriteFrame(enemies_frames.front());
    background->addChild(sprite_enemies);
    sprite_enemies->setPosition(1000, 300);

    auto animation = Animation::createWithSpriteFrames(frames, 1.0f/4);
    sprite->runAction(RepeatForever::create(Animate::create(animation)));

    //move to
    auto movement = MoveTo::create(10, Vec2(1300, 100));
    auto resetPosition = MoveTo::create(0, Vec2(0, 120));

    auto my_spawn = Spawn::createWithTwoActions(Actions::SomeActions::jumpAction(),
                                                  Actions::SomeActions::rotateAction());
    auto sequence = Sequence::create(movement, resetPosition,
                                     my_spawn, nullptr);
    sprite->runAction(RepeatForever::create(sequence));

    return true;
}
void LearnSpriteSheets::menuCloseCallback(cocos2d::Ref *pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
