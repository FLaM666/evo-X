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
SDName: Boss_Flamegor
SD%Complete: 100
SDComment:
SDCategory: Blackwing Lair
EndScriptData */

#include "precompiled.h"

enum
{
    EMOTE_GENERIC_FRENZY        = -1000002,

    SPELL_SHADOWFLAME           = 22539,
    SPELL_WINGBUFFET            = 23339,
    SPELL_FRENZY                = 23342                     //This spell periodically triggers fire nova
};

struct MANGOS_DLL_DECL boss_flamegorAI : public ScriptedAI
{
    boss_flamegorAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 ShadowFlame_Timer;
    uint32 WingBuffet_Timer;
    uint32 Frenzy_Timer;

    void Reset()
    {
        ShadowFlame_Timer = 21000;                          //These times are probably wrong
        WingBuffet_Timer = 35000;
        Frenzy_Timer = 10000;
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        //ShadowFlame_Timer
        if (ShadowFlame_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_SHADOWFLAME);
            ShadowFlame_Timer = urand(15000, 22000);
        }else ShadowFlame_Timer -= diff;

        //WingBuffet_Timer
        if (WingBuffet_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_WINGBUFFET);
            if (m_creature->getThreatManager().getThreat(m_creature->getVictim()))
                m_creature->getThreatManager().modifyThreatPercent(m_creature->getVictim(),-75);

            WingBuffet_Timer = 25000;
        }else WingBuffet_Timer -= diff;

        //Frenzy_Timer
        if (Frenzy_Timer < diff)
        {
            DoScriptText(EMOTE_GENERIC_FRENZY, m_creature);
            DoCast(m_creature,SPELL_FRENZY);
            Frenzy_Timer = urand(8000, 1000);
        }else Frenzy_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_boss_flamegor(Creature* pCreature)
{
    return new boss_flamegorAI(pCreature);
}

void AddSC_boss_flamegor()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_flamegor";
    newscript->GetAI = &GetAI_boss_flamegor;
    newscript->RegisterSelf();
}
