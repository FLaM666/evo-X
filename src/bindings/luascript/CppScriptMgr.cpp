#include "config.h"
#include "CppScriptMgr.h"

uint8 loglevel = 0;
int nrscripts;
Script *m_scripts[MAX_SCRIPTS];

void cppScriptsFree()
{
    for(int i=0;i<nrscripts;i++)
		{
        delete m_scripts[i];
		m_scripts[i]=NULL;
		}
}

void cppScriptsInit()
{
    nrscripts = 0;
    for(int i=0;i<MAX_SCRIPTS;i++)
        m_scripts[i]=NULL;
     cppLoadScripts();
}

Script* GetScriptByName(std::string Name)
{
    for(int i=0;i<MAX_SCRIPTS;i++)
    {
        if( m_scripts[i] && m_scripts[i]->Name == Name )
            return m_scripts[i];
    }
    return NULL;
}

void cppDisableScript(const char* scriptname)
	{
    for(int i=0;i<MAX_SCRIPTS;i++)
    {
        if( m_scripts[i] && ( m_scripts[i]->Name == scriptname ) )
          delete m_scripts[i];
		  m_scripts[i] = NULL;
    }
	}

bool cppGossipHello ( bool& retval, Player * player, Creature *_Creature )
{
    Script *tmpscript = NULL;

    tmpscript = GetScriptByName(_Creature->GetCreatureInfo()->ScriptName);
    if(!tmpscript || !tmpscript->pGossipHello) return false;

    player->PlayerTalkClass->ClearMenus();
    retval = tmpscript->pGossipHello(player,_Creature);
	return true;
}

bool cppGossipSelect( bool& retval, Player *player, Creature *_Creature, const uint32&  sender, const uint32&  action )
{
    Script *tmpscript = NULL;

    tmpscript = GetScriptByName(_Creature->GetCreatureInfo()->ScriptName);
    if(!tmpscript || !tmpscript->pGossipSelect) return false;

    player->PlayerTalkClass->ClearMenus();
    retval = tmpscript->pGossipSelect(player,_Creature,sender,action);
	return true;
}

bool cppGossipSelectWithCode( bool& retval, Player *player, Creature *_Creature, const uint32& sender, const uint32&  action, char* sCode )
{
    Script *tmpscript = NULL;

    tmpscript = GetScriptByName(_Creature->GetCreatureInfo()->ScriptName);
    if(!tmpscript || !tmpscript->pGossipSelectWithCode) return false;

    player->PlayerTalkClass->ClearMenus();
    retval = tmpscript->pGossipSelectWithCode(player,_Creature,sender,action,sCode);
	return true;
}

bool cppQuestAccept( bool& retval, Player *player, Creature *_Creature, Quest *_Quest )
{
    Script *tmpscript = NULL;

    tmpscript = GetScriptByName(_Creature->GetCreatureInfo()->ScriptName);
    if(!tmpscript || !tmpscript->pQuestAccept) return false;

    player->PlayerTalkClass->ClearMenus();
    retval = tmpscript->pQuestAccept(player,_Creature,_Quest);
	return true;
}

bool cppQuestSelect( bool& retval, Player *player, Creature *_Creature, Quest *_Quest )
{
    Script *tmpscript = NULL;

    tmpscript = GetScriptByName(_Creature->GetCreatureInfo()->ScriptName);
    if(!tmpscript || !tmpscript->pQuestSelect) return false;

    player->PlayerTalkClass->ClearMenus();
    retval = tmpscript->pQuestSelect(player,_Creature,_Quest);
	return true;
}

bool cppQuestComplete( bool& retval, Player *player, Creature *_Creature, Quest *_Quest )
{
    Script *tmpscript = NULL;

    tmpscript = GetScriptByName(_Creature->GetCreatureInfo()->ScriptName);
    if(!tmpscript || !tmpscript->pQuestComplete) return false;

    player->PlayerTalkClass->ClearMenus();
    retval = tmpscript->pQuestComplete(player,_Creature,_Quest);
	return true;
}

bool cppChooseReward( bool& retval, Player *player, Creature *_Creature, Quest *_Quest, const uint32& opt )
{
    Script *tmpscript = NULL;

    tmpscript = GetScriptByName(_Creature->GetCreatureInfo()->ScriptName);
    if(!tmpscript || !tmpscript->pChooseReward) return false;

    player->PlayerTalkClass->ClearMenus();
    retval = tmpscript->pChooseReward(player,_Creature,_Quest,opt);
	return true;
}

bool cppNPCDialogStatus( uint32& retval, Player *player, Creature *_Creature )
{
    Script *tmpscript = NULL;

    tmpscript = GetScriptByName(_Creature->GetCreatureInfo()->ScriptName);
    if(!tmpscript || !tmpscript->pNPCDialogStatus) return false;

    player->PlayerTalkClass->ClearMenus();
    retval = tmpscript->pNPCDialogStatus(player,_Creature);
	return true;
}

bool cppItemHello( bool& retval, Player *player, Item *_Item, Quest *_Quest )
{
    Script *tmpscript = NULL;

    tmpscript = GetScriptByName(_Item->GetProto()->ScriptName);
    if(!tmpscript || !tmpscript->pItemHello) return false;

    player->PlayerTalkClass->ClearMenus();
    retval = tmpscript->pItemHello(player,_Item,_Quest);
	return true;
}

bool cppItemQuestAccept( bool& retval, Player *player, Item *_Item, Quest *_Quest )
{
    Script *tmpscript = NULL;

    tmpscript = GetScriptByName(_Item->GetProto()->ScriptName);
    if(!tmpscript || !tmpscript->pItemQuestAccept) return false;

    player->PlayerTalkClass->ClearMenus();
    retval = tmpscript->pItemQuestAccept(player,_Item,_Quest);
	return true;
}

bool cppGOHello( bool& retval, Player *player, GameObject *_GO )
{
    Script *tmpscript = NULL;

    tmpscript = GetScriptByName(_GO->GetGOInfo()->ScriptName);
    if(!tmpscript || !tmpscript->pGOHello) return false;

    player->PlayerTalkClass->ClearMenus();
    retval = tmpscript->pGOHello(player,_GO);
	return true;
}

bool cppGOQuestAccept( bool& retval, Player *player, GameObject *_GO, Quest *_Quest )
{
    Script *tmpscript = NULL;

    tmpscript = GetScriptByName(_GO->GetGOInfo()->ScriptName);
    if(!tmpscript || !tmpscript->pGOQuestAccept) return false;

    player->PlayerTalkClass->ClearMenus();
    retval = tmpscript->pGOQuestAccept(player,_GO,_Quest);
	return true;
}

bool cppGOChooseReward( bool& retval, Player *player, GameObject *_GO, Quest *_Quest, const uint32& opt )
{
    Script *tmpscript = NULL;

    tmpscript = GetScriptByName(_GO->GetGOInfo()->ScriptName);
    if(!tmpscript || !tmpscript->pGOChooseReward) return false;

    player->PlayerTalkClass->ClearMenus();
    retval = tmpscript->pGOChooseReward(player,_GO,_Quest,opt);
	return true;
}
