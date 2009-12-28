/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Westfall
SD%Complete: 90
SDComment: Quest support: 155, 1651
SDCategory: Westfall
EndScriptData */

/* ContentData
npc_daphne_stilwell
npc_defias_traitor
EndContentData */

#include "precompiled.h"
#include "escort_ai.h"

/*######
## npc_daphne_stilwell
######*/

enum
{
    SAY_DS_START        = -1000293,
    SAY_DS_DOWN_1       = -1000294,
    SAY_DS_DOWN_2       = -1000295,
    SAY_DS_DOWN_3       = -1000296,
    SAY_DS_PROLOGUE     = -1000297,

    SPELL_SHOOT         = 6660,
    QUEST_TOME_VALOR    = 1651,
    NPC_DEFIAS_RAIDER   = 6180,
    EQUIP_ID_RIFLE      = 2511
};

struct MANGOS_DLL_DECL npc_daphne_stilwellAI : public npc_escortAI
{
    npc_daphne_stilwellAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        m_uiWPHolder = 0;
        Reset();
    }

    uint32 m_uiWPHolder;
    uint32 m_uiShootTimer;

    void Reset()
    {
        if (HasEscortState(STATE_ESCORT_ESCORTING))
        {
            switch(m_uiWPHolder)
            {
                case 7: DoScriptText(SAY_DS_DOWN_1, m_creature); break;
                case 8: DoScriptText(SAY_DS_DOWN_2, m_creature); break;
                case 9: DoScriptText(SAY_DS_DOWN_3, m_creature); break;
            }
        }
        else
            m_uiWPHolder = 0;

        m_uiShootTimer = 0;
    }

    void WaypointReached(uint32 uiPoint)
    {
        m_uiWPHolder = uiPoint;

        switch(uiPoint)
        {
            case 4:
                SetEquipmentSlots(false, EQUIP_NO_CHANGE, EQUIP_NO_CHANGE, EQUIP_ID_RIFLE);
                m_creature->SetSheath(SHEATH_STATE_RANGED);
                m_creature->HandleEmoteCommand(EMOTE_STATE_USESTANDING_NOSHEATHE);
                break;
            case 7:
                m_creature->SummonCreature(NPC_DEFIAS_RAIDER, -11450.836, 1569.755, 54.267, 4.230, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                m_creature->SummonCreature(NPC_DEFIAS_RAIDER, -11449.697, 1569.124, 54.421, 4.206, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                m_creature->SummonCreature(NPC_DEFIAS_RAIDER, -11448.237, 1568.307, 54.620, 4.206, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                break;
            case 8:
                m_creature->SetSheath(SHEATH_STATE_RANGED);
                m_creature->SummonCreature(NPC_DEFIAS_RAIDER, -11450.836, 1569.755, 54.267, 4.230, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                m_creature->SummonCreature(NPC_DEFIAS_RAIDER, -11449.697, 1569.124, 54.421, 4.206, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                m_creature->SummonCreature(NPC_DEFIAS_RAIDER, -11448.237, 1568.307, 54.620, 4.206, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                m_creature->SummonCreature(NPC_DEFIAS_RAIDER, -11448.037, 1570.213, 54.961, 4.283, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                break;
            case 9:
                m_creature->SetSheath(SHEATH_STATE_RANGED);
                m_creature->SummonCreature(NPC_DEFIAS_RAIDER, -11450.836, 1569.755, 54.267, 4.230, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                m_creature->SummonCreature(NPC_DEFIAS_RAIDER, -11449.697, 1569.124, 54.421, 4.206, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                m_creature->SummonCreature(NPC_DEFIAS_RAIDER, -11448.237, 1568.307, 54.620, 4.206, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                m_creature->SummonCreature(NPC_DEFIAS_RAIDER, -11448.037, 1570.213, 54.961, 4.283, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                m_creature->SummonCreature(NPC_DEFIAS_RAIDER, -11449.018, 1570.738, 54.828, 4.220, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                break;
            case 10:
                SetRun(false);
                break;
            case 11:
                DoScriptText(SAY_DS_PROLOGUE, m_creature);
                break;
            case 13:
                SetEquipmentSlots(true);
                m_creature->SetSheath(SHEATH_STATE_UNARMED);
                m_creature->HandleEmoteCommand(EMOTE_STATE_USESTANDING_NOSHEATHE);
                break;
            case 17:
                if (Player* pPlayer = GetPlayerForEscort())
                    pPlayer->GroupEventHappens(QUEST_TOME_VALOR, m_creature);
                break;
        }
    }

    void AttackStart(Unit* pWho)
    {
        if (!pWho)
            return;

        if (m_creature->Attack(pWho, false))
        {
            m_creature->AddThreat(pWho);
            m_creature->SetInCombatWith(pWho);
            pWho->SetInCombatWith(m_creature);

            m_creature->GetMotionMaster()->MoveChase(pWho, 30.0f);
        }
    }

    void JustSummoned(Creature* pSummoned)
    {
        pSummoned->AI()->AttackStart(m_creature);
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiShootTimer < uiDiff)
        {
            m_uiShootTimer = 1000;

            if (!m_creature->IsWithinDist(m_creature->getVictim(), ATTACK_DISTANCE))
                DoCast(m_creature->getVictim(), SPELL_SHOOT);

        }
        else
            m_uiShootTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

bool QuestAccept_npc_daphne_stilwell(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_TOME_VALOR)
    {
        DoScriptText(SAY_DS_START, pCreature);

        if (npc_daphne_stilwellAI* pEscortAI = dynamic_cast<npc_daphne_stilwellAI*>(pCreature->AI()))
            pEscortAI->Start(true, true, pPlayer->GetGUID(), pQuest);
    }

    return true;
}

CreatureAI* GetAI_npc_daphne_stilwell(Creature* pCreature)
{
    return new npc_daphne_stilwellAI(pCreature);
}

/*######
## npc_defias_traitor
######*/

#define SAY_START                   -1000101
#define SAY_PROGRESS                -1000102
#define SAY_END                     -1000103
#define SAY_AGGRO_1                 -1000104
#define SAY_AGGRO_2                 -1000105

#define QUEST_DEFIAS_BROTHERHOOD    155

struct MANGOS_DLL_DECL npc_defias_traitorAI : public npc_escortAI
{
    npc_defias_traitorAI(Creature* pCreature) : npc_escortAI(pCreature) { Reset(); }

    void WaypointReached(uint32 i)
    {
        switch (i)
        {
            case 35:
                SetRun(false);
                break;
            case 36:
                if (Player* pPlayer = GetPlayerForEscort())
                    DoScriptText(SAY_PROGRESS, m_creature, pPlayer);
                break;
            case 44:
                if (Player* pPlayer = GetPlayerForEscort())
                {
                    DoScriptText(SAY_END, m_creature, pPlayer);
                    pPlayer->GroupEventHappens(QUEST_DEFIAS_BROTHERHOOD, m_creature);
                }
                break;
        }
    }

    void Aggro(Unit* who)
    {
        DoScriptText(urand(0, 1) ? SAY_AGGRO_1 : SAY_AGGRO_2, m_creature);
    }

    void Reset() { }
};

bool QuestAccept_npc_defias_traitor(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_DEFIAS_BROTHERHOOD)
    {
        DoScriptText(SAY_START, pCreature, pPlayer);

        if (npc_defias_traitorAI* pEscortAI = dynamic_cast<npc_defias_traitorAI*>(pCreature->AI()))
            pEscortAI->Start(true, true, pPlayer->GetGUID(), pQuest);
    }

    return true;
}

CreatureAI* GetAI_npc_defias_traitor(Creature* pCreature)
{
    return new npc_defias_traitorAI(pCreature);
}

void AddSC_westfall()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "npc_daphne_stilwell";
    newscript->GetAI = &GetAI_npc_daphne_stilwell;
    newscript->pQuestAccept = &QuestAccept_npc_daphne_stilwell;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_defias_traitor";
    newscript->GetAI = &GetAI_npc_defias_traitor;
    newscript->pQuestAccept = &QuestAccept_npc_defias_traitor;
    newscript->RegisterSelf();
}
