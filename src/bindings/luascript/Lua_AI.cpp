
#include "Lua_AI.h"
#include "Player.h"
#include "GameObject.h"
#include "SharedDefines.h"
#include "GossipDef.h"
#include "QuestDef.h"
#include "WorldSession.h"
#include "CreatureAI.h"
#include "TargetedMovementGenerator.h"
#include "ScriptMgr.h"
#include "Common.h"
#include "Creature.h"

typedef std::map<uint32,LuaAI*> Lua_Ai_Register_type;
Lua_Ai_Register_type Lua_Ai_Register;

extern lua_State *LuaVM;

int lb_Export_AI(lua_State* L)
	{
	using namespace luabind;
module(L)
[
	class_<LuaAI_Proxy>("LuaAI")
	.def("GetCreature", &LuaAI_Proxy::GetCreature)
	.def("ChangeState", &LuaAI_Proxy::ChangeState)
	.def("SetCurrentState", &LuaAI_Proxy::SetCurrentState)
	.def("CurrentState", &LuaAI_Proxy::CurrentState)
	.def("DoStartAttack", &LuaAI_Proxy::DoStartAttack)
	.def("DoStopAttack", &LuaAI_Proxy::DoStopAttack)
	.def("DoCast", &LuaAI_Proxy::DoCast)
	.def("DoSay", &LuaAI_Proxy::DoSay)
	.def("Data", &LuaAI_Proxy::Data)
	.def("SetData", &LuaAI_Proxy::SetData)
	.def("MoveInLineOfSight_agr", &LuaAI_Proxy::MoveInLineOfSight_agr)
	.def("needToStop_agr", &LuaAI_Proxy::needToStop_agr)
	.def("IsVisible_agr", &LuaAI_Proxy::IsVisible_agr)
	.def("SetUpdateInterval", &LuaAI_Proxy::SetUpdateInterval)
];

	return 0;
	}

bool IsValidLuaAIState(const luabind::adl::object& ob)
	{
	if(!ob.is_valid()) return false;
	if(! (luabind::type(ob) == LUA_TTABLE) ) return false;

	luabind::adl::object tobj = ob["Enter"];
	if(! (luabind::type(tobj) == LUA_TFUNCTION) ) return false;

	tobj = ob["Exit"];
	if(! (luabind::type(tobj) == LUA_TFUNCTION) ) return false;

	tobj = ob["Init"];
	if(! (luabind::type(tobj) == LUA_TFUNCTION) ) return false;


	return true;
	}

LuaAI::LuaAI(Creature* creature)
	: m_creature(creature),UpdateInterval(0),currTime(0)
    {
	m_proxy = new LuaAI_Proxy(this);
	register_LuaAI(this);
	}

LuaAI::~LuaAI()
	{
	ML_TRY
	using namespace luabind;
	object ob = this->m_CurrentState["DeInit"];

	if( type(ob) == LUA_TFUNCTION )
		call_function<void>(ob,boost::ref<LuaAI_Proxy>(*(this->m_proxy))  );
	ML_CATCH

	delete m_proxy;
	unregister_LuaAI(this);
	}

void LuaAI::Reload()
	{
		//we are going to set currient state to invalid object
		luabind::object ob;
		this->m_CurrentState = ob;

		if( luabind::call_function<int>(LuaVM, "HasAI" , boost::ref<Creature>(*(this->m_creature)) ) == 0 )
		{
		error_log("[LUA] script has AI , but now dont have !!!! : %s , your server may crash ",m_creature->GetCreatureInfo()->ScriptName);
		return;
		}

    luabind::adl::object start_state = luabind::call_function<luabind::adl::object>(LuaVM,
																				                                                                   "GetAI" ,
																																			        boost::ref<Creature>(*(this->m_creature))
																																			       );

	if( !IsValidLuaAIState(start_state) ) error_log("[LUA] script is not valid , however will be loaded : %s",m_creature->GetCreatureInfo()->ScriptName);
    this->SetCurrentState(start_state);

	ob = start_state["Init"];

    if( !luabind::call_function<bool>(ob, boost::ref<LuaAI_Proxy>(*(this->m_proxy)) ) )
		error_log("[LUA] : AI : creature returned false on Init function ,but will be loaded however ,try to restart the server if you want proper behaviour : %s ",m_creature->GetCreatureInfo()->ScriptName);

	}

void LuaAI::UpdateAI(const uint32 diff)
{
ML_TRY
if( this->m_creature->getDeathState() == DEAD ) return;

//this is for calling "Update" func in lua , you can change the update interval 
//id UpdateInterval is 0 then "Update" wont be called at all
if( UpdateInterval != 0 )
	{
if(this->currTime > this->UpdateInterval )
	{
UpdateScriptedStateMachine();
currTime -= UpdateInterval;
	}
else currTime += diff;
	}


    if( m_creature->getVictim() != NULL )
    {
        if( needToStop() )
        {
            DoStopAttack();
        }
        else if( m_creature->IsStopped() )
        {
            if( m_creature->isAttackReady() )
            {
                if(!m_creature->canReachWithAttack(m_creature->getVictim()))
                    return;
                m_creature->AttackerStateUpdate(m_creature->getVictim());
                m_creature->resetAttackTimer();

                if ( !m_creature->getVictim() )
                    return;

                if( needToStop() )
                    DoStopAttack();
            }
        }
    }

ML_CATCH
}

void LuaAI::DoStartAttack(Unit* victim)
{
    //this is for mele attacks only
    m_creature->Attack(victim);
    (*m_creature)->Mutate(new TargetedMovementGenerator(*victim));

	 if(victim->HasStealthAura())
         victim->RemoveSpellsCausingAura(SPELL_AURA_MOD_STEALTH);

	 if (victim->GetTypeId() == TYPEID_PLAYER)
        m_creature->SetLootRecipient((Player*)victim);
}

void LuaAI::DoStopAttack()
{
    if( m_creature->getVictim() != NULL )
    {
        m_creature->AttackStop();
    }
    // Remove TargetedMovementGenerator from MotionMaster stack list, and add HomeMovementGenerator instead
    if( ( *m_creature )->top()->GetMovementGeneratorType() == TARGETED_MOTION_TYPE )
       ( *m_creature )->TargetedHome();
}

void LuaAI::DoGoHome()
{
    if( !m_creature->getVictim() && m_creature->isAlive() )
	{
        (*m_creature)->TargetedHome();
	}
}

void LuaAI::SetCurrentState(const luabind::object& s)
{
		if( ( !s.is_valid() ) || !(luabind::type(s) == LUA_TTABLE ) )
			{
			PRINT_LUA_OBJECT_ERROR;
			return;
			}
		m_CurrentState = s;
}

void LuaAI::UpdateScriptedStateMachine()
{

    //make sure the state is valid before calling its Execute "method"
    if (m_CurrentState.is_valid())
    {
	    luabind::adl::object ob = m_CurrentState["Update"];
		if( luabind::type(ob) == LUA_TFUNCTION )
	        luabind::call_function<void>(ob,boost::ref<LuaAI_Proxy>(*(this->m_proxy)));
		else PRINT_LUA_OBJECT_ERROR;

	}
	else PRINT_LUA_OBJECT_ERROR;
}

void LuaAI::ChangeState(const luabind::object& new_state)
{

    if( !m_CurrentState.is_valid() || !new_state.is_valid() ) { PRINT_LUA_OBJECT_ERROR; return; }
     //TODO fix here , we need stronger check if code is correct
    //call the Exit method of the existing state
    luabind::object ob = m_CurrentState["Exit"];
	if(ob.is_valid())
	        luabind::call_function<void>(ob,boost::ref<LuaAI_Proxy>(*(this->m_proxy)));
	else PRINT_LUA_OBJECT_ERROR;

    //change state to the new state
    m_CurrentState = new_state;

    //call the Entry method of the new state
    ob = m_CurrentState["Enter"];
	if(ob.is_valid())
	        luabind::call_function<void>(ob,boost::ref<LuaAI_Proxy>(*(this->m_proxy)));
	else PRINT_LUA_OBJECT_ERROR;
}

//These are the callbacks that will be exported to lua
void LuaAI::MoveInLineOfSight(Unit * u)
    {
	ML_TRY
	if(m_creature->isDead() ) return;

	using namespace luabind;
	object ob = this->m_CurrentState["MoveInLineOfSight"];

	if( type(ob) == LUA_TFUNCTION )
		call_function<void>(ob,boost::ref<LuaAI_Proxy>(*(this->m_proxy)),boost::ref<Unit>(*u) );
	ML_CATCH
	}

void LuaAI::AttackStart(Unit * u)
    {
	ML_TRY
	using namespace luabind;
	object ob = this->m_CurrentState["AttackStart"];

	if( type(ob) == LUA_TFUNCTION )
		call_function<void>(ob,boost::ref<LuaAI_Proxy>(*(this->m_proxy)),boost::ref<Unit>(*u) );

	ML_CATCH
	}

void LuaAI::AttackStop(Unit * u)
	{
	ML_TRY
	using namespace luabind;
	object ob = this->m_CurrentState["AttackStop"];

	if( type(ob) == LUA_TFUNCTION )
		call_function<void>(ob,boost::ref<LuaAI_Proxy>(*(this->m_proxy)),boost::ref<Unit>(*u) );
	else this->AttackStop_default(u);
	ML_CATCH
	}

void LuaAI::AttackStop_default(Unit *)
   {
    if( m_creature->isAlive() )
        DoGoHome();
   }

void LuaAI::HealBy(Unit *healer, uint32 amount_healed)
    {
	//not implemented in core , while reading comments
	}

void LuaAI::DamageInflict(Unit *done_by, uint32 amount_damage)
    {
	ML_TRY
	using namespace luabind;
	object ob = this->m_CurrentState["DamageInflict"];

	if( type(ob) == LUA_TFUNCTION )
		call_function<void>(ob,boost::ref<LuaAI_Proxy>(*(this->m_proxy)),boost::ref<Unit>(*done_by),amount_damage );
	ML_CATCH
	}

bool LuaAI::IsVisible(Unit *who) const
		{
	ML_TRY
	using namespace luabind;
	object ob = this->m_CurrentState["IsVisible"];

	if( type(ob) == LUA_TFUNCTION )
		return call_function<bool>(ob,boost::ref<LuaAI_Proxy>(*(this->m_proxy)),boost::ref<Unit>(*who) );
	else return this->IsVisible_default(who);
	ML_CATCH
	return false;// control value , in case of exception
		}

bool LuaAI::needToStop() const
	{
	ML_TRY
	using namespace luabind;
	object ob = this->m_CurrentState["needToStop"];

	if( type(ob) == LUA_TFUNCTION )
		return call_function<bool>(ob,boost::ref<LuaAI_Proxy>(*(this->m_proxy)) );
	else return this->needToStop_default();
	ML_CATCH
	return true;// control value , in case of exception
	}

bool LuaAI::needToStop_default() const
{
    //TODO check m_creature->getVictim() if is not good , may return NULL ??
    return ( !m_creature->getVictim()->isTargetableForAttack() || !m_creature->isAlive() );
}

luabind::object& LuaAI::Data()
	{
	return this->m_data;
	}

void LuaAI::SetData(const luabind::object& data)
	{
	//no check if data is valid
	this->m_data = data;
	}

//Lua registration form

void register_LuaAI(LuaAI* ai)
	{
	Lua_Ai_Register[ ai->m_creature->GetGUIDLow() ] = ai;
	}

void load_AllAIs()
	{
	if(Lua_Ai_Register.empty() ) return;

    Lua_Ai_Register_type::iterator iter;
	for( iter = Lua_Ai_Register.begin() ; iter != Lua_Ai_Register.end() ; iter++ )
		{
		iter->second->Reload();
		}
	}

void unload_ALLAIs()
	{
	//invalid object :)
	luabind::object ob;

	if(Lua_Ai_Register.empty() ) return;

    Lua_Ai_Register_type::iterator iter;
	for( iter = Lua_Ai_Register.begin() ; iter != Lua_Ai_Register.end() ; iter++ )
		{
		iter->second->SetInvalid(ob);
		iter->second->SetData(ob);
		}
	}

void unregister_LuaAI(LuaAI* ai)
	{
    Lua_Ai_Register_type::iterator iter = Lua_Ai_Register.find(ai->m_creature->GetGUIDLow());
	if( iter != Lua_Ai_Register.end() ) Lua_Ai_Register.erase(iter);
	}

bool isRegistered_LuaAI(Creature* cr)
	{
    Lua_Ai_Register_type::iterator iter = Lua_Ai_Register.find(cr->GetGUIDLow());
    return ( iter != Lua_Ai_Register.end() );
	}

//LuaAI Proxy ,used for passing to lua
void LuaAI_Proxy::MoveInLineOfSight_agr(Unit* u)
	{
    if( !m_ai->m_creature->getVictim() && u->isTargetableForAttack() && m_ai->IsVisible(u) && u->isInAccessablePlaceFor(m_ai->m_creature))
		{
        float attackRadius = m_ai->m_creature->GetAttackDistance(u);
        if(m_ai->m_creature->IsWithinDist(u, attackRadius) && m_ai->m_creature->GetDistanceZ(u) <= CREATURE_Z_ATTACK_RANGE)
			{
            if( m_ai->m_creature->IsHostileTo( u ) )
				{
                m_ai->AttackStart(u);
                if(u->HasStealthAura())
                    u->RemoveSpellsCausingAura(SPELL_AURA_MOD_STEALTH);
				}
			}
		}
	}

bool LuaAI_Proxy::needToStop_agr()
	{
    if( !m_ai->m_creature->isAlive() || !m_ai->m_creature->getVictim() || !m_ai->m_creature->getVictim()->isTargetableForAttack() )
        return true;

    if(!m_ai->m_creature->getVictim()->isInAccessablePlaceFor(m_ai->m_creature))
        return true;

    float rx,ry,rz;
    m_ai->m_creature->GetRespawnCoord(rx, ry, rz);
    float spawndist=m_ai->m_creature->GetDistanceSq(rx,ry,rz);
    float length = m_ai->m_creature->GetDistanceSq(m_ai->m_creature->getVictim());
    float hostillen=m_ai->m_creature->GetHostilityDistance( m_ai->m_creature->getVictim()->GetGUID() );
    return (( length > (10.0f + hostillen) * (10.0f + hostillen) && spawndist > 6400.0f )
        || ( length > (20.0f + hostillen) * (20.0f + hostillen) && spawndist > 2500.0f )
        || ( length > (30.0f + hostillen) * (30.0f + hostillen) ));
	}

bool LuaAI_Proxy::IsVisible_agr(Unit *pl)
{
    bool seestealth = true;
    uint32 sight = VISIBLE_RANGE;
    float dist = m_ai->m_creature->GetDistanceSq(pl);
    if(pl->HasStealthAura())
    {
        int32 seevaluse;
        int notfront = m_ai->m_creature->isInFront(pl, sight) ? 0 : 1;
        seevaluse = 5  + m_ai->m_creature->getLevel() * 5 + m_ai->m_creature->m_detectStealth - pl->m_stealthvalue - (uint32)sqrt(dist/100) - 50 * notfront;
        if(seevaluse<0)
            seestealth = false;
        else if(seevaluse>=( rand()%30 ) )
            seestealth = true;
        else seestealth = false;
    }
                                                            // offset=1.0
    return seestealth && (dist * 1.0 <= sight) ;
}



