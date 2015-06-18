//
//  GameUILayer.cpp
//  Dragon
//
//  Created by B081mac on 15/4/14.
//
//

#include "GameUILayer.h"
#include "DataCenter.h"
#include "VisibleRect.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Progress.h"
using namespace CocosDenshion;

GameUILayer::GameUILayer()
:m_pGameLayer(NULL)
{
    
}

GameUILayer::~GameUILayer()
{
    
}

Scene* GameUILayer::gameScene()
{
    auto scene = Scene::create();
    
    auto layer = GameUILayer::create();
    
    scene->addChild(layer);
    
    return scene;
}



bool GameUILayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    CCLOG("%s",CCFileUtils::getInstance()->getWritablePath().c_str());
    initTop();
    
    initBG();
    
    showTarget();
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic("battle.mp3",true);
    
    return true;
}

void GameUILayer::showTarget()
{
    LayerColor* backLayerColor = LayerColor::create(Color4B(0, 0, 0, 0));
    this->addChild(backLayerColor,99);
    
    auto BG = Armature::create("bgmb_02");
    BG->getAnimation()->playWithIndex(0);
    BG->setPosition(VisibleRect::center() - Vec2(0, 185));
    backLayerColor->addChild(BG,1);
    
    BG->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_1(GameUILayer::removeTargetLayer, this,backLayerColor) );
    
    if (m_pGameLayer)
    {
        m_pGameLayer->removeFromParentAndCleanup(true);
    }
    
    m_pGameLayer = GameLayer::create();
    this->addChild(m_pGameLayer,10);
    m_pGameLayer->initPropSprite();
    
    m_mapTarget = DataCenter::getInstance()->getMapInfo()->getMapTarget();
    
    map<GemType ,int > ::iterator it = m_mapTarget.begin();
    int index = 0;
    while (it != m_mapTarget.end())
    {
        displayTarget(it->first, it->second, backLayerColor, index);
        index++;
        it++;
    }
    m_targetBG->getAnimation()->playWithIndex(3 - (int)m_mapTarget.size());
    
    initData();
}

void GameUILayer::displayTarget(GemType type, int num ,Node * pLayer ,int index)
{
    __String *str = __String::createWithFormat("%d",num);
    LabelAtlas * labelTarget = LabelAtlas::create("0", "defen_number.png", 16, 22, '0');
    labelTarget->setString(str->getCString());
    
    Sprite *sprTarget = Sprite::create();
    switch (type)
    {
        case empty:
            sprTarget->setTexture("icefloor.png");
            break;
        case red:
            sprTarget->setTexture("red.png");
            break;
        case yellow:
            sprTarget->setTexture("yellow.png");
            break;
        case blue:
            sprTarget->setTexture("blue.png");
            break;
        case green:
            sprTarget->setTexture("green.png");
            break;
        case purple:
            sprTarget->setTexture("purple.png");
            break;
        case white:
            sprTarget->setTexture("white.png");
            break;
        case ice:
            sprTarget->setTexture("ice.png");
            break;
        case dragontooth:
            sprTarget->setTexture("tooth.png");
            break;
        default:
            break;
    }

    pLayer->addChild(labelTarget ,2);
    pLayer->addChild(sprTarget, 2);
    
    sprTarget->setPosition(VisibleRect::center() - Vec2(100, 160 + index * 80));
    sprTarget->setOpacity(0);
    labelTarget->setPosition(sprTarget->getPosition() + Vec2(150, 0));
    labelTarget->setScale(2);
    labelTarget->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    labelTarget->setOpacity(0);
    
    sprTarget->runAction(Sequence::create(DelayTime::create(0.3),FadeIn::create(0.7), NULL));
    labelTarget->runAction(Sequence::create(DelayTime::create(0.3),FadeIn::create(0.7), NULL));
}

void GameUILayer::removeTargetLayer(Node *pSender, Node *pLayer)
{
    gameLayerFadeOut(pLayer,0.8);
    pLayer->runAction(Sequence::create(DelayTime::create(0.9), CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, pLayer)), NULL));
    
    m_pGameLayer->runAction(Sequence::create(DelayTime::create(0.9), CallFunc::create(CC_CALLBACK_0(GameLayer::appear, m_pGameLayer)), NULL));
}

void GameUILayer::initData()
{
//    if (m_pGameLayer)
//    {
//        m_pGameLayer->removeFromParentAndCleanup(true);
//    }
//    
//    m_pGameLayer = GameLayer::create();
//    this->addChild(m_pGameLayer,10);
//    m_pGameLayer->initPropSprite();
    if (DataCenter::getInstance()->getTimeLimit())
    {
        schedule(schedule_selector(GameUILayer::limitTime), 1.0);
    }
    
    m_bWinGame = false;
    m_iScoreNum = 0;
    m_labelScore->setString("0");
    m_labelScore->setScale(1);
    DataCenter::getInstance()->setWinnerMode(false);
    
    
    for (int i = 0; i < COLLECT_ARRAY; i++)
    {
        m_bComplete[i] = true;
    }
    
    for(int i=0;i<maxgem;i++)
    {
        m_iArrTargetNum[i]=0;
        m_iArrTargetIndex[i]=0;
    }
    
    MapInfo *info = DataCenter::getInstance()->getMapInfo();
    
    m_iOperationNum = info->getOperationNum();
    __String *str = __String::createWithFormat("%d",m_iOperationNum);
    m_labelOperation->setString(str->getCString());
    
    m_mapTarget = info->getMapTarget();
    
    map<GemType ,int > ::iterator it = m_mapTarget.begin();
    
    int index = 0;
    while (it != m_mapTarget.end())
    {
        m_iArrTargetNum[it->first] = it->second;
        m_iArrTargetIndex[it->first] = index;
        
        targetNumAndDisplay(index, it->first, it->second);
        
        m_bComplete[index] = false;
        m_sprAchieve[index]->setVisible(false);
        
        index++;
        
        it++;
    }
    m_targetBG->getAnimation()->playWithIndex(3 - (int)m_mapTarget.size());
}

void GameUILayer::initBG()
{
    auto sprSkillBG = Sprite::create("map01_00.png");
    sprSkillBG->setPosition(VisibleRect::bottom() + Vec2(0, sprSkillBG->getBoundingBox().size.height/2));
    this->addChild(sprSkillBG,6);
    
    auto sprGameBG = Sprite::create("map01_01.png");
    sprGameBG->setPosition(VisibleRect::bottom() + Vec2(0, sprGameBG->getBoundingBox().size.height/2));
    this->addChild(sprGameBG,5);
    
    auto sprTree = Sprite::create("map01_02.png");
    sprTree->setPosition(VisibleRect::top() + Vec2(0, -sprTree->getBoundingBox().size.height/2));
    this->addChild(sprTree,3);
    
    auto sprSky = Sprite::create("map01_05.png");
    sprSky->setPosition(VisibleRect::top() + Vec2(0, -sprSky->getBoundingBox().size.height/2));
    this->addChild(sprSky,0);
    
    auto sprMontain = Sprite::create("map01_03.png");
    sprMontain->setPosition(VisibleRect::top() + Vec2(0, -sprSky->getBoundingBox().size.height/2 - sprMontain->getBoundingBox().size.height/1.5));
    this->addChild(sprMontain,2);
    
    auto sprCloud = Sprite::create("map01_04.png");
    sprCloud->setPosition(VisibleRect::top() + Vec2(0, -sprCloud->getBoundingBox().size.height));
//    this->addChild(sprCloud,1);
    
    auto cloud = Armature::create("map01_yun");
    cloud->getAnimation()->playWithIndex(0);
    cloud->setPosition(VisibleRect::top() + Vec2(0, -sprCloud->getBoundingBox().size.height));
    this->addChild(cloud,1);
    
    auto light = Armature::create("map01_line");
    light->getAnimation()->playWithIndex(0);
    light->setPosition(VisibleRect::top() - Vec2(300, sprCloud->getBoundingBox().size.height/2));
    this->addChild(light,3);
    
    auto sprState1 = Sprite::create("map01_taizi.png");
    sprState1->setPosition(sprGameBG->getPosition() + Vec2(0, sprGameBG->getBoundingBox().size.height/2 - sprState1->getBoundingBox().size.height/2));
    this->addChild(sprState1,4);
    
    auto sprState2 = Sprite::create("map01_taizi.png");
    sprState2->setPosition(sprGameBG->getPosition() + Vec2(1.4*sprState2->getBoundingBox().size.width, sprGameBG->getBoundingBox().size.height/2 - sprState2->getBoundingBox().size.height/3));
    this->addChild(sprState2,4);
    
    auto sprState3 = Sprite::create("map01_taizi.png");
    sprState3->setPosition(sprGameBG->getPosition() + Vec2(-1.4*sprState3->getBoundingBox().size.width, sprGameBG->getBoundingBox().size.height/2 - sprState3->getBoundingBox().size.height/3));
    this->addChild(sprState3,4);
    
    auto sprState4 = Sprite::create("map01_taizi.png");
    sprState4->setPosition(sprGameBG->getPosition() + Vec2(2.8*sprState4->getBoundingBox().size.width, sprGameBG->getBoundingBox().size.height/2 - sprState4->getBoundingBox().size.height*0));
    this->addChild(sprState4,4);
    
    auto sprState5 = Sprite::create("map01_taizi.png");
    sprState5->setPosition(sprGameBG->getPosition() + Vec2(-2.8*sprState5->getBoundingBox().size.width, sprGameBG->getBoundingBox().size.height/2 - sprState5->getBoundingBox().size.height*0));
    this->addChild(sprState5,4);

}

void GameUILayer::initTop()
{
    Armature *stepBg = Armature::create("bushu_ui");
    this->addChild(stepBg,8);
    stepBg->getAnimation()->playWithIndex(0);
    stepBg->setPosition(VisibleRect::top() - Vec2(-105, stepBg->getBoundingBox().size.height/2 + 8));
    
    m_labelOperation = LabelAtlas::create("0", "bushu_number.png", 22, 33, '0');
    this->addChild(m_labelOperation,8);
    m_labelOperation->setPosition(Vec2(423, 1082));
    m_labelOperation->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    m_labelScore = LabelAtlas::create("0", "defen_number.png", 16, 22, '0');
    this->addChild(m_labelScore,8);
    m_labelScore->setPosition(Vec2(533, 1080));
    m_labelScore->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    DataCenter::getInstance()->setPosStar(m_labelOperation->getPosition());
    
    auto *imageItem = MenuItemImage::create("ui_zanting01.png", "ui_zanting02.png", CC_CALLBACK_1(GameUILayer::pauseMenu, this));
    imageItem->setPosition(VisibleRect::rightTop() - Point(imageItem->getBoundingBox().size.width/2 , imageItem->getBoundingBox().size.height/2 ));
    
    auto menu = Menu::create(imageItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 8);
    
    auto levelBg = Sprite::create("ui_gkdiban.png");
    this->addChild(levelBg, 11);
    levelBg->setPosition(VisibleRect::right() - Vec2(levelBg->getBoundingBox().size.width/2, -124));
    
    auto labelLevel = LabelAtlas::create("1", "guanqia_number.png", 12, 16, '0');
    this->addChild(labelLevel, 11);
    labelLevel->setPosition(levelBg->getPosition() + Vec2(23, 6));
    labelLevel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    
    auto coinBg = Sprite::create("ui_longbidiban.png");
    this->addChild(coinBg, 11);
    coinBg->setPosition(VisibleRect::left() + Vec2(levelBg->getBoundingBox().size.width/2, 124));
    
    auto labelCoin = LabelAtlas::create("9999", "guanqia_number.png", 12, 16, '0');
    this->addChild(labelCoin, 11);
    labelCoin->setPosition(coinBg->getPosition() + Vec2(4, 6));
    labelCoin->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    
    auto coin = Sprite::create("ui_longbi.png");
    this->addChild(coin, 11);
    coin->setPosition(coinBg->getPosition() - Vec2(45, -10));
    
    
    m_targetBG = Armature::create("guanqiamubiao_ui");
    this->addChild(m_targetBG, 8);
    m_targetBG->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    m_targetBG->setPosition(VisibleRect::leftTop() + Vec2(m_targetBG->getBoundingBox().size.width/2 + 10, 0));
    m_targetBG->getAnimation()->playWithIndex(0);
    
    float distance = 40;
    for (int i = 0; i < COLLECT_ARRAY; i++)
    {
        m_sprTarget[i] = Sprite::create("red.png");
        m_sprTarget[i]->setScale(0.45);
        m_sprTarget[i]->setPosition(m_targetBG->getPosition() - Point( m_sprTarget[i]->getBoundingBox().size.height/1.5, distance * i + 65));
        this->addChild(m_sprTarget[i], 8);
        m_sprTarget[i]->setVisible(false);
        
        m_labelTarget[i] = LabelAtlas::create("0", "defen_number.png", 16, 22, '0');
        m_labelTarget[i]->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
        m_labelTarget[i]->setPosition(m_targetBG->getPosition() - Point( -m_sprTarget[i]->getBoundingBox().size.height/1.5, distance * i + 52));
        this->addChild(m_labelTarget[i], 9);
        m_labelTarget[i]->setVisible(false);
        
        m_sprAchieve[i] = Sprite::create("wancheng_ui.png");
        m_sprAchieve[i]->setPosition(m_targetBG->getPosition() - Point( -m_sprTarget[i]->getBoundingBox().size.height/1.5, distance * i + 62));
        this->addChild(m_sprAchieve[i], 8);
        m_sprAchieve[i]->setVisible(false);
    }
    
    Progress *pro1 = Progress::create("ui_nuqi01.png", "ui_nuqi02.png");
    this->addChild(pro1, 8);
    pro1->setPosition(320,705);
    pro1->setProgress(100);
    
    Progress *pro2 = Progress::create("ui_nuqi01.png", "ui_nuqi02.png");
    this->addChild(pro2, 8);
    pro2->setPosition(60,741);
    pro2->setProgress(80);
    
    Progress *pro3 = Progress::create("ui_nuqi01.png", "ui_nuqi02.png");
    this->addChild(pro3, 8);
    pro3->setPosition(188,718);
    pro3->setProgress(50);
    
    Progress *pro4 = Progress::create("ui_nuqi01.png", "ui_nuqi02.png");
    this->addChild(pro4, 8);
    pro4->setPosition(450,718);
    pro4->setProgress(20);
    
    Progress *pro5 = Progress::create("ui_nuqi01.png", "ui_nuqi02.png");
    this->addChild(pro5, 8);
    pro5->setPosition(580,741);
    pro5->setProgress(60);
    
    Progress *pro6 = Progress::create("ui_hpboss01.png", "ui_hpboss02.png");
    this->addChild(pro6, 8);
    pro6->setPosition(315,1040);
    pro6->setProgress(40);
    
    Progress *pro7 = Progress::create("ui_jindu01.png", "ui_jindu02.png");
    this->addChild(pro7, 8);
    pro7->setPosition(530,1055);
    pro7->setProgress(40);
    
//    auto star1 = Sprite::create("ui_star02.png");
//    this->addChild(star1, 18);
//    star1->setPosition(pro7->getPosition() - Vec2(20, 0));
//    
//    auto star2 = Sprite::create("ui_star02.png");
//    this->addChild(star2, 18);
//    star2->setPosition(pro7->getPosition() + Vec2(20, 0));
//    
//    auto star3 = Sprite::create("ui_star02.png");
//    this->addChild(star3, 18);
//    star3->setPosition(pro7->getPosition() + Vec2(60, 0));
}

void GameUILayer::targetNumAndDisplay(int index,GemType type, int num)
{
    m_labelTarget[index]->setVisible(true);
    m_sprTarget[index]->setVisible(true);
    
    __String *str = __String::createWithFormat("%d",num);
    m_labelTarget[index]->setString(str->getCString());
    
    switch (type)
    {
        case empty:
            m_sprTarget[index]->setTexture("icefloor.png");
            break;
        case red:
            m_sprTarget[index]->setTexture("red.png");
            break;
        case yellow:
            m_sprTarget[index]->setTexture("yellow.png");
            break;
        case blue:
            m_sprTarget[index]->setTexture("blue.png");
            break;
        case green:
            m_sprTarget[index]->setTexture("green.png");
            break;
        case purple:
            m_sprTarget[index]->setTexture("purple.png");
            break;
        case white:
            m_sprTarget[index]->setTexture("white.png");
            break;
        case ice:
            m_sprTarget[index]->setTexture("ice.png");
            break;
        case dragontooth:
            m_sprTarget[index]->setTexture("tooth.png");
            break;
        default:
            break;
    }
    
    DataCenter::getInstance()->initMapPoint(type, m_sprTarget[index]->getPosition());
}

void GameUILayer::addBlackLayer(LAYER_TYPE type)
{
    //添加一个半灰色的层
    LayerColor* backLayerColor = LayerColor::create(Color4B(25, 25, 25, 125));
    this->addChild(backLayerColor,99);
    
    auto BG = Armature::create("ui_db1");
    BG->getAnimation()->playWithIndex(0);
    BG->setPosition(VisibleRect::center());
    
    backLayerColor->addChild(BG,1);
    
    //添加向下触摸屏蔽
    auto callback = [](Touch * ,Event *)
    {
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,backLayerColor);
    
    
    
    switch (type)
    {
        case layerPause:
        {
            
        }
            break;
        case layerTime:
        {
            BG->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_1(GameUILayer::addTimeDown, this,backLayerColor) );
        }
            break;
        default:
            break;
    }

}

void GameUILayer::pauseMenu(Ref *pSender)
{
    
    //添加一个半灰色的层
    LayerColor* backLayerColor = LayerColor::create(Color4B(25, 25, 25, 125));
    this->addChild(backLayerColor,99);
    
    auto BG = Armature::create("ui_db1");
    BG->getAnimation()->playWithIndex(0);
    BG->setPosition(VisibleRect::center());
    backLayerColor->addChild(BG,1);

    auto cloud = Armature::create("ui_zanting");
    cloud->getAnimation()->playWithIndex(0);
    cloud->setPosition(VisibleRect::center() + Vec2(0, 30));
    backLayerColor->addChild(cloud,2);
    
    
        
    //添加向下触摸屏蔽
    auto callback = [](Touch * ,Event *)
    {
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,backLayerColor);
    
    auto *labelItemRestar = MenuItemImage::create("icon_chonglai.png", "icon_chonglai2.png", bind(&GameUILayer::restarGame, this, std::placeholders::_1, backLayerColor));
    
    auto *labelItemQuit = MenuItemImage::create("icon_zhucaidan.png", "icon_zhucaidan2.png", CC_CALLBACK_1(GameUILayer::quitGame, this));
    
    auto *labelItemContinue = MenuItemImage::create("icon_jixu.png", "icon_jixu2.png", bind(&GameUILayer::continueGame, this, std::placeholders::_1, backLayerColor));
    
    auto *labelItemCha = MenuItemImage::create("icon_guanbi01_1.png", "icon_guanbi01_2.png", bind(&GameUILayer::continueGame, this, std::placeholders::_1, backLayerColor));
    labelItemCha->setOpacity(0);
    labelItemCha->runAction(FadeIn::create(1));
    auto menu = Menu::create(labelItemQuit,labelItemRestar,labelItemContinue, NULL);
    menu->setPosition(VisibleRect::center() - Vec2(0, 85));
    menu->alignItemsHorizontallyWithPadding(100);
    backLayerColor->addChild(menu,2);
    
    auto menu2 = Menu::create(labelItemCha, NULL);
    menu2->setPosition(cloud->getPosition() + Vec2(265, 65));
    backLayerColor->addChild(menu2,2);
}


void GameUILayer::quitGame(Ref *pSender)
{
    resumeGame();
    DataCenter::getInstance()->destroyMapInfo();
    DataCenter::getInstance()->setTimeLimit(false);
    Director::getInstance()->pushScene(HelloWorld::createScene());
}

void GameUILayer::continueGame(Ref *pSender, Node *pNode)
{
    resumeGame();
    pNode->removeFromParentAndCleanup(true);
}

void GameUILayer::add5Step(Ref *pSender, Node *pNode)
{
    m_iOperationNum += 5;
    __String *str = __String::createWithFormat("%d",m_iOperationNum);
    m_labelOperation->setString(str->getCString());
    pNode->removeFromParentAndCleanup(true);
}

void GameUILayer::restarGame(Ref *pSender,Node* pNode)
{
    resumeGame();
    pNode->removeFromParentAndCleanup(true);
    
    gameLayerFadeOut(m_pGameLayer , 0.8);
    
    this->runAction(Sequence::create(DelayTime::create(0.9), CallFunc::create(CC_CALLBACK_0(GameUILayer::showTarget, this)), NULL));
    
}

void GameUILayer::resumeGame()
{
    Director::getInstance()->resume();
}

void GameUILayer::pauseGame()
{
    Director::getInstance()->pause();
}

void GameUILayer::updateOperationNum(Ref *obj)
{
    if (!DataCenter::getInstance()->getTimeLimit())
    {
        float time = 0;
        if (m_bWinGame)
        {
            time = 0.2;
        }
        else
        {
            time = 0.3;
        }
        m_labelOperation->runAction(Sequence::create(ScaleTo::create(time/2, 1.5),ScaleTo::create(time/2, 1) , CallFunc::create(CC_CALLBACK_0(GameUILayer::operationAnimaOver, this)), NULL));
//        m_iOperationNum--;
//        __String *str = __String::createWithFormat("%d",m_iOperationNum);
//        m_labelOperation->setString(str->getCString());
    }
}

void GameUILayer::operationAnimaOver()
{
    m_iOperationNum--;
    __String *str = __String::createWithFormat("%d",m_iOperationNum);
    m_labelOperation->setString(str->getCString());
}

void GameUILayer::failGame()
{
    addBlackLayer(layerTime);
//    Director::getInstance()->pause();
//    
//    //添加一个半灰色的层
//    LayerColor* backLayerColor = LayerColor::create(Color4B(25, 25, 25, 125));
//    this->addChild(backLayerColor,99);
//    //添加向下触摸屏蔽
//    auto callback = [](Touch * ,Event *)
//    {
//        return true;
//    };
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->onTouchBegan = callback;
//    listener->setSwallowTouches(true);
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,backLayerColor);
//    
//    auto *labelItemRestar = MenuItemLabel::create(Label::createWithSystemFont("重新挑战", "",30 ), bind(&GameUILayer::restarGame, this, std::placeholders::_1, backLayerColor));
//    labelItemRestar->setPosition(Vec2::ZERO);
//    
//    auto *labelItemQuit = MenuItemLabel::create(Label::createWithSystemFont("升级宠物", "",30 ), CC_CALLBACK_1(GameUILayer::quitGame, this));
//    labelItemQuit->setPosition(Vec2::ZERO);
//    
//    
//    auto menu = Menu::create(labelItemRestar,labelItemQuit, NULL);
//    menu->setPosition(VisibleRect::center());
//    menu->alignItemsHorizontallyWithPadding(20);
//    backLayerColor->addChild(menu);

}

void GameUILayer::addTimeDown(Node *pSender, Node *pLayer)
{
    auto time = Armature::create("djs_01");
    time->getAnimation()->playWithIndex(0);
    time->setPosition(VisibleRect::center() + Vec2(0, 230));
    time->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_1(GameUILayer::failLayer, this,pLayer) );
    pLayer->addChild(time,2);
    
    auto words = Armature::create("ui_jia501");
    words->getAnimation()->playWithIndex(0);
    words->setPosition(VisibleRect::center() + Vec2(0, 30));
    pLayer->addChild(words,2);

    auto add = Armature::create("jiawu_icon");
    pLayer->addChild(add,2);
    add->setPosition(VisibleRect::center() - Vec2(100, 50));
    add->getAnimation()->play("Animation1");
    
    auto *labelItemRestar = MenuItemImage::create("icon_queding.png", "icon_queding2.png", bind(&GameUILayer::add5Step, this, std::placeholders::_1, pLayer));
    labelItemRestar->setPosition(Vec2::ZERO);

    
    auto menu = Menu::create(labelItemRestar, NULL);
    menu->setPosition(VisibleRect::center() + Vec2(50, -50));
    pLayer->addChild(menu,2);

}

 void GameUILayer::failLayer(Node* pSender , Node * pLayer)
{
    pLayer->removeAllChildren();
    
    auto BG = Armature::create("ui_db1");
    BG->getAnimation()->playWithIndex(0);
    BG->setPosition(VisibleRect::center());
    pLayer->addChild(BG,1);
    
    auto fail = Armature::create("ui_cgsb01");
    fail->getAnimation()->playWithIndex(0);
    fail->setPosition(VisibleRect::center() + Vec2(0, 50));
    pLayer->addChild(fail,2);

    auto *labelItemRestar = MenuItemImage::create("icon_cxtz.png", "icon_cxtz2.png", bind(&GameUILayer::restarGame, this, std::placeholders::_1, pLayer));
    
    auto *labelItemQuit = MenuItemImage::create("icon_jinhua.png", "icon_jinhua2.png", CC_CALLBACK_1(GameUILayer::quitGame, this));
    
    auto menu = Menu::create(labelItemQuit,labelItemRestar,NULL);
    menu->setPosition(VisibleRect::center() - Vec2(0, 65));
    menu->alignItemsHorizontallyWithPadding(100);
    pLayer->addChild(menu,2);

}

void GameUILayer::matchOver(Ref *obj)
{
    if (!DataCenter::getInstance()->getTimeLimit())
    {
        limitOperatiomNum();
    }
}

void GameUILayer::limitOperatiomNum()
{
    if (m_bWinGame)
    {
        
        if (m_iOperationNum == 0)
        {
            if (m_pGameLayer)
            {
                gameLayerFadeOut(m_pGameLayer , 0.8);
            }
            this->runAction(Sequence::create(DelayTime::create(0.9),CallFunc::create(CC_CALLBACK_0(GameUILayer::addWinLayer, this)), NULL));
//            DataCenter::getInstance()->setWinnerMode(true);
//            MessageBox("YOU WIN !!!", "Congratulate");
        }
        else
        {
            if (!DataCenter::getInstance()->getWinnerMode())
            {
                DataCenter::getInstance()->setWinnerMode(true);
                auto BG = Armature::create("ui_db1");
                BG->getAnimation()->playWithIndex(0);
                BG->setPosition(VisibleRect::center());
                this->addChild(BG,11);
                BG->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_1(GameUILayer::completeWords, this) );
            }
            else
            {
                __String *str = __String::createWithFormat("%d",m_iOperationNum);
                NotificationCenter::getInstance()->postNotification(kMSG_WinnerModeStart, str);
            }
        }
    }
    else
    {
        if (m_iOperationNum == 0)
        {
            failGame();
        }
    }

}

void GameUILayer::completeWords(Node *pSender)
{
    auto BG = Armature::create("ui_mbdc01");
    BG->getAnimation()->playWithIndex(0);
    BG->setPosition(Vec2::ZERO);
    pSender->addChild(BG,1);
    
    pSender->runAction(Sequence::create(DelayTime::create(1.5) ,FadeOut::create(1), CallFuncN::create(CC_CALLBACK_1(GameUILayer::winnerMode, this) ), NULL));
}

void GameUILayer::winnerMode(Node *pSender)
{
    pSender->removeFromParentAndCleanup(true);
    __String *str = __String::createWithFormat("%d",m_iOperationNum);
    NotificationCenter::getInstance()->postNotification(kMSG_WinnerModeStart, str);
}

void GameUILayer::limitTime(float dt)
{
    m_iOperationNum--;
    __String *str = __String::createWithFormat("%d",m_iOperationNum);
    m_labelOperation->setString(str->getCString());
    
    if (m_iOperationNum == 0)
    {
        failGame();
    }
}

void GameUILayer::gameLayerFadeOut(Node *pSender  ,float times)
{
    if (pSender)
    {
        pSender->runAction(FadeOut::create(times));
    }
    Vector<Node*> children = pSender->getChildren();
    
    if (children.size() > 0)
    {
        for (int i = 0; i < children.size(); i++)
        {
            gameLayerFadeOut(children.at(i),times);
        }
    }
}

void GameUILayer::gameLayerFadeIn(Node *pSender  ,float times)
{
    if (pSender)
    {
        pSender->runAction(FadeIn::create(times));
    }
    Vector<Node*> children = pSender->getChildren();
    
    if (children.size() > 0)
    {
        for (int i = 0; i < children.size(); i++)
        {
            gameLayerFadeIn(children.at(i),times);
        }
    }
}

//void GameUILayer::gameLayerSetOpacity(Node *pSender)
//{
//    if (pSender)
//    {
//        pSender->setOpacity(0);
//    }
//    Vector<Node*> children = pSender->getChildren();
//    
//    if (children.size() > 0)
//    {
//        for (int i = 0; i < children.size(); i++)
//        {
//            gameLayerSetOpacity(children.at(i));
//        }
//    }
//}


void GameUILayer::addWinLayer()
{
    LayerColor* backLayerColor = LayerColor::create(Color4B(0, 0, 0, 0));
    this->addChild(backLayerColor,99);

    auto BG = Armature::create("ui_db1");
    BG->getAnimation()->playWithIndex(0);
    BG->setPosition(VisibleRect::center() - Vec2(0, 370));
    backLayerColor->addChild(BG,1);
    
    auto fail = Armature::create("ui_diwen1");
    fail->getAnimation()->playWithIndex(0);
    fail->setPosition(VisibleRect::center() - Vec2(0, 128));
    backLayerColor->addChild(fail,2);
    
    auto score = Armature::create("ui_fs");
    score->getAnimation()->playWithIndex(0);
    score->setPosition(VisibleRect::center() - Vec2(200, 330));
    backLayerColor->addChild(score,2);
    
    auto reward = Armature::create("ui_ggjl01");//ui_fz01
    reward->getAnimation()->playWithIndex(0);
    reward->setPosition(VisibleRect::center() - Vec2(200, 390));
    backLayerColor->addChild(reward,2);
    
    
    //添加向下触摸屏蔽
//    auto callback = [](Touch * ,Event *)
//    {
//        return true;
//    };
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->onTouchBegan = callback;
//    listener->setSwallowTouches(true);
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,backLayerColor);


    auto *labelItemRestar = MenuItemImage::create("icon_chonglai.png", "icon_chonglai2.png", bind(&GameUILayer::restarGame, this, std::placeholders::_1, backLayerColor));
    
    auto *labelItemQuit = MenuItemImage::create("icon_zhucaidan.png", "icon_zhucaidan2.png", CC_CALLBACK_1(GameUILayer::quitGame, this));
    
    auto *labelItemContinue = MenuItemImage::create("icon_xiayiguan2.png", "icon_xiayiguan2.png", CC_CALLBACK_1(GameUILayer::quitGame, this));
    
    auto *labelItemCha = MenuItemImage::create("icon_guanbi01_1.png", "icon_guanbi01_2.png", CC_CALLBACK_1(GameUILayer::quitGame, this));
    labelItemCha->setOpacity(0);
    labelItemCha->runAction(FadeIn::create(1));
    auto menu = Menu::create(labelItemQuit,labelItemRestar,labelItemContinue, NULL);
    menu->setPosition(VisibleRect::center() - Vec2(0, 480));
    menu->alignItemsHorizontallyWithPadding(150);
    backLayerColor->addChild(menu,2);
    
    auto menu2 = Menu::create(labelItemCha, NULL);
    menu2->setPosition(BG->getPosition() + Vec2(265, 95));
    backLayerColor->addChild(menu2,2);

    __String *str = __String::createWithFormat("%d",m_iScoreNum);
    LabelAtlas * labelScore = LabelAtlas::create("0", "defen_number.png", 16, 22, '0');
    labelScore->setString(str->getCString());
    backLayerColor->addChild(labelScore,2);
    labelScore->setPosition(Vec2(VisibleRect::center().x, score->getPositionY()));
    labelScore->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    labelScore->setScale(2);
}

void GameUILayer::updateCollect(Ref *obj)
{
    __String *str = (__String*)obj;
    int iMsg = str->intValue();
    
    int times = iMsg/1000;
    m_iScoreNum += times * 20;
    __String *score = __String::createWithFormat("%d",m_iScoreNum);
    m_labelScore->setString(score->getCString());
    m_labelScore->setScale(1);
    m_labelScore->stopAllActions();
    m_labelScore->runAction(Sequence::create(ScaleTo::create(0.1, 1.2), ScaleTo::create(0.1, 1),ScaleTo::create(0.1, 1.2),ScaleTo::create(0.1, 1),NULL));
    
    GemType type = (GemType)(iMsg%100);
    int index = m_iArrTargetIndex[type];
    if (m_iArrTargetNum[type] > 0)
    {
        m_iArrTargetNum[type]--;
        if (m_iArrTargetNum[type] == 0)
        {
            m_labelTarget[index]->setVisible(false);
            m_bComplete[index] = true;
            m_sprAchieve[index]->setVisible(true);
            m_sprAchieve[index]->setScale(4);
            m_sprAchieve[index]->runAction(ScaleTo::create(0.2, 1));
        }
        else
        {
            __String *str = __String::createWithFormat("%d",m_iArrTargetNum[type]);
            m_labelTarget[index]->setString(str->getCString());
        }
    }
    
    m_bWinGame = true;
    
    for (int i = 0; i < COLLECT_ARRAY; i++)
    {
        if (m_bComplete[i] == false)
        {
            m_bWinGame = false;
        }
    }
}

void GameUILayer::onEnter()
{
    Layer::onEnter();
    
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameUILayer::updateOperationNum), kMSG_UpdateMoves, NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameUILayer::matchOver), kMSG_MatchDown, NULL);
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameUILayer::updateCollect), kMSG_ShowCollecte, NULL);
}

void GameUILayer::onExit()
{
    NotificationCenter::getInstance()->removeObserver(this, kMSG_UpdateMoves);
    NotificationCenter::getInstance()->removeObserver(this, kMSG_MatchDown);
    NotificationCenter::getInstance()->removeObserver(this, kMSG_ShowCollecte);
    Layer::onExit();
}
