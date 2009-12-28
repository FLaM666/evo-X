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
SDName: Boss_Vaelastrasz
SD%Complete: 75
SDComment: Burning Adrenaline not correctly implemented in core
SDCategory: Blackwing Lair
EndScriptData */

#include "precompiled.h"

#define SAY_LINE1           -1469026
#define SAY_LINE2           -1469027
#define SAY_LINE3           -1469028
#define SAY_HALFLIFE        -1469029
#define SAY_KILLTARGET      -1469030

#define GOSSIP_ITEM         "Start Event <Needs Gossip Text>"

#define SPELL_ESSENCEOFTHERED       23513
#define SPELL_FLAMEBREATH           23461
#define SPELL_FIRENOVA              23462
#define SPELL_TAILSWIPE             15847
#define SPELL_BURNINGADRENALINE     23620
#define SPELL_CLEAVE                20684                   //Chain cleave is most likely named something different and contains a dummy effect

struct MANGOS_DLL_DECL boss_vaelAI : public ScriptedAI
{
    boss_vaelAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        pCreature->setFaction(35);
        pCreature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        Reset();
    }

    uint64 PlayerGUID;
    uint32 SpeachTimer;
    uint32 SpeachNum;
    uint32 Cleave_Timer;
    uint32 FlameBreath_Timer;
    uint32 FireNova_Timer;
    uint32 BurningAdrenalineCaster_Timer;
    uint32 BurningAdrenalineTank_Timer;
    uint32 TailSwipe_Timer;
    bool HasYelled;
    bool DoingSpeach;

    void Reset()
    {
        PlayerGUID = 0;
        SpeachTimer = 0;
        SpeachNum = 0;
        Cleave_Timer = 8000;                                //These times are probably wrong
        FlameBreath_Timer = 11000;
        BurningAdrenalineCaster_Timer = 15000;
        BurningAdrenalineTank_Timer = 45000;
        FireNova_Timer = 5000;
        TailSwipe_Timer = 20000;
        HasYelled = false;
        DoingSpeach = false;
    }

    void BeginSpeach(Unit* target)
    {
        //Stand up and begin speach
        PlayerGUID = target->GetGUID();

        //10 seconds
        DoScriptText(SAY_LINE1, m_creature);

        SpeachTimer = 10000;
        SpeachNum = 0;
        DoingSpeach = true;
    }

    void KilledUnit(Unit *victim)
    {
        if (urand(0, 4))
            return;

        DoScriptText(SAY_KILLTARGET, m_creature, victim);
    }

    void Aggro(Unit* pWho)
    {
        DoCast(m_creature,SPELL_ESSENCEOFTHERED);
        m_creature->SetInCombatWithZone();
    }

    void UpdateAI(const uint32 diff)
    {
        //Speach
        if (DoingSpeach)
        {
            if (SpeachTimer < diff)
            {
                switch (SpeachNum)
                {
                    case 0:
                        //16 seconds till next line
                        DoScriptText(SAY_LINE2, m_creature);
                        SpeachTimer = 16000;
                        ++SpeachNum;
                        break;
                    case 1:
                        //This one is actually 16 seconds but we only go to 10 seconds because he starts attacking after he says "I must fight this!"
                        DoScriptText(SAY_LINE3, m_creature);
                        SpeachTimer = 10000;
                        ++SpeachNum;
                        break;
                    case 2:
                        m_creature->setFaction(103);
                        m_creature->SetHealth(int(m_creature->GetMaxHealth()*.3));
                        if (PlayerGUID && Unit::GetUnit((*m_creature),PlayerGUID))
                        {
                            AttackStart(Unit::GetUnit((*m_creature),PlayerGUID));
                            DoCast(m_creature,SPELL_ESSENCEOFTHERED);
                        }
                        SpeachTimer = 0;
                        DoingSpeach = false;
                        break;
                }
            }else SpeachTimer -= diff;
        }

        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Yell if hp lower than 15%
        if (m_creature->GetHealth()*100 / m_creature->GetMaxHealth() < 15 && !HasYelled)
        {
            DoScriptText(SAY_HALFLIFE, m_creature);
            HasYelled = true;
        }

        //Cleave_Timer
        if (Cleave_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_CLEAVE);
            Cleave_Timer = 15000;
        }else Cleave_Timer -= diff;

        //FlameBreath_Timer
        if (FlameBreath_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_FLAMEBREATH);
            FlameBreath_Timer = urand(4000, 8000);
        }else FlameBreath_Timer -= diff;

        //BurningAdrenalineCaster_Timer
        if (BurningAdrenalineCaster_Timer < diff)
        {
            Unit* target = NULL;

            int i = 0 ;
            while (i < 3)                                   // max 3 tries to get a random target with power_mana
            {
                ++i;
                target = SelectUnit(SELECT_TARGET_RANDOM,1);//not aggro leader
                if (target)
                    if (target->getPowerType() == POWER_MANA)
                        i=3;
            }
            if (target)                                     // cast on self (see below)
                target->CastSpell(target,SPELL_BURNINGADRENALINE,1);

            BurningAdrenalineCaster_Timer = 15000;
        }else BurningAdrenalineCaster_Timer -= diff;

        //BurningAdrenalineTank_Timer
        if (BurningAdrenalineTank_Timer < diff)
        {
            // have the victim cast the spell on himself otherwise the third effect aura will be applied
            // to Vael instead of the player
            m_creature->getVictim()->CastSpell(m_creature->getVictim(),SPELL_BURNINGADRENALINE,1);

            BurningAdrenalineTank_Timer = 45000;
        }else BurningAdrenalineTank_Timer -= diff;

        //FireNova_Timer
        if (FireNova_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_FIRENOVA);
            FireNova_Timer = 5000;
        }else FireNova_Timer -= diff;

        //TailSwipe_Timer
        if (TailSwipe_Timer < diff)
        {
            //Only cast if we are behind
            /*if (!m_creature->HasInArc(M_PI, m_creature->getVictim()))
            {
            DoCast(m_creature->getVictim(),SPELL_TAILSWIPE);
            }*/

            TailSwipe_Timer = 20000;
        }else TailSwipe_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

bool GossipSelect_boss_vael(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)               //Fight time
    {
        pPlayer->CLOSE_GOSSIP_MENU();

        if (boss_vaelAI* pVaelAI = dynamic_cast<boss_vaelAI*>(pCreature->AI()))
            pVaelAI->BeginSpeach((Unit*)pPlayer);
    }

    return true;
}

bool GossipHello_boss_vael(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->SEND_GOSSIP_MENU(907, pCreature->GetGUID());

    return true;
}

CreatureAI* GetAI_boss_vael(Creature* pCreature)
{
    return new boss_vaelAI(pCreature);
}

void AddSC_boss_vael()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_vaelastrasz";
    newscript->GetAI = &GetAI_boss_vael;
    newscript->pGossipHello = &GossipHello_boss_vael;
    newscript->pGossipSelect = &GossipSelect_boss_vael;
    newscript->RegisterSelf();
}
