
#ifndef LUA_AI_H
#define LUA_AI_H

#include "Player.h"
#include "GameObject.h"
#include "SharedDefines.h"
#include "GossipDef.h"
#include "QuestDef.h"
#include "WorldSession.h"
#include "CreatureAI.h"
#include "luainc.h"
#include "Creature.h"

//Here is big mess .... need to fixup the mess a little

//goind to implement FSM , as it is faster and easyer for exporting to scripting.

#define PRINT_LUA_OBJECT_ERROR error_log("Invalid object in Lua AI system in %s #i" __FILE__ , __LINE__ )

int lb_Export_AI(lua_State* L);

bool IsValidLuaAIState(const luabind::adl::object& ob);

#define VISIBLE_RANGE (26.46f)

class LuaAI_Proxy;

class MANGOS_DLL_DECL LuaAI : public CreatureAI
  {
  private:
    luabind::object m_CurrentState;
	luabind::object m_data;

	uint32 UpdateInterval;
	uint32 currTime;

  public:
    Creature* m_creature;
	LuaAI_Proxy* m_proxy;

    LuaAI(Creature* creature);
    virtual ~LuaAI();

	luabind::object& Data();
	void SetData(const luabind::object& data);
     
    void Reload();

    void SetCurrentState(const luabind::object& s);

	void SetInvalid(const luabind::object& s) { m_CurrentState = s; }

    inline void SetUpdateInterval(const uint32& time) { UpdateInterval = time; currTime = 0; }

	Creature* GetCreature() { return m_creature; }
    //this method makes sure the current state object is valid before calling
    // the Execute function of the Lua table it represents
    void UpdateScriptedStateMachine();

    //change to a new state
    void ChangeState(const luabind::object& new_state);

    //retrieve the current state
    const luabind::object& CurrentState()const   { return m_CurrentState; }

    // Called if IsVisible(Unit *who) is true at each *who move
    void MoveInLineOfSight(Unit * u);

    // Called at each attack of m_creature by any victim
    void AttackStart(Unit * u);

    // Called at stoping attack by any attacker
    void AttackStop(Unit * u);

    void AttackStop_default(Unit *);

    // Called at any heal cast/item used (call non implemented in mangos)
    void HealBy(Unit *healer, uint32 amount_healed);

    // Called at any Damage from any attacker
    void DamageInflict(Unit *done_by, uint32 amount_damage);

    // Is unit visibale for MoveInLineOfSight
	bool IsVisible(Unit *who) const;
    bool IsVisible_default(Unit *who) const
      {
       return !who->HasStealthAura() && m_creature->GetDistanceSq(who) <= VISIBLE_RANGE;
      }

    // Called at World update tick
    void UpdateAI(const uint32);

    // Check condition for attack stop
    virtual bool needToStop() const;
    bool needToStop_default() const;
    //= Some useful helpers =========================

    // Start attack of victim and go to him
    void DoStartAttack(Unit* victim);

    // Stop attack of current victim
    void DoStopAttack();

    // Cast spell
    void DoCast(Unit* victim, uint32 spelId)
    {
	  m_creature->StopMoving();
      m_creature->CastSpell(victim,spelId,true);
    }

    void DoCastSpell(Unit* who,SpellEntry *spellInfo)
    {
      m_creature->CastSpell(who,spellInfo,true);
    }

    void DoSay(char const* text, uint32 language)
    {
      m_creature->MonsterSay(text,language, m_creature->GetGUID());
    }

    void DoGoHome();

  };

class LuaAI_Proxy
	{
	public:
	LuaAI_Proxy(LuaAI* ai) :m_ai(ai)  { }
	~LuaAI_Proxy() { }

    void SetUpdateInterval(const uint32& time) {m_ai->SetUpdateInterval(time); }

    const luabind::object& Data(void) { return this->m_ai->Data(); }
    void SetData(const luabind::object& data) { this->m_ai->SetData(data); }

    inline void SetCurrentState(const luabind::object& s) { m_ai->SetCurrentState(s); }

    inline void ChangeState(const luabind::object& new_state) { m_ai->ChangeState(new_state); }

    inline const luabind::object& CurrentState()const { return m_ai->CurrentState(); }
 
    inline Creature* GetCreature() { return m_ai->m_creature; }
    
    inline void DoStartAttack(Unit* victim)  { m_ai->DoStartAttack(victim); }
 
    inline void DoStopAttack() { m_ai->DoStopAttack(); }

    inline void DoCast(Unit* victim, uint32 spelId)
    {
	m_ai->m_creature->CastSpell(victim,spelId,true);
    }
    
    inline void DoSay(char const* text, uint32 language)
    {
     m_ai->m_creature->MonsterSay(text,language, m_ai->m_creature->GetGUID());
    }
    
    void MoveInLineOfSight_agr(Unit* u);
	bool needToStop_agr();
	bool IsVisible_agr(Unit *pl);

	private:
	LuaAI* m_ai;
	};

void register_LuaAI(LuaAI* ai);
void unregister_LuaAI(LuaAI* ai);
void load_AllAIs();
void unload_ALLAIs();
bool isRegistered_LuaAI(Creature* cr);

#endif //LUA_AI_H
