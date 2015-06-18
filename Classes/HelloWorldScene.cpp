#include "HelloWorldScene.h"
#include "GameLayer.h"
#include "VisibleRect.h"
#include "GameUILayer.h"
#include "DataCenter.h"
#include "cocostudio/CocoStudio.h"
using namespace rapidjson;

using namespace cocostudio;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

	CCLOG("visibleSize.width = %f, visibleSize.height = %f",visibleSize.width,visibleSize.height);
	CCLOG("origin.width = %f, origin.height = %f",origin.x,origin.y);
	CCLOG("winSize.width = %f, winSize.height = %f",winSize.width,winSize.height);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                            CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto labelItem1 = MenuItemLabel::create(Label::createWithSystemFont("普通关卡", "",30 ), CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    labelItem1->setPosition(Vec2::ZERO);
    
    auto labelItem2 = MenuItemLabel::create(Label::createWithSystemFont("无限关卡", "",30 ), CC_CALLBACK_1(HelloWorld::menuTimeLimit, this));
    
    labelItem2->setPosition(Vec2::ZERO);
    
    auto labelItem3 = MenuItemLabel::create(Label::createWithSystemFont("播放动画", "",30 ), CC_CALLBACK_1(HelloWorld::menuAnimation, this));
    
    labelItem3->setPosition(Vec2::ZERO);
    
    auto labelItem4 = MenuItemLabel::create(Label::createWithSystemFont("Shader", "",30 ), CC_CALLBACK_1(HelloWorld::menuAddShader, this));
    
    labelItem4->setPosition(Vec2::ZERO);

    
    // create menu, it's an autorelease object
    auto menu = Menu::create(labelItem1,labelItem2, NULL);
    menu->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    menu->alignItemsVerticallyWithPadding(10);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    // add the label as a child to this layer
//    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    sprite->setTag(567);
    
//    GemAction::getInstance();
//    GemAction::setBright(sprite);
    
//	Sprite *sp = Sprite::create("orange.png");
//	this->addChild(sp,2);
//	sp->setPosition(sprite->getPosition());
    
//    auto sprBG = Sprite::create("BG.png");
//    this->addChild(sprBG,100);
//    sprBG->setPosition(VisibleRect::center());
    m_iTimes = 0;
	
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Anemoi0.png" , "Anemoi0.plist" , "Anemoi.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Apollo0.png" , "Apollo0.plist" , "Apollo.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Asteria0.png" , "Asteria0.plist" , "Asteria.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Cronus0.png" , "Cronus0.plist" , "Cronus.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Doris0.png" , "Doris0.plist" , "Doris.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Gaea0.png" , "Gaea0.plist" , "Gaea.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Hecate0.png" , "Hecate0.plist" , "Hecate.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("hephaestus0.png" , "hephaestus0.plist" , "hephaestus.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Hades0.png" , "Hades0.plist" , "Hades.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Hades_20.png" , "Hades_20.plist" , "Hades_2.ExportJson");
    
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("nice_effect0.png" , "nice_effect0.plist" , "nice_effect.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("excellent_effect0.png" , "excellent_effect0.plist" , "excellent_effect.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("unbelievable_effect0.png" , "unbelievable_effect0.plist" , "unbelievable_effect.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("effect_xuanzhong0.png" , "effect_xuanzhong0.plist" , "effect_xuanzhong.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("effect_chuizi0.png" , "effect_chuizi0.plist" , "effect_chuizi.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("chuizi_icon0.png" , "chuizi_icon0.plist" , "chuizi_icon.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("jiawu_icon0.png" , "jiawu_icon0.plist" , "jiawu_icon.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("lingxing_icon0.png" , "lingxing_icon0.plist" , "lingxing_icon.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("mobang_icon0.png" , "mobang_icon0.plist" , "mobang_icon.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("nuqi_icon0.png" , "nuqi_icon0.plist" , "nuqi_icon.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("shizi_icon0.png" , "shizi_icon0.plist" , "shizi_icon.ExportJson");
    
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("effect_suilie0.png" , "effect_suilie0.plist" , "effect_suilie.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("effect_suilie1.png" , "effect_suilie1.plist" , "effect_suilie.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("effect_bingkuaisui0.png" , "effect_bingkuaisui0.plist" , "effect_bingkuaisui.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("effect_bingkuaisui1.png" , "effect_bingkuaisui1.plist" , "effect_bingkuaisui.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("effect_tiechuangsui0.png" , "effect_tiechuangsui0.plist" , "effect_tiechuangsui.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("tongsexiao0.png" , "tongsexiao0.plist" , "tongsexiao.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("blue_liang0.png" , "blue_liang0.plist" , "blue_liang.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("green_liang0.png" , "green_liang0.plist" , "green_liang.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("purple_liang0.png" , "purple_liang0.plist" , "purple_liang.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("red_liang0.png" , "red_liang0.plist" , "red_liang.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("white_liang0.png" , "white_liang0.plist" , "white_liang.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("yellow_liang0.png" , "yellow_liang0.plist" , "yellow_liang.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("hengxiao_effect0.png" , "hengxiao_effect0.plist" , "hengxiao_effect.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("jiugong01_effect0.png" , "jiugong01_effect0.plist" , "jiugong01_effect.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("jiugong02_effect0.png" , "jiugong02_effect0.plist" , "jiugong02_effect.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("bushu_ui0.png" , "bushu_ui0.plist" , "bushu_ui.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("guanqiamubiao_ui0.png" , "guanqiamubiao_ui0.plist" , "guanqiamubiao_ui.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("xialuojiantou0.png" , "xialuojiantou0.plist" , "xialuojiantou.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("hudun_effect0.png" , "hudun_effect0.plist" , "hudun_effect.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("buju_effect0.png" , "buju_effect0.plist" , "buju_effect.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("xialuojiantou0.png" , "xialuojiantou0.plist" , "xialuojiantou.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("tsx_eff0.png" , "tsx_eff0.plist" , "tsx_eff.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("jvqi_effect0.png" , "jvqi_effect0.plist" , "jvqi_effect.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("map01_line0.png" , "map01_line0.plist" , "map01_line.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("map01_yun0.png" , "map01_yun0.plist" , "map01_yun.ExportJson");
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("ui_zanting0.png" , "ui_zanting0.plist" , "ui_zanting.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("ui_db10.png" , "ui_db10.plist" , "ui_db1.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("jiafen0.png" , "jiafen0.plist" , "jiafen.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("ui_cgsb010.png" , "ui_cgsb010.plist" , "ui_cgsb01.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("djs_010.png" , "djs_010.plist" , "djs_01.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("ui_jia5010.png" , "ui_jia5010.plist" , "ui_jia501.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("jiugong03_effect0.png" , "jiugong03_effect0.plist" , "jiugong03_effect.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("jiugong04_effect0.png" , "jiugong04_effect0.plist" , "jiugong04_effect.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("ui_mbdc010.png" , "ui_mbdc010.plist" , "ui_mbdc01.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("ui_diwen10.png" , "ui_diwen10.plist" , "ui_diwen1.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("ui_fs0.png" , "ui_fs0.plist" , "ui_fs.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("ui_fz010.png" , "ui_fz010.plist" , "ui_fz01.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("ui_ggjl010.png" , "ui_ggjl010.plist" , "ui_ggjl01.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("bgmb_020.png" , "bgmb_020.plist" , "bgmb_02.ExportJson");

    
//    Armature *armature1 = Armature::create( "Anemoi");
//    armature1->setPosition(Point(visibleSize.width * 0.5, visibleSize.height * 0.9));
//
//    armature1->getAnimation()->playWithIndex(m_iTimes);
//    this->addChild(armature1);
//    armature1->setTag(111);
//
//    
//    Armature *armature2 = Armature::create( "Apollo");
//    armature2->setPosition(Point(visibleSize.width * 0.25, visibleSize.height * 0.9));
//    
//    armature2->getAnimation()->playWithIndex(m_iTimes);
//    this->addChild(armature2);
//    armature2->setTag(222);
//    
//    Armature *armature3 = Armature::create( "Asteria");
//    armature3->setPosition(Point(visibleSize.width * 0.75, visibleSize.height * 0.9));
//    
//    armature3->getAnimation()->playWithIndex(m_iTimes);
//    this->addChild(armature3);
//    armature3->setTag(333);
//    
//    Armature *armature4 = Armature::create( "Cronus");
//    armature4->setPosition(Point(visibleSize.width * 0.5, visibleSize.height * 0.78));
//    
//    armature4->getAnimation()->playWithIndex(m_iTimes);
//    this->addChild(armature4);
//    armature4->setTag(444);
//    
//    Armature *armature5 = Armature::create( "Doris");
//    armature5->setPosition(Point(visibleSize.width * 0.25, visibleSize.height * 0.78));
//    
//    armature5->getAnimation()->playWithIndex(m_iTimes);
//    this->addChild(armature5);
//    armature5->setTag(555);
//    
//    
//    Armature *armature6 = Armature::create( "Gaea");
//    armature6->setPosition(Point(visibleSize.width * 0.75, visibleSize.height * 0.78));
//    
//    armature6->getAnimation()->playWithIndex(m_iTimes);
//    this->addChild(armature6);
//    armature6->setTag(666);
//    
//    Armature *armature7 = Armature::create( "Hecate");
//    armature7->setPosition(Point(visibleSize.width * 0.25, visibleSize.height * 0.65));
//    
//    armature7->getAnimation()->playWithIndex(m_iTimes);
//    this->addChild(armature7);
//    armature7->setTag(777);
//    
//    Armature *armature8 = Armature::create( "hephaestus");
//    armature8->setPosition(Point(visibleSize.width * 0.75, visibleSize.height * 0.65));
//    
//    armature8->getAnimation()->playWithIndex(m_iTimes);
//    this->addChild(armature8);
//    armature8->setTag(888);
//    
//    
//    Armature *armature9 = Armature::create( "Hades");
//    armature9->setPosition(Point(visibleSize.width * 0.25, visibleSize.height * 0.20));
//    
//    armature9->getAnimation()->playWithIndex(m_iTimes);
//    this->addChild(armature9);
//    armature9->setTag(999);
//    
//    Armature *armature10 = Armature::create( "Hades_2");
//    armature10->setPosition(Point(visibleSize.width * 0.75, visibleSize.height * 0.20));
//    
//    armature10->getAnimation()->playWithIndex(m_iTimes);
//    this->addChild(armature10);
//    armature10->setTag(101);
//    
////    CCLOG("%zd",armature1->getAnimation()->getMovementCount());
//    
//    CCLOG("%zd",armature2->getAnimation()->getMovementCount());
//    
//    CCLOG("%zd",armature3->getAnimation()->getMovementCount());
//    
//    CCLOG("%zd",armature4->getAnimation()->getMovementCount());
//    
//    CCLOG("%zd",armature5->getAnimation()->getMovementCount());
//    
//    CCLOG("%zd",armature6->getAnimation()->getMovementCount());
//    
//    CCLOG("%zd",armature7->getAnimation()->getMovementCount());
//
//    CCLOG("%zd",armature8->getAnimation()->getMovementCount());
//
//    CCLOG("%zd",armature9->getAnimation()->getMovementCount());
//    
//    CCLOG("%zd",armature9->getAnimation()->getMovementCount());
//    
//    CCLOG("%zd",armature10->getAnimation()->getMovementCount());
//    
//    ParticleSystemQuad *partic1 = ParticleSystemQuad::create("tongsexiao.plist");
//    this->addChild(partic1);
//    partic1->setPosition(Vec2::ZERO);
//
//    for (int i = 0; i < 10; i++)
//    {
//        auto spr = Sprite::create("texiao2.png");
//        this->addChild(spr,9);
//        spr->setPosition(0,500 + i * 6);
//        spr->setScaleY(0.05);
//        spr->runAction(RepeatForever::create(Sequence::create(DelayTime::create(0.1),CallFuncN::create(CC_CALLBACK_1(HelloWorld::changeColor, this)), NULL)));
//    }
//    
    return true;
}


void HelloWorld::changeColor(Node *pSender)
{
    auto spr = (Sprite*)pSender;
    spr->setColor(Color3B(arc4random()%255, arc4random()%255, arc4random()%255));
    spr->setOpacity(100);
}

bool HelloWorld::ShowJsonData()
{
    string filename="MyTest.json";
    rapidjson::Document doc;
    //判断文件是否存在
    if(!FileUtils::getInstance()->isFileExist(filename))
    {
        log("json file is not find [%s]",filename.c_str());
        return false;
    }
    //读取文件数据，初始化doc
    std::string data=FileUtils::getInstance()->getStringFromFile(filename);
    doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
    //判断读取成功与否 和 是否为数组类型
    if (doc.HasParseError() || !doc.IsArray())
    {
        log("get json data err!");
        return false;
    }
    //从第2行开始，因为第一行是属性
    for(unsigned int i=1;i<doc.Size();i++)
    {
        //逐个提取数组元素（声明的变量必须为引用）
        rapidjson::Value &v=doc[i];
        
        int id;//ID
        string name;//名称
        int hp;//血量
        int Defense;//防御力
//        int attack;//攻击力
//        int passable;//是否可穿透（通行）
        
        //按下标提取
        int a=0;
        id=v[a++].GetInt();
        name=v[a++].GetString();
        hp=v[a++].GetInt();
        Defense=v[a++].GetInt();
//        attack=v[a++].GetInt();
        if (v[a].IsArray())
        {
            for (int i = 0; i < v[a].Capacity(); i ++)
            {
                CCLOG("%d" ,v[a][i].GetInt());
            }
        }
        
        CCLOG("ID:%d,Name:%s,Blood:%d,Atrack:%d",
            id,name.c_str(),hp,Defense);
    }
    
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    DataCenter::getInstance()->initMapInfo(1);
    Director::getInstance()->replaceScene(GameUILayer::gameScene());
}

void HelloWorld::menuTimeLimit(Ref *pSender)
{
    DataCenter::getInstance()->setTimeLimit(true);
    DataCenter::getInstance()->initMapInfo(2);
    Director::getInstance()->replaceScene(GameUILayer::gameScene());
}

void HelloWorld::menuAddShader(cocos2d::Ref *pSender)
{
    m_iTimes++;
    if(this->getChildByTag(567))
    {
        Node *node = this->getChildByTag(567);
        GLProgram * p = GLProgram::createWithFilenames("bright.vsh", "bright.fsh");
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
        p->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
        p->link();
        p->updateUniforms();
        node->setGLProgram(p);
    }

}

void HelloWorld::menuAnimation(cocos2d::Ref *pSender)
{
    m_iTimes++;
    
    Armature *armature1 = (Armature*)this->getChildByTag(111);
    // 播放动画
    armature1->getAnimation()->playWithIndex(m_iTimes%4);
    
    Armature *armature2 = (Armature*)this->getChildByTag(222);
    // 播放动画
    armature2->getAnimation()->playWithIndex(m_iTimes%4);
    
    Armature *armature3 = (Armature*)this->getChildByTag(333);
    // 播放动画
    armature3->getAnimation()->playWithIndex(m_iTimes%4);
    
    Armature *armature4 = (Armature*)this->getChildByTag(444);
    // 播放动画
    armature4->getAnimation()->playWithIndex(m_iTimes%4);
    
    Armature *armature5 = (Armature*)this->getChildByTag(555);
    // 播放动画
    armature5->getAnimation()->playWithIndex(m_iTimes%4);
    
    Armature *armature6 = (Armature*)this->getChildByTag(666);
    // 播放动画
    armature6->getAnimation()->playWithIndex(m_iTimes%4);
    
    Armature *armature7 = (Armature*)this->getChildByTag(777);
    // 播放动画
    armature7->getAnimation()->playWithIndex(m_iTimes%4);
    
    Armature *armature8 = (Armature*)this->getChildByTag(888);
    // 播放动画
    armature8->getAnimation()->playWithIndex(m_iTimes%4);
    
    Armature *armature9 = (Armature*)this->getChildByTag(999);
    // 播放动画
    armature9->getAnimation()->playWithIndex(m_iTimes%6);
    
    Armature *armature10 = (Armature*)this->getChildByTag(101);
    // 播放动画
    armature10->getAnimation()->playWithIndex(m_iTimes%5);
}
