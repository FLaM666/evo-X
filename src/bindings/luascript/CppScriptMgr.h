
#ifndef CPP_SCRIPTS_MGR_H
#define CPP_SCRIPTS_MGR_H

#include "Player.h"
#include "GameObject.h"
#include "SharedDefines.h"
#include "GossipDef.h"
#include "QuestDef.h"
#include "WorldSession.h"
#include "CreatureAI.h"
#include "TargetedMovementGenerator.h"

#define MAX_SCRIPTS 1000

struct Script
{
    Script() :
    pGossipHello(NULL), pQuestAccept(NULL), pGossipSelect(NULL), pGossipSelectWithCode(NULL),
        pQuestSelect(NULL), pQuestComplete(NULL), pNPCDialogStatus(NULL), pChooseReward(NULL),
        pItemHello(NULL), pGOHello(NULL), pAreaTrigger(NULL), pItemQuestAccept(NULL), pGOQuestAccept(NULL),
        pGOChooseReward(NULL), GetAI(NULL)
        {}

    std::string Name;

    // -- Quest/gossip Methods to be scripted --
    bool (*pGossipHello         )(Player *player, Creature *_Creature);
    bool (*pQuestAccept         )(Player *player, Creature *_Creature, Quest *_Quest );
    bool (*pGossipSelect        )(Player *player, Creature *_Creature, uint32 sender, uint32 action );
    bool (*pGossipSelectWithCode)(Player *player, Creature *_Creature, uint32 sender, uint32 action, char* sCode );
    bool (*pQuestSelect         )(Player *player, Creature *_Creature, Quest *_Quest );
    bool (*pQuestComplete       )(Player *player, Creature *_Creature, Quest *_Quest );
    uint32 (*pNPCDialogStatus   )(Player *player, Creature *_Creature );
    bool (*pChooseReward        )(Player *player, Creature *_Creature, Quest *_Quest, uint32 opt );
    bool (*pItemHello           )(Player *player, Item *_Item, Quest *_Quest );
    bool (*pGOHello             )(Player *player, GameObject *_GO );
    bool (*pAreaTrigger         )(Player *player, Quest *_Quest, uint32 triggerID );
    bool (*pItemQuestAccept     )(Player *player, Item *_Item, Quest *_Quest );
    bool (*pGOQuestAccept       )(Player *player, GameObject *_GO, Quest *_Quest );
    bool (*pGOChooseReward      )(Player *player, GameObject *_GO, Quest *_Quest, uint32 opt );

    CreatureAI* (*GetAI)(Creature *_Creature);
    // -----------------------------------------

};

extern int nrscripts;
extern Script *m_scripts[MAX_SCRIPTS];

#define VISIBLE_RANGE (26.46f)

void cppDisableScript(const char* scriptname);

void cppLoadScripts();
void cppScriptsFree();
void cppScriptsInit();

bool cppGossipHello ( bool& retval, Player * player, Creature *_Creature );
bool cppGossipSelect( bool& retval, Player *player, Creature *_Creature, const uint32&  sender, const uint32&  action );
bool cppGossipSelectWithCode( bool& retval, Player *player, Creature *_Creature, const uint32& sender, const uint32&  action, char* sCode );
bool cppQuestAccept( bool& retval, Player *player, Creature *_Creature, Quest *_Quest );
bool cppQuestSelect( bool& retval, Player *player, Creature *_Creature, Quest *_Quest );
bool cppQuestComplete( bool& retval, Player *player, Creature *_Creature, Quest *_Quest );
bool cppChooseReward( bool& retval, Player *player, Creature *_Creature, Quest *_Quest, const uint32& opt );
bool cppNPCDialogStatus( uint32& retval, Player *player, Creature *_Creature );
bool cppItemHello( bool& retval, Player *player, Item *_Item, Quest *_Quest );
bool cppItemQuestAccept( bool& retval, Player *player, Item *_Item, Quest *_Quest );
bool cppGOHello( bool& retval, Player *player, GameObject *_GO );
bool cppGOQuestAccept( bool& retval, Player *player, GameObject *_GO, Quest *_Quest );
bool cppGOChooseReward( bool& retval, Player *player, GameObject *_GO, Quest *_Quest, const uint32& opt );

#endif //CPP_SCRIPTS_MGR_H
