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
SDName: Boss_Grand_Warlock_Nethekurse
SD%Complete: 75
SDComment: encounter not fully completed. missing part where boss kill minions.
SDCategory: Hellfire Citadel, Shattered Halls
EndScriptData */

/* ContentData
boss_grand_warlock_nethekurse
mob_fel_orc_convert
mob_lesser_shadow_fissure
EndContentData */

#include "precompiled.h"
#include "shattered_halls.h"

struct Say
{
    int32 id;
};

static Say PeonAttacked[]=
{
    {-1540001},
    {-1540002},
    {-1540003},
    {-1540004},
};
static Say PeonDies[]=
{
    {-1540005},
    {-1540006},
    {-1540007},
    {-1540008},
};

#define SAY_INTRO           -1540000
#define SAY_TAUNT_1         -1540009
#define SAY_TAUNT_2         -1540010
#define SAY_TAUNT_3         -1540011
#define SAY_AGGRO_1         -1540012
#define SAY_AGGRO_2         -1540013
#define SAY_AGGRO_3         -1540014
#define SAY_SLAY_1          -1540015
#define SAY_SLAY_2          -1540016
#define SAY_DIE             -1540017

#define SPELL_DEATH_COIL            30500
#define SPELL_DARK_SPIN             30502                   // core bug spell attack caster :D
#define SPELL_SHADOW_FISSURE        30496                   // Summon the ShadowFissure NPC

#define SPELL_SHADOW_CLEAVE         30495
#define H_SPELL_SHADOW_SLAM         35953

#define SPELL_HEMORRHAGE            30478

#define SPELL_CONSUMPTION           30497
#define SPELL_TEMPORARY_VISUAL      39312                   // this is wrong, a temporary solution. spell consumption already has the purple visual, but doesn't display as it should

struct MANGOS_DLL_DECL boss_grand_warlock_nethekurseAI : public ScriptedAI
{
    boss_grand_warlock_nethekurseAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    bool IntroOnce;
    bool IsIntroEvent;
    bool IsMainEvent;
    bool SpinOnce;
    //bool HasTaunted;
    bool Phase;

    uint32 PeonEngagedCount;
    uint32 PeonKilledCount;

    uint32 IntroEvent_Timer;
    uint32 DeathCoil_Timer;
    uint32 ShadowFissure_Timer;
    uint32 Cleave_Timer;

    void Reset()
    {
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

        IsIntroEvent = false;
        IntroOnce = false;
        IsMainEvent = false;
        //HasTaunted = false;
        SpinOnce = false;
        Phase = false;

        PeonEngagedCount = 0;
        PeonKilledCount = 0;

        IntroEvent_Timer = 90000;                           //how long before getting bored and kills his minions?
        DeathCoil_Timer = 20000;
        ShadowFissure_Timer = 8000;
        Cleave_Timer = 5000;
    }

    void DoYellForPeonAggro()
    {
        if (PeonEngagedCount >= 4)
            return;

        DoScriptText(PeonAttacked[PeonEngagedCount].id, m_creature);
        ++PeonEngagedCount;
    }

    void DoYellForPeonDeath()
    {
        if (PeonKilledCount >= 4)
            return;

        DoScriptText(PeonDies[PeonKilledCount].id, m_creature);
        ++PeonKilledCount;

        if (PeonKilledCount == 4)
        {
            IsIntroEvent = false;
            IsMainEvent = true;
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }
    }

    void DoTauntPeons()
    {
        switch(urand(0, 2))
        {
            case 0: DoScriptText(SAY_TAUNT_1, m_creature); break;
            case 1: DoScriptText(SAY_TAUNT_2, m_creature); break;
            case 2: DoScriptText(SAY_TAUNT_3, m_creature); break;
        }

        //TODO: kill the peons first
        IsIntroEvent = false;
        PeonEngagedCount = 4;
        PeonKilledCount = 4;
        IsMainEvent = true;
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void AttackStart(Unit* who)
    {
        if (IsIntroEvent || !IsMainEvent)
            return;

        if (m_creature->Attack(who, true))
        {
            m_creature->AddThreat(who);
            m_creature->SetInCombatWith(who);
            who->SetInCombatWith(m_creature);

            if (Phase)
                DoStartNoMovement(who);
            else
                DoStartMovement(who);
        }
    }

    void MoveInLineOfSight(Unit *who)
    {
        if (!IntroOnce && m_creature->IsWithinDistInMap(who, 50.0f))
        {
            if (who->GetTypeId() != TYPEID_PLAYER)
                return;

            DoScriptText(SAY_INTRO, m_creature);
            IntroOnce = true;
            IsIntroEvent = true;

            if (m_pInstance)
                m_pInstance->SetData(TYPE_NETHEKURSE,IN_PROGRESS);
        }

        if (IsIntroEvent || !IsMainEvent)
            return;

        ScriptedAI::MoveInLineOfSight(who);
    }

    void Aggro(Unit *who)
    {
        switch(urand(0, 2))
        {
            case 0: DoScriptText(SAY_AGGRO_1, m_creature); break;
            case 1: DoScriptText(SAY_AGGRO_2, m_creature); break;
            case 2: DoScriptText(SAY_AGGRO_3, m_creature); break;
        }
    }

    void JustSummoned(Creature *summoned)
    {
        summoned->setFaction(16);
        summoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        summoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

        //triggered spell of consumption does not properly show it's SpellVisual, wrong spellid?
        summoned->CastSpell(summoned,SPELL_TEMPORARY_VISUAL,true);
        summoned->CastSpell(summoned,SPELL_CONSUMPTION,false,0,0,m_creature->GetGUID());
    }

    void KilledUnit(Unit* victim)
    {
        DoScriptText(urand(0, 1) ? SAY_SLAY_1 : SAY_SLAY_2, m_creature);
    }

    void JustDied(Unit* Killer)
    {
        DoScriptText(SAY_DIE, m_creature);

        if (!m_pInstance)
            return;

        m_pInstance->SetData(TYPE_NETHEKURSE,DONE);

        if (m_pInstance->GetData64(DATA_NETHEKURSE_DOOR))
        {
            if (GameObject* pDoor = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(DATA_NETHEKURSE_DOOR)))
                pDoor->SetGoState(GO_STATE_ACTIVE);
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (IsIntroEvent)
        {
            if (!m_pInstance)
                return;

            if (m_pInstance->GetData(TYPE_NETHEKURSE) == IN_PROGRESS)
            {
                if (IntroEvent_Timer < diff)
                {
                    DoTauntPeons();
                }else IntroEvent_Timer -= diff;
            }
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (!IsMainEvent)
            return;

        if (Phase)
        {
            if (!SpinOnce)
            {
                DoCast(m_creature->getVictim(),SPELL_DARK_SPIN);
                SpinOnce = true;
            }

            if (Cleave_Timer < diff)
            {
                DoCast(m_creature->getVictim(), m_bIsRegularMode ? SPELL_SHADOW_CLEAVE : H_SPELL_SHADOW_SLAM);
                Cleave_Timer = urand(6000, 8500);
            }else Cleave_Timer -= diff;
        }
        else
        {
            if (ShadowFissure_Timer < diff)
            {
                if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM,0))
                    DoCast(target,SPELL_SHADOW_FISSURE);
                ShadowFissure_Timer = urand(7500, 15000);
            }else ShadowFissure_Timer -= diff;

            if (DeathCoil_Timer < diff)
            {
                if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM,0))
                    DoCast(target,SPELL_DEATH_COIL);
                DeathCoil_Timer = urand(15000, 20000);
            }else DeathCoil_Timer -= diff;

            if ((m_creature->GetHealth()*100) / m_creature->GetMaxHealth() <= 20)
                Phase = true;

            DoMeleeAttackIfReady();
        }
    }
};

struct MANGOS_DLL_DECL mob_fel_orc_convertAI : public ScriptedAI
{
    mob_fel_orc_convertAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    uint32 Hemorrhage_Timer;

    void Reset()
    {
        m_creature->SetNoCallAssistance(true);              //we don't want any assistance (WE R HEROZ!)
        Hemorrhage_Timer = 3000;
    }

    void MoveInLineOfSight(Unit *who)
    {
        return;
    }

    void Aggro(Unit* who)
    {
        if (m_pInstance)
        {
            if (m_pInstance->GetData64(DATA_NETHEKURSE))
            {
                Creature *pKurse = (Creature*)Unit::GetUnit(*m_creature, m_pInstance->GetData64(DATA_NETHEKURSE));
                if (pKurse && m_creature->IsWithinDist(pKurse, 45.0f))
                {
                    ((boss_grand_warlock_nethekurseAI*)pKurse->AI())->DoYellForPeonAggro();

                    if (m_pInstance->GetData(TYPE_NETHEKURSE) == IN_PROGRESS)
                        return;
                    else m_pInstance->SetData(TYPE_NETHEKURSE,IN_PROGRESS);
                }
            }
        }
    }

    void JustDied(Unit* Killer)
    {
        if (m_pInstance)
        {
            if (m_pInstance->GetData(TYPE_NETHEKURSE) != IN_PROGRESS)
                return;

            if (m_pInstance->GetData64(DATA_NETHEKURSE))
            {
                Creature *pKurse = (Creature*)Unit::GetUnit(*m_creature, m_pInstance->GetData64(DATA_NETHEKURSE));
                if (pKurse)
                    ((boss_grand_warlock_nethekurseAI*)pKurse->AI())->DoYellForPeonDeath();
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (Hemorrhage_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_HEMORRHAGE);
            Hemorrhage_Timer = 15000;
        }else Hemorrhage_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

//NOTE: this creature are also summoned by other spells, for different creatures
struct MANGOS_DLL_DECL mob_lesser_shadow_fissureAI : public ScriptedAI
{
    mob_lesser_shadow_fissureAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    void Reset() { }
    void MoveInLineOfSight(Unit *who) { }
    void AttackStart(Unit* who) { }
};

CreatureAI* GetAI_boss_grand_warlock_nethekurse(Creature* pCreature)
{
    return new boss_grand_warlock_nethekurseAI(pCreature);
}

CreatureAI* GetAI_mob_fel_orc_convert(Creature* pCreature)
{
    return new mob_fel_orc_convertAI(pCreature);
}

CreatureAI* GetAI_mob_lesser_shadow_fissure(Creature* pCreature)
{
    return new mob_lesser_shadow_fissureAI(pCreature);
}

void AddSC_boss_grand_warlock_nethekurse()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_grand_warlock_nethekurse";
    newscript->GetAI = &GetAI_boss_grand_warlock_nethekurse;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_fel_orc_convert";
    newscript->GetAI = &GetAI_mob_fel_orc_convert;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_lesser_shadow_fissure";
    newscript->GetAI = &GetAI_mob_lesser_shadow_fissure;
    newscript->RegisterSelf();
}
