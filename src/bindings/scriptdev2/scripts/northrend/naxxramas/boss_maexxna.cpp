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
SDName: Boss_Maexxna
SD%Complete: 60
SDComment: this needs review, and rewrite of the webwrap ability
SDCategory: Naxxramas
EndScriptData */

#include "precompiled.h"
#include "naxxramas.h"

enum
{
    SPELL_WEBWRAP           = 28622,                        //Spell is normally used by the webtrap on the wall NOT by Maexxna

    SPELL_WEBSPRAY          = 29484,
    H_SPELL_WEBSPRAY        = 54125,
    SPELL_POISONSHOCK       = 28741,
    H_SPELL_POISONSHOCK     = 54122,
    SPELL_NECROTICPOISON    = 28776,
    H_SPELL_NECROTICPOISON  = 54121,
    SPELL_FRENZY            = 54123,
    H_SPELL_FRENZY          = 54124,

    //spellId invalid
    SPELL_SUMMON_SPIDERLING = 29434,
    NPC_SPIDERLING          = 17055
};

#define LOC_X1    3546.796
#define LOC_Y1    -3869.082
#define LOC_Z1    296.450

#define LOC_X2    3531.271
#define LOC_Y2    -3847.424
#define LOC_Z2    299.450

#define LOC_X3    3497.067
#define LOC_Y3    -3843.384
#define LOC_Z3    302.384

struct MANGOS_DLL_DECL mob_webwrapAI : public ScriptedAI
{
    mob_webwrapAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint64 m_uiVictimGUID;

    void Reset()
    {
        m_uiVictimGUID = 0;
    }

    void SetVictim(uint64 victim)
    {
        if (victim)
        {
            m_uiVictimGUID = victim;
            if (Unit* pVictim = Unit::GetUnit((*m_creature), m_uiVictimGUID))
                pVictim->CastSpell(pVictim, SPELL_WEBWRAP, true);
        }
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (uiDamage > m_creature->GetHealth())
        {
            if (m_uiVictimGUID)
            {
                if (Unit* pVictim = Unit::GetUnit((*m_creature), m_uiVictimGUID))
                    pVictim->RemoveAurasDueToSpell(SPELL_WEBWRAP);
            }
        }
    }
    void JustDied(Unit* Killer)
    {
        if (Unit* pVictim = Unit::GetUnit((*m_creature), m_uiVictimGUID))
            pVictim->RemoveAurasDueToSpell(SPELL_WEBWRAP);
    }

    void MoveInLineOfSight(Unit* pWho) { }
    void UpdateAI(const uint32 uiDiff) { }
};

struct MANGOS_DLL_DECL boss_maexxnaAI : public ScriptedAI
{
    boss_maexxnaAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsHeroicMode = false;//pCreature->GetMap()->IsRaidOrHeroicDungeon();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsHeroicMode;

    uint32 m_uiWebWrapTimer;
    uint32 m_uiWebSprayTimer;
    uint32 m_uiPoisonShockTimer;
    uint32 m_uiNecroticPoisonTimer;
    uint32 m_uiSummonSpiderlingTimer;
    bool   m_bEnraged;

    void Reset()
    {
        m_uiWebWrapTimer = 20000;                           //20 sec init, 40 sec normal
        m_uiWebSprayTimer = 40000;                          //40 seconds
        m_uiPoisonShockTimer = 20000;                       //20 seconds
        m_uiNecroticPoisonTimer = 30000;                    //30 seconds
        m_uiSummonSpiderlingTimer = 30000;                  //30 sec init, 40 sec normal
        m_bEnraged = false;
    }

    void Aggro(Unit* pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_MAEXXNA, IN_PROGRESS);
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_MAEXXNA, DONE);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_MAEXXNA, FAIL);
    }

   void DoCastWebWrap()
    {
        Unit* pWrapped = NULL;
        for(uint8 i = 0; i < 1; ++i)
        {
            float LocX, LocY, LocZ;
            switch(rand()%3)
            {
                case 0:
                    LocX = LOC_X1 + rand()%5; LocY = LOC_Y1 + rand()%5; LocZ = LOC_Z1 + 1;
                    break;
                case 1:
                    LocX = LOC_X2 + rand()%5; LocY = LOC_Y2 + rand()%5; LocZ = LOC_Z2 + 1;
                    break;
                case 2:
                    LocX = LOC_X3 + rand()%5; LocY = LOC_Y3 + rand()%5; LocZ = LOC_Z3 + 1;
                    break;
            }

            if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,1))
            {
                if (pWrapped)
                    if (pTarget == pWrapped)
                         return;

                DoTeleportPlayer(pTarget, LocX, LocY, LocZ, pTarget->GetOrientation());
                if (Creature* pWrap = m_creature->SummonCreature(16486, LocX, LocY, LocZ, 0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 120000))
                    ((mob_webwrapAI*)pWrap->AI())->SetVictim(pTarget->GetGUID());
                pWrapped = pTarget;
            }
        }
    }
    void SummonSpiderling()
    {
        uint8 number = 9;
        float x,y,z;
        for(uint8 i = 0; number >= i; i++)
        {
            if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
            {
                m_creature->GetRandomPoint(m_creature->GetPositionX(),m_creature->GetPositionY(),m_creature->GetPositionZ(),7.0f,x,y,z);
                if(Creature* spiderling = m_creature->SummonCreature(NPC_SPIDERLING, x, y, z,0, TEMPSUMMON_DEAD_DESPAWN, 0))
                {
                    spiderling->AddThreat(pTarget, 0.0f);
                    spiderling->AI()->AttackStart(pTarget);
                }
            }
        }
    }
    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Web Wrap
        if (m_uiWebWrapTimer < uiDiff)
        {
            DoCastWebWrap();
            m_uiWebWrapTimer = 40000;
        }
        else
            m_uiWebWrapTimer -= uiDiff;

        // Web Spray
        if (m_uiWebSprayTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_WEBSPRAY);
            m_uiWebSprayTimer = 40000;
        }
        else
            m_uiWebSprayTimer -= uiDiff;

        // Poison Shock
        if (m_uiPoisonShockTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_POISONSHOCK);
            m_uiPoisonShockTimer = 20000;
        }
        else
            m_uiPoisonShockTimer -= uiDiff;

        // Necrotic Poison
        if (m_uiNecroticPoisonTimer < uiDiff)
        {
            DoCast(m_creature->getVictim(), SPELL_NECROTICPOISON);
            m_uiNecroticPoisonTimer = 30000;
        }
        else
            m_uiNecroticPoisonTimer -= uiDiff;

        // Summon Spiderling
        if (m_uiSummonSpiderlingTimer < uiDiff)
        {
            SummonSpiderling();
            m_uiSummonSpiderlingTimer = 40000;
        }
        else
            m_uiSummonSpiderlingTimer -= uiDiff;

        //Enrage if not already enraged and below 30%
        if (!m_bEnraged && (m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) < 30)
        {
            DoCast(m_creature, SPELL_FRENZY);
            m_bEnraged = true;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_webwrap(Creature* pCreature)
{
    return new mob_webwrapAI(pCreature);
}

CreatureAI* GetAI_boss_maexxna(Creature* pCreature)
{
    return new boss_maexxnaAI(pCreature);
}

void AddSC_boss_maexxna()
{
    Script* NewScript;

    NewScript = new Script;
    NewScript->Name = "boss_maexxna";
    NewScript->GetAI = &GetAI_boss_maexxna;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_webwrap";
    NewScript->GetAI = &GetAI_mob_webwrap;
    NewScript->RegisterSelf();
}
