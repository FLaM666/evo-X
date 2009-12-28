/* Copyright (pCreature) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Boss_Kalecgos
SD%Complete: 95%
SDComment: PlayAble
SDCategory: Sunwell Plateau
SDAuthot: Scrappy Doo
EndScriptData */

#include "precompiled.h"
#include "sunwell_plateau.h"
#include "WorldPacket.h"
//#include "sc_creature.h"
//#include "sc_instance.h"
#include "GameObject.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"

enum Says
{
    //kalecgos dragon form
    SAY_EVIL_AGGRO                  = -1580000,
    SAY_EVIL_SPELL1                 = -1580001,
    SAY_EVIL_SPELL2                 = -1580002,
    SAY_EVIL_SLAY1                  = -1580003,
    SAY_EVIL_SLAY2                  = -1580004,
    SAY_EVIL_ENRAGE                 = -1580005,

    //kalecgos humanoid form
    SAY_GOOD_AGGRO                  = -1580006,
    SAY_GOOD_NEAR_DEATH             = -1580007,
    SAY_GOOD_NEAR_DEATH2            = -1580008,
    SAY_GOOD_PLRWIN                 = -1580009,

    SAY_SATH_AGGRO                  = -1580010,
    SAY_SATH_DEATH                  = -1580011,
    SAY_SATH_SPELL1                 = -1580012,
    SAY_SATH_SPELL2                 = -1580013,
    SAY_SATH_SLAY1                  = -1580014,
    SAY_SATH_SLAY2                  = -1580015,
    SAY_SATH_ENRAGE                 = -1580016,
};

enum Spells
{
    MOB_KALEC                       = 24891,
    SPECTRAL_REALM                  = 25796,
    NORMAL_REALM                    = 25795,

    /*** Misc ***/
    SPELL_TAIL_LASH                 = 45122,
    SPELL_BANISH                    = 44836,
    SPELL_SPECTRAL_EXHAUSTION       = 44867,
    SPELL_ENRAGE2                   = 26662,

    /*** Kalecgos Dragon****/
    SPELL_SPECTRAL_BLAST            = 44866,
    SPELL_ARCANE_BUFFET             = 45018,
    SPELL_FROST_BREATH              = 44799,
    SPELL_CRAZED_RAGE               = 44806,                // this should be 44807 instead

    /*** Kalecgos Human ***/
    SPELL_REVITALIZE                = 45027,
    SPELL_HEROIC_STRIKE             = 45026,

    /*** Sathrovarr ***/
    SPELL_CORRUPTING_STRIKE         = 45029,
    SPELL_CURSE_OF_BOUNDLESS_AGONY  = 45032,
    SPELL_SHADOW_BOLT_VOLLEY        = 45031,
};

#define    DRAGON_REALM_Z                  53.079
#define    DEMON_REALM_Z                   -74.558
#define    GO_FAILED                       "You are unable to use this currently."

uint32 WildMagic[]= { 44978, 45001, 45002, 45004, 45006, 45010 };

//Wild Magic
class MANGOS_DLL_DECL WildMagicA : public Aura
{
    public:
        WildMagicA(SpellEntry *spellInfo, uint32 eff, int32 *bp, Unit *target, Unit *caster) : Aura(spellInfo, eff, bp, target, caster, NULL)
            {}
};

//KalecgosDragon
struct MANGOS_DLL_DECL boss_kalecgosAI : public ScriptedAI
{
    boss_kalecgosAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint64 NormalGUID;

    uint32 SpectralBlastTimer;
    uint32 TailLashTimer;
    uint32 ArcaneBuffetTimer;
    uint32 FrostBreathTimer;
    uint32 WildMagicTimer;
    uint32 SathrovarrTimer;
    uint32 NextEnrageTimer;

    bool Banished;
    bool Enraged;
    bool Sathrospawnd;
    bool Check;

    void Reset()
    {
       if (m_pInstance)
       {
            m_pInstance->SetData(DATA_KALECGOS_EVENT,NOT_STARTED);
            m_pInstance->SetData(DATA_SATHROVARR_EVENT,NOT_STARTED);
       }      

        SpectralBlastTimer      = 20000+(rand()%5000);
        TailLashTimer           = 25000+rand()%15000;
        ArcaneBuffetTimer       = 8000;
        FrostBreathTimer        = 15000;
        WildMagicTimer          = 10000;
        SathrovarrTimer         = 35000;

        NormalGUID = 0;

        Enraged             = false;
        Sathrospawnd        = false;
        Check               = true;
        Banished            = false;

        if (m_creature->HasAura(SPELL_CRAZED_RAGE))
            m_creature->RemoveAurasDueToSpell(SPELL_CRAZED_RAGE);

        if (m_creature->HasAura(SPELL_BANISH))
            m_creature->RemoveAurasDueToSpell(SPELL_BANISH);
    }

    void Aggro(Unit* who)
    {
        DoScriptText(SAY_EVIL_AGGRO, m_creature);
        if (m_pInstance)
            m_pInstance->SetData(DATA_KALECGOS_EVENT, IN_PROGRESS);

        if (Creature *Normal = m_creature->SummonCreature(NORMAL_REALM, m_creature->GetPositionX(), m_creature->GetPositionY(), DRAGON_REALM_Z, 0, TEMPSUMMON_TIMED_DESPAWN, 1200000))
        {
            NormalGUID = Normal->GetGUID();
        }
    }

    void JustDied(Unit *killer)
    {
        if (m_pInstance)
            m_pInstance->SetData(DATA_KALECGOS_EVENT, DONE);
    }

    void CastWildMagic()
    {
        SpellEntry *spellInfo = (SpellEntry *)GetSpellStore()->LookupEntry(WildMagic[urand(1,6)]);
        if (spellInfo)
            if(Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
        {
                if (target && target->IsWithinDistInMap(m_creature, 50))
                {
                    for(uint32 i=0 ;i<3; ++i)
                    {
                        uint8 eff = spellInfo->Effect[i];
                        if (eff>=TOTAL_SPELL_EFFECTS)
                            continue;
                        target->AddAura(new WildMagicA(spellInfo, i, NULL, target, target));
                    }
                    WildMagicTimer = 19000;
                }else WildMagicTimer = 1000;
        }
    }

    void KilledUnit(Unit* victim)
    {
        switch(rand()%2)
        {
            case 0: DoScriptText(SAY_EVIL_SLAY1, m_creature); break;
            case 1: DoScriptText(SAY_EVIL_SLAY2, m_creature); break;
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_creature->HasAura(SPELL_BANISH))
        {
            if (m_pInstance && m_pInstance->GetData(DATA_KALECGOS_EVENT) == NOT_STARTED)
            {
                m_creature->RemoveAurasDueToSpell(SPELL_BANISH);
                ((boss_kalecgosAI*)m_creature->AI())->Reset();
                m_creature->AI()->EnterEvadeMode();
        }
            return;
        }

        /* Banish at 1% hp working */
        if (((m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) <= 1) && !Banished)
        {
            if (m_pInstance)
                m_pInstance->SetData(DATA_KALECGOS_EVENT, DONE);
            DoCast(m_creature, SPELL_BANISH, true);
            Banished = true;
        }

        //Mising VMAPS workarroud, ANTY BUG :D
        if (Unit* Spectral = Unit::GetUnit(*m_creature, NormalGUID))
            if ((m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) > 1)
                if (!m_creature->IsInRange(Spectral, 0.0f, 50.0f, true))
                {
                    m_creature->GetMap()->CreatureRelocation(m_creature, m_creature->GetPositionX(), m_creature->GetPositionY(), DRAGON_REALM_Z, m_creature->GetOrientation());
                    ((boss_kalecgosAI*)m_creature->AI())->Reset();
                    m_creature->AI()->EnterEvadeMode();
    }

        Unit *who = m_creature->getVictim();
        if(who && !who->IsInRange(m_creature, 0.0f, 50.0f, true))
    {
            m_creature->AddThreat(who, -100000.0f);
            if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 1))
        {
                m_creature->AddThreat(target, 100000.0f);
                m_creature->AI()->AttackStart(target);
        }
    }
        //END 

        //Enrage at 10% both bosses
        if (!Enraged)
        {
            if (m_pInstance && m_pInstance->GetData(DATA_SATHROVARR_EVENT) == SPECIAL)
            {
                if (Unit* pSathrovarr = Unit::GetUnit(*m_creature, m_pInstance->GetData64(DATA_SATHROVARR)))
                {
                    if (pSathrovarr->isAlive())
                        pSathrovarr->CastSpell(pSathrovarr, SPELL_CRAZED_RAGE, true);
                }
                NextEnrageTimer = 10000;
                Enraged = true;
            }

            if ((m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) < 10)
            {
                if (m_pInstance) 
                    m_pInstance->SetData(DATA_SATHROVARR_EVENT,SPECIAL);
                DoCast(m_creature, SPELL_CRAZED_RAGE, true);
                NextEnrageTimer = 10000;
                Enraged = true;
            }
        } 
        else if (NextEnrageTimer < diff)
        {
            DoCast(m_creature, SPELL_CRAZED_RAGE, true);
            NextEnrageTimer = 10000;
        }else NextEnrageTimer -= diff;

        //Simple Spelss
        if (ArcaneBuffetTimer < diff)
            {
            if (rand()%3 == 0 && Sathrospawnd)
            {   
                DoScriptText(SAY_EVIL_SPELL1, m_creature);
            }
            if (m_creature->getVictim())
                DoCast(m_creature->getVictim(), SPELL_ARCANE_BUFFET);
            ArcaneBuffetTimer = 8000;
        }else ArcaneBuffetTimer -= diff;

        if (FrostBreathTimer < diff)
        {
            if (rand()%2 == 0 && Sathrospawnd)
            {
                DoScriptText(SAY_EVIL_SPELL2, m_creature);
            }
            if (m_creature->getVictim())
                DoCast(m_creature->getVictim(), SPELL_FROST_BREATH);
            FrostBreathTimer = 25000;
        }else FrostBreathTimer -= diff;

        if (TailLashTimer < diff)
        {
            if (m_creature->getVictim())
                DoCast(m_creature->getVictim(), SPELL_TAIL_LASH);
            TailLashTimer = 25000+rand()%15000;
        }else TailLashTimer -= diff;

        if (WildMagicTimer < diff)
        {
            CastWildMagic();
        }else WildMagicTimer -= diff;
        //end of simple spells

        DoMeleeAttackIfReady();

        //Teleport To Spectral Realm
        if (SpectralBlastTimer < diff)
        {
            ThreatList const& m_threatlist = m_creature->getThreatManager().getThreatList();
            if (m_threatlist.empty())
            {
                SpectralBlastTimer = 1000;
                return;
            }

            std::list<Unit*> targetList;
            for(ThreatList::const_iterator itr = m_threatlist.begin(); itr!= m_threatlist.end(); ++itr)
                if((*itr)->getTarget() && (*itr)->getTarget()->GetTypeId() == TYPEID_PLAYER && (*itr)->getTarget()->GetGUID() && !(*itr)->getTarget()->HasAura(SPELL_SPECTRAL_EXHAUSTION) && (*itr)->getTarget()->IsInRange(m_creature, 0.0f, 50.0f, true))
                    targetList.push_back((*itr)->getTarget());
            if(targetList.empty())
            {
                SpectralBlastTimer = 1000;
                return;
            }
        
            std::list<Unit*>::iterator i = targetList.begin();
            advance(i, rand()%targetList.size());
            if((*i))
            {
                if(m_pInstance && m_pInstance->GetData(DATA_KALECGOS_EVENT) == SPECIAL)
                {
                    SpectralBlastTimer = 20000+rand()%5000;
                }
                else
        {
                    if (Unit* target = SelectUnit(SELECT_TARGET_TOPAGGRO, 0))
                        if ( target == (*i))
                            return; 

                    m_creature->AddThreat((*i), -100000.0f);
                    (*i)->InterruptNonMeleeSpells(true);
                    (*i)->CastSpell((*i), SPELL_SPECTRAL_BLAST,true);
                    (*i)->CastSpell((*i), SPELL_SPECTRAL_EXHAUSTION,true);
                    ((Player*)(*i))->TeleportTo((*i)->GetMapId(), (*i)->GetPositionX(), (*i)->GetPositionY(), DEMON_REALM_Z, (*i)->GetOrientation());
        }
                SpectralBlastTimer = 20000+rand()%5000;    
            }else SpectralBlastTimer = 1000;                
        }else SpectralBlastTimer -= diff;

        if (SathrovarrTimer < diff && !Sathrospawnd)
        {
            if (Creature* Sath = ((Creature*)Unit::GetUnit(*m_creature, m_pInstance->GetData64(DATA_SATHROVARR))))
            {
                Sath->SetVisibility(VISIBILITY_ON);
                Sath->setFaction(14);
                Sathrospawnd = true;
                if(Sath) Sath->AI()->AttackStart(m_creature->getVictim());
            }
        }else SathrovarrTimer -= diff;
    }
};

//Sathrovar
struct MANGOS_DLL_DECL boss_sathrovarrAI : public ScriptedAI
{
    boss_sathrovarrAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        KalecGUID = 0;
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint64 KalecGUID;
    uint64 SpectralGUID;

    uint32 CorruptingStrikeTimer;
    uint32 CurseOfBoundlessAgonyTimer;
    uint32 ShadowBoltVolleyTimer;
    uint32 CheckTimer;
    uint32 NextEnrageTimer;

    bool Banished;
    bool Enraged;
    bool Check;

    void Reset()
    {
       if (m_pInstance)
       {
            m_pInstance->SetData(DATA_KALECGOS_EVENT,NOT_STARTED);
            m_pInstance->SetData(DATA_SATHROVARR_EVENT,NOT_STARTED);
       }

        CorruptingStrikeTimer = 13000;
        CurseOfBoundlessAgonyTimer = 15000;
        ShadowBoltVolleyTimer = 7000 + rand()%3 * 1000;
        CheckTimer = 2000;

        Banished            = false;
        Enraged             = false;
        Check               = true;

        KalecGUID = 0;
        SpectralGUID =0;

        TeleportAllPlayersBack();

        if (m_creature->HasAura(SPELL_CRAZED_RAGE))
            m_creature->RemoveAurasDueToSpell(SPELL_CRAZED_RAGE);

        if (m_creature->HasAura(SPELL_BANISH))
            m_creature->RemoveAurasDueToSpell(SPELL_BANISH);
    }

    void Aggro(Unit* who)
    {
        DoScriptText(SAY_SATH_AGGRO, m_creature);

        if (Creature *Kalec = m_creature->SummonCreature(MOB_KALEC, m_creature->GetPositionX() + 10, m_creature->GetPositionY() + 5, m_creature->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 100))
        {
            KalecGUID = Kalec->GetGUID();
            m_creature->AI()->AttackStart(Kalec);
            m_creature->AddThreat(Kalec, 1000000.0f);
        }

        if (Creature *Spectral = m_creature->SummonCreature(SPECTRAL_REALM, m_creature->GetPositionX(), m_creature->GetPositionY(), DEMON_REALM_Z, 0, TEMPSUMMON_TIMED_DESPAWN, 1200000))
        {
            SpectralGUID = Spectral->GetGUID();
        }
    }

    void JustDied(Unit *killer)
    {
        DoScriptText(SAY_SATH_DEATH, m_creature);   
    }

    void TeleportAllPlayersBack()
    {
        std::list<HostileReference *> t_list = m_creature->getThreatManager().getThreatList();
        for(std::list<HostileReference *>::iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
        {
            Unit *target = Unit::GetUnit(*m_creature, (*itr)->getUnitGuid());
            if (target && target->GetTypeId() == TYPEID_PLAYER)
            {
                target->InterruptNonMeleeSpells(true);
                target->CastSpell(target,SPELL_SPECTRAL_EXHAUSTION, true);
                ((Player*)target)->TeleportTo(target->GetMapId(), target->GetPositionX(), target->GetPositionY(), DRAGON_REALM_Z, target->GetOrientation());
            }
        }
    }

    void KilledUnit(Unit* victim)
    {
        switch(rand()%2)
        {
            case 0: DoScriptText(SAY_SATH_SLAY1, m_creature); break;
            case 1: DoScriptText(SAY_SATH_SLAY2, m_creature); break;
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
                return;

        if (m_creature->HasAura(SPELL_BANISH))
        {
            if (CheckTimer < diff)
            {
                TeleportAllPlayersBack();
                CheckTimer = 30000;
            }
            else CheckTimer -= diff;

            if (m_pInstance && m_pInstance->GetData(DATA_KALECGOS_EVENT) == DONE)
                m_creature->RemoveAurasDueToSpell(SPELL_BANISH);
            else if (m_pInstance && m_pInstance->GetData(DATA_KALECGOS_EVENT) == NOT_STARTED)
            {
                m_creature->RemoveAurasDueToSpell(SPELL_BANISH);
                m_creature->GetMap()->CreatureRelocation(m_creature, m_creature->GetPositionX(), m_creature->GetPositionY(), DEMON_REALM_Z, m_creature->GetOrientation());
                ((boss_sathrovarrAI*)m_creature->AI())->Reset();
                m_creature->AI()->EnterEvadeMode();
            }

            return;
        }

        if (!Banished)
            if (Unit* Spectral = Unit::GetUnit(*m_creature, SpectralGUID))
                if ((m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) > 1)
                    if (!m_creature->IsInRange(Spectral, 0.0f, 50.0f, true))
                    {
                        m_creature->GetMap()->CreatureRelocation(m_creature, m_creature->GetPositionX(), m_creature->GetPositionY(), DEMON_REALM_Z, m_creature->GetOrientation());
                        ((boss_sathrovarrAI*)m_creature->AI())->Reset();
                        m_creature->AI()->EnterEvadeMode();
                    }

        //If high Aggro teleported to normal realm attack Kalec or  next target
        Unit *who = m_creature->getVictim();
        if(who && !who->IsInRange(m_creature, 0.0f, 50.0f, true))
        {
            m_creature->AddThreat(who, -100000.0f);
            if(Unit* Kalec = Unit::GetUnit(*m_creature, KalecGUID))
            {
                m_creature->AI()->AttackStart(Kalec);
                m_creature->AddThreat(Kalec, 100000.0f);
            }
            else if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 1))
            {
                m_creature->AddThreat(target, 100000.0f);
                m_creature->AI()->AttackStart(target);
            }
        } 

        if (Unit* Kalec = Unit::GetUnit(*m_creature, KalecGUID))
            if (!Kalec->isAlive())
            {
                TeleportAllPlayersBack();
                if ((boss_sathrovarrAI*)m_creature->AI())
                {
                    ((boss_sathrovarrAI*)m_creature->AI())->Reset();
                    m_creature->AI()->EnterEvadeMode();
                    m_creature->GetMotionMaster()->MoveTargetedHome(); 
                }
            }

        // Banish at 1% hp working
        if (((m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) < 1) && !Banished)
        {
            //Stop  Kalecgos portal creation if not banished
            if (m_pInstance && m_pInstance->GetData(DATA_KALECGOS_EVENT) != DONE)
                m_pInstance->SetData(DATA_KALECGOS_EVENT, SPECIAL);

            TeleportAllPlayersBack();
            m_creature->GetMap()->CreatureRelocation(m_creature, m_creature->GetPositionX(), m_creature->GetPositionY(), DRAGON_REALM_Z, m_creature->GetOrientation());
            DoCast(m_creature, SPELL_BANISH, true);
            Banished = true;
        } 

        //Enrage
        if (!Enraged)
        {         
            if (m_pInstance && m_pInstance->GetData(DATA_SATHROVARR_EVENT) == SPECIAL)
            {
                DoScriptText(SAY_SATH_ENRAGE, m_creature);
                DoCast(m_creature, SPELL_CRAZED_RAGE, true);
                NextEnrageTimer = 10000;
                Enraged = true;
            }

            if ((m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) < 10)
            {
                if (m_pInstance) 
                    m_pInstance->SetData(DATA_SATHROVARR_EVENT,SPECIAL);
                DoScriptText(SAY_SATH_ENRAGE, m_creature);
                DoCast(m_creature, SPELL_CRAZED_RAGE, true);
                NextEnrageTimer = 10000;
                Enraged = true;
            }
        } 
        else if (NextEnrageTimer < diff)
        {
            DoCast(m_creature, SPELL_CRAZED_RAGE, true);
            NextEnrageTimer = 10000;
        }else NextEnrageTimer -= diff;

        if (CorruptingStrikeTimer < diff)
        {
            if (rand()%2 == 0)
            {    
                DoScriptText(SAY_SATH_SPELL2, m_creature);
            }
            if (Unit* victim = m_creature->getVictim())
                DoCast(victim, SPELL_CORRUPTING_STRIKE);
            CorruptingStrikeTimer = 13000;
        }else CorruptingStrikeTimer -= diff;

        if (CurseOfBoundlessAgonyTimer < diff)
        {
            if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                DoCast(target, SPELL_CURSE_OF_BOUNDLESS_AGONY);
            CurseOfBoundlessAgonyTimer = 20000;
        }else CurseOfBoundlessAgonyTimer -= diff;

        if (ShadowBoltVolleyTimer < diff)
        {
            if (rand()%2 == 0)
            {    
                DoScriptText(SAY_SATH_SPELL1, m_creature);
            }
            if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                DoCast(target, SPELL_SHADOW_BOLT_VOLLEY,true);
            ShadowBoltVolleyTimer = 15000;
        }else ShadowBoltVolleyTimer -= diff;

        //Remove Arcane Bufet in spectral Realm and Teleport Players back to normal if Exhaution ends.
        if (CheckTimer < diff)
        {
            std::list<HostileReference *> t_list = m_creature->getThreatManager().getThreatList();
            for(std::list<HostileReference *>::iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
            {
                Unit *target = Unit::GetUnit(*m_creature, (*itr)->getUnitGuid());
                if (target && target->GetTypeId() == TYPEID_PLAYER && m_creature->IsWithinDistInMap(target, 40))              
                {
                    if (target->HasAura(SPELL_ARCANE_BUFFET))
                        target->RemoveAurasDueToSpell(SPELL_ARCANE_BUFFET);

                    if (!target->HasAura(SPELL_SPECTRAL_EXHAUSTION))
                    {
                        //remove target from threat  list
                        m_creature->AddThreat(target, -100000.0f);
                        target->InterruptNonMeleeSpells(true);
                        target->CastSpell(target,SPELL_SPECTRAL_EXHAUSTION, true);
                        ((Player*)target)->TeleportTo(target->GetMapId(), target->GetPositionX(), target->GetPositionY(), DRAGON_REALM_Z, target->GetOrientation());
                    }
                }
            }
            CheckTimer = 3000;
        }CheckTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

//KalecgosHuman
struct MANGOS_DLL_DECL boss_kalecAI : public ScriptedAI
{
    boss_kalecAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        SathGUID = 0;
        Reset();
    }

    ScriptedInstance *m_pInstance;

    uint32 RevitalizeTimer;
    uint32 HeroicStrikeTimer;
    uint32 YellTimer;
    uint32 YellSequence;

    bool SathDied;

    uint64 SathGUID;

    void Reset()
    {
        RevitalizeTimer = 5000;
        HeroicStrikeTimer = 3000;
        YellTimer = 5000;
        YellSequence = 0;

        SathDied = false;

        if (m_pInstance)
            SathGUID = m_pInstance->GetData64(DATA_SATHROVARR);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (YellTimer < diff)
        {
            switch(YellSequence)
            {
            case 0:
                DoScriptText(SAY_GOOD_AGGRO, m_creature);
                YellSequence++;
                break;
            case 1:
                if ((m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) < 50) 
                {
                    DoScriptText(SAY_GOOD_NEAR_DEATH, m_creature);
                    YellSequence++;
                }
                break;
            case 2:
                if ((m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) < 10) 
                {
                    DoScriptText(SAY_GOOD_NEAR_DEATH2, m_creature);
                    YellSequence++;
                }
                break;
            default:
                break;
            }
            YellTimer = 5000;
        }

        if (!SathDied)
            if (Unit* Sath = Unit::GetUnit(*m_creature, SathGUID))
                if (Sath && !Sath->isAlive())
                {
                    DoScriptText(SAY_GOOD_PLRWIN, m_creature);
                    SathDied = true;
                }

        if (RevitalizeTimer < diff)
        {
            DoCast(m_creature, SPELL_REVITALIZE, true);
            RevitalizeTimer = 4000;
        }else RevitalizeTimer -= diff;

        if (HeroicStrikeTimer < diff)
        {
            if (m_creature->getVictim())
            DoCast(m_creature->getVictim(), SPELL_HEROIC_STRIKE);
            HeroicStrikeTimer = 2000;
        }else HeroicStrikeTimer -= diff;

        DoMeleeAttackIfReady();
        }
};

//Spectral Realm Rift
bool GOkalecgos_teleporter(Player* pPlayer, GameObject* pGo)
{
    //In theory, each portal can be used by up to 10 players before it expires (pCreature) wowwiki
    if (pPlayer->HasAura(SPELL_SPECTRAL_EXHAUSTION))
    {
        pPlayer->GetSession()->SendNotification(GO_FAILED);
            return true;
    }
    else
    {
        //Aura excaustion  jako oznacznik czasu spedzonego w  spectral realmie
        pPlayer->InterruptNonMeleeSpells(true);
        pPlayer->CastSpell(pPlayer, SPELL_SPECTRAL_EXHAUSTION, true);
        pPlayer->TeleportTo(pPlayer->GetMapId(), pPlayer->GetPositionX(), pPlayer->GetPositionY(), DEMON_REALM_Z, pPlayer->GetOrientation());
        return false;
    }
}

CreatureAI* GetAI_boss_kalecgos(Creature* pCreature)
{
    return new boss_kalecgosAI(pCreature);
}

CreatureAI* GetAI_boss_sathrovarr(Creature* pCreature)
{
    return new boss_sathrovarrAI(pCreature);
}

CreatureAI* GetAI_boss_kalec(Creature* pCreature)
{
    return new boss_kalecAI(pCreature);
}

void AddSC_boss_kalecgos()
{
    Script* newscript;

    newscript = new Script;
    newscript->GetAI = &GetAI_boss_kalecgos;
    newscript->Name = "boss_kalecgos";
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->GetAI = &GetAI_boss_sathrovarr;
    newscript->Name = "boss_sathrovarr";
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->GetAI = &GetAI_boss_kalec;
    newscript->Name = "boss_kalec";
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="kalecgos_teleporter";
    newscript->pGOHello = &GOkalecgos_teleporter;
    newscript->RegisterSelf();
}
