/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Boss_Alythess
SD%Complete: 75%
SDComment: Touches doesn't work good, some problems with spells (Conflagration damages also Warclock)
EndScriptData */

#include "precompiled.h"
#include "sunwell_plateau.h"

// definitions
// texts
#define YELL_TWINS_AGGRO			-1940001
#define YELL_TWINS_BOTH_DEATH		-1940002
#define YELL_TWINS_SINGLE_DEATH		-1940003
#define YELL_TWINS_ENRAGE			-1940004

#define YELL_TWINS_SPELL_STURMKNOCKBACK	    -1940010 
#define YELL_TWINS_SPELL_STURMKNOCKBACK0	-1940005 
#define YELL_TWINS_SPELL_STURMKNOCKBACK1	-1940006
#define YELL_TWINS_SPELL_STURMKNOCKBACK2	-1940007
#define YELL_TWINS_SPELL_STURMKNOCKBACK3	-1940008
#define YELL_TWINS_SPELL_STURMKNOCKBACK4	-1940009 

#define YELL_ALY_SLAY			             -1941000
#define YELL_TWINS_SPELL_LOHE		         -1941001
#define YELL_TWINS_SPELL_SCHATTENKLINGEN     -1941002

#define YELL_SACRO_SLAY			             -1942000
#define YELL_TWINS_SPELL_SCHATTENNOVA	     -1942001
#define YELL_TWINS_SPELL_VERWIRRENDERS	     -1942002

// spell - enrage
#define SPELL_TWINS_ENRAGE			27680 // enrage

// spells - alythess
#define SPELL_PYROGENICS    		45230 // self cast buff making 35% more dmg from fire
#define SPELL_FLAME_TOUCHED         45348 // debuf doing fire damage over time and stacking to 20
#define SPELL_CONFLAGRATION         45342 // making player burn
#define SPELL_BLAZE                 45235 // fire damage ~5k
#define SPELL_FLAME_SEAR            46771 // fire damage over 6 sec ~8k

// spells - sacrolash
#define SPELL_DARK_TOUCHED    		45347 // debuf doing shadow damage over time and stacking to 20
#define SPELL_SHADOW_BLADES         45248 // shadow damage ~4k
#define SPELL_SHADOW_NOVA           45329 // shadow aoe ~5k
#define SPELL_CONFOUNDING_BLOW      45256 // shadow damage over time and confuse

// npc summoned by sacrolash
#define NPC_SHADOW_IMAGE            25214 // npc spawns by sacrolash
#define SPELL_DARK_STRIKE           45271 // shadow damage ~2k 
#define SPELL_SHADOWFURY            45270 // shadow aoe ~2k stunning all enemies

//############################################
//################## ALYTHESS ################
//############################################

struct MANGOS_DLL_DECL boss_alythessAI : public ScriptedAI
{
    boss_alythessAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((ScriptedInstance*)c->GetInstanceData());
        Reset();
    }

	ScriptedInstance* pInstance;  

	uint32 Pyrogenics_Timer;
	uint32 Flame_Touched_Timer;
	uint32 Conflagration_Timer;
	uint32 Blaze_Timer;
	uint32 Flame_Sear_Timer;
	uint32 Enrage_Timer;
	uint64 TargetGUID[3];
	bool isEnraged;

    void Reset()
		{	
			Pyrogenics_Timer = 100; 
			Flame_Touched_Timer = 30000; 
			Conflagration_Timer = 25000 + rand()%15000;
			Blaze_Timer = 1000; 
			Flame_Sear_Timer = 15000; 
			Enrage_Timer = 120000; 

			isEnraged = false;
		}

	void Aggro(Unit *who)
		{
			DoScriptText(YELL_TWINS_AGGRO, m_creature);
			DoPlaySoundToSet(m_creature, 12484);
		}
	
	void KilledUnit(Unit* victim)
		{
           DoScriptText(YELL_ALY_SLAY, m_creature);
           switch(rand()%3)
           {
            	case 0: DoPlaySoundToSet(m_creature, 12490); break;
            	case 1: DoPlaySoundToSet(m_creature, 12491); break;
            }
		}

	void JustDied(Unit* Killer)
		{
			DoScriptText(YELL_TWINS_SINGLE_DEATH, m_creature);
			DoPlaySoundToSet(m_creature, 12488);
		}

	void UpdateAI(const uint32 diff)
    {       
		
		// return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
			
		// does sacrolash stand and cast spells, after someone is out of range she follows victim
		Unit *who = m_creature->getVictim();
		if(who && who->IsInRange(m_creature, 0.0f, 15.0f, false)){
			m_creature->StopMoving();
		} else {
			m_creature->CanFreeMove();
		}

        // enrage
        if (Enrage_Timer < diff && !isEnraged)
        {
            DoScriptText(YELL_TWINS_ENRAGE, m_creature);
            DoCast(m_creature, SPELL_TWINS_ENRAGE);
            isEnraged = true;
        } else Enrage_Timer -= diff;
		
		// pyrogenics buff
        if (Pyrogenics_Timer < diff)
        {
            DoCast(m_creature, SPELL_PYROGENICS);
            Pyrogenics_Timer = 35000;
        } else Pyrogenics_Timer -= diff;
		
		// flame touched debuff - doesn't work correclty
		/*
		if (Flame_Touched_Timer < diff)
        {
			Unit* victim = SelectUnit(SELECT_TARGET_RANDOM, 0);
			if(victim && (victim->GetTypeId() == TYPEID_PLAYER)) {
				DoCast(victim, SPELL_FLAME_TOUCHED);
			} 
            Flame_Touched_Timer = 30000 + rand()%1000;
        } else Flame_Touched_Timer -= diff;
		*/
		
		// conflagration
        if (Conflagration_Timer < diff)
        {
			if (Unit *victim = SelectUnit(SELECT_TARGET_RANDOM, 0))
                DoCast(victim, SPELL_CONFLAGRATION);
            Conflagration_Timer = 20000 + rand()%1000;
        } else Conflagration_Timer -= diff;
		
		// blaze
        if (Blaze_Timer < diff)
        {
			Unit *victim = m_creature->getVictim();
			if(victim) {
				DoCast(victim, SPELL_BLAZE);
			}
            Blaze_Timer = 5000 + rand()%5000;
        } else Blaze_Timer -= diff;
		
		// flame sear
        if (Flame_Sear_Timer < diff)
        {
			Unit* victim = SelectUnit(SELECT_TARGET_RANDOM, 0);
			if (victim){
				DoCast(victim, SPELL_FLAME_SEAR);
			}
			Unit* victim2 = SelectUnit(SELECT_TARGET_RANDOM, 0);
			if (victim2){
				DoCast(victim2, SPELL_FLAME_SEAR);
			}
			Unit* victim3 = SelectUnit(SELECT_TARGET_RANDOM, 0);
			if (victim3){
				DoCast(victim3, SPELL_FLAME_SEAR);					
			}
            Flame_Sear_Timer = 30000;
        } else Flame_Sear_Timer -= diff;
		
        DoMeleeAttackIfReady();
    }
};

//############################################
//################# SACROLASH ################
//############################################

struct MANGOS_DLL_DECL boss_sacrolashAI : public ScriptedAI
{
    boss_sacrolashAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = ((ScriptedInstance*)c->GetInstanceData());
        Reset();
    }
			
	ScriptedInstance* pInstance;
	
	uint32 Enrage_Timer;
	uint32 Dark_Touched_Timer;
	uint32 Shadow_Nova_Timer;
	uint32 Confounding_Blow_Timer;
	uint32 Shadow_Blades_Timer;
	uint32 Summon_Shadow_Image;
	uint64 TargetGUID[3];
	bool isEnraged;

	void Reset()
	
		{	
			Enrage_Timer = 120000; 
			Dark_Touched_Timer = 30000;
			Shadow_Nova_Timer = 15000;
			Confounding_Blow_Timer = 3000;
			Shadow_Blades_Timer = 10000;
			Summon_Shadow_Image = 30000;
			isEnraged = false;
		}

	void Aggro(Unit *who)
		{
			DoScriptText(YELL_TWINS_AGGRO, m_creature);
		}

	void KilledUnit(Unit* victim)
		{
           DoScriptText(YELL_SACRO_SLAY, m_creature);
		   switch(rand()%2)
           {
            	case 0: DoPlaySoundToSet(m_creature, 12486); break;
            	case 1: DoPlaySoundToSet(m_creature, 12487); break;
           }
		}

	void JustDied(Unit* Killer)
		{
			DoScriptText(YELL_TWINS_SINGLE_DEATH, m_creature);
			DoPlaySoundToSet(m_creature, 12492);
		}

    void UpdateAI(const uint32 diff)
    {
	
        // return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
		
		// enrage
		if (Enrage_Timer < diff && !isEnraged)
        {
            DoScriptText(YELL_TWINS_ENRAGE, m_creature);
            DoCast(m_creature, SPELL_TWINS_ENRAGE);
            isEnraged = true;
        } else Enrage_Timer -= diff;
		
		// dark touched buff - doesn't work correclty
		/*
        if (Dark_Touched_Timer < diff)
        {
			Unit* victim = m_creature->getVictim();
			if (victim && (victim->GetTypeId() == TYPEID_PLAYER)) {
				DoCast(victim, SPELL_DARK_TOUCHED);
			} 
            Dark_Touched_Timer = 30000 + rand()%10000;
        } else Dark_Touched_Timer -= diff;
		*/
		
		// shadow blades
        if (Shadow_Blades_Timer < diff)
        {
			Unit* victim = SelectUnit(SELECT_TARGET_RANDOM, 0);
			if (victim){
				DoCast(victim, SPELL_SHADOW_BLADES);
			}
			Unit* victim2 = SelectUnit(SELECT_TARGET_RANDOM, 0);
			if (victim2){
				DoCast(victim2, SPELL_SHADOW_BLADES);
			}
			Unit* victim3 = SelectUnit(SELECT_TARGET_RANDOM, 0);
			if (victim3){
				DoCast(victim3, SPELL_SHADOW_BLADES);					
			}
            Shadow_Blades_Timer = 10000 + rand()%1000;
        } else Shadow_Blades_Timer -= diff;
		
		// shadow nova
        if (Shadow_Nova_Timer < diff)
        {
            DoCast(m_creature, SPELL_SHADOW_NOVA);
            Shadow_Nova_Timer = 10000 + rand()%2500;
        } else Shadow_Nova_Timer -= diff;
		
		// confounding blow
        if (Confounding_Blow_Timer < diff)
        {
			Unit *victim = m_creature->getVictim();
			if(victim) {
				DoCast(victim, SPELL_CONFOUNDING_BLOW);
			}
            Confounding_Blow_Timer = 20000;
        } else Confounding_Blow_Timer -= diff;
		
		// summon spawns
		if (Summon_Shadow_Image < diff)
        {
			Unit *image = m_creature->SummonCreature(NPC_SHADOW_IMAGE, 0, 0, 0, 0.0,TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 11000);
			if(image) {
				image->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			}
            Summon_Shadow_Image = 30000;
        } else Summon_Shadow_Image -= diff;

        DoMeleeAttackIfReady();
    }
};

//############################################
//############## SHADOW IMAGE ################
//############################################
struct MANGOS_DLL_DECL npc_shadow_imageAI : public ScriptedAI
{
    npc_shadow_imageAI(Creature *c) : ScriptedAI(c)
    {
        Reset();
    }

	ScriptedInstance* pInstance; 
	
	uint32 Dark_Strike_Timer;
	uint32 Shadowfury_Timer;
	uint32 Despawn_Timer;
	
	void Aggro(Unit* target) {
		m_creature->SetInCombatWithZone();
	}
	
    void Reset()
		{	
			Dark_Strike_Timer = 1000;
			Shadowfury_Timer = 7000;
			Despawn_Timer = 8000;
		}
		
	void UpdateAI(const uint32 diff)
    {       	
		// dark strike
	    if (Dark_Strike_Timer < diff)
        {
			Unit *victim = m_creature->getVictim();
            if(victim) {
				DoCast(victim, SPELL_DARK_STRIKE);
			}
            Dark_Strike_Timer = 2000;
        } else Dark_Strike_Timer -= diff;
		
		// shadowfury just before dead
		if (Shadowfury_Timer < diff)
        {
            DoCast(m_creature, SPELL_SHADOWFURY);
			Shadowfury_Timer = 10000;	
        } else Shadowfury_Timer -= diff;

		// forced despawn after 11 sec 			
		if(Despawn_Timer < diff) {
			m_creature->ForcedDespawn(); 
		} else Despawn_Timer -= diff;
		
        DoMeleeAttackIfReady();
    }
};


CreatureAI* GetAI_npc_shadow_image(Creature *_Creature)
{
    return new npc_shadow_imageAI (_Creature);
}

CreatureAI* GetAI_boss_alythess(Creature *_Creature)
{
    return new boss_alythessAI (_Creature);
}

CreatureAI* GetAI_boss_sacrolash(Creature *_Creature)
{
    return new boss_sacrolashAI (_Creature);
}

void AddSC_boss_eredar_twins()
{
    Script *newscript;
	
	newscript = new Script;
    newscript->Name = "npc_shadow_image";
    newscript->GetAI = &GetAI_npc_shadow_image;
    newscript->RegisterSelf();
	
    newscript = new Script;
    newscript->Name = "boss_alythess";
    newscript->GetAI = &GetAI_boss_alythess;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_sacrolash";
    newscript->GetAI = &GetAI_boss_sacrolash;
    newscript->RegisterSelf();
}
