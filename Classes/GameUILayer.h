//
//  GameUILayer.h
//  Dragon
//
//  Created by B081mac on 15/4/14.
//
//

#ifndef __Dragon__GameUILayer__
#define __Dragon__GameUILayer__

#include <iostream>
#include "cocos2d.h"
#include "DataTools.h"
#include "GameLayer.h"

USING_NS_CC;
using namespace std;

#define COLLECT_ARRAY 3

class GameUILayer : public Layer
{
public:
    
    GameUILayer();
    ~GameUILayer();
    
    static Scene* gameScene();
    
    virtual bool init();
    
    virtual void onEnter();
    
    virtual void onExit();
    
    void initBG();
    
    void initTop();
    
    void initData();
    
    void targetNumAndDisplay(int index,GemType type , int num);
    
    void pauseMenu(Ref* pSender);
    
    void continueGame(Ref* pSender,Node* pNode);
    
    void restarGame(Ref* pSender,Node* pNode);
    
    void quitGame(Ref* pSender);
    
    void resumeGame();
    
    void updateOperationNum(Ref* obj);
    
    void matchOver(Ref* obj);
    
    void updateCollect(Ref* obj);
    
    void failGame();
    
    void limitOperatiomNum();
    
    void limitTime(float dt);
    
    CREATE_FUNC(GameUILayer);
    
private:
    GameLayer *m_pGameLayer;
    
    bool m_bWinGame;
    
    int m_iOperationNum;
    map <GemType , int> m_mapTarget;
    
    LabelAtlas *m_labelOperation;
    LabelAtlas *m_labelScore;
    
    LabelAtlas *m_labelTarget[COLLECT_ARRAY];
    Sprite *m_sprTarget[COLLECT_ARRAY];
    Sprite *m_sprAchieve[COLLECT_ARRAY];
    Armature *m_targetBG;
    bool m_bComplete[COLLECT_ARRAY];  //finished
    
    int m_iArrTargetNum[maxgem];
    int m_iArrTargetIndex[maxgem];
};


#endif /* defined(__Dragon__GameUILayer__) */
