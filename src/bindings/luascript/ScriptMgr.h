/* 
 * Copyright (C) 2005,2006 MaNGOS <http://www.mangosproject.org/>
 *
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

#ifndef SCRIPTMGR_H
#define SCRIPTMGR_H

#include "Player.h"
#include "GameObject.h"
#include "SharedDefines.h"
#include "GossipDef.h"
#include "QuestDef.h"
#include "WorldSession.h"
#include "CreatureAI.h"

#define MAX_SCRIPTS 1000

#define ML_TRY try {
#define ML_CATCH 	} catch(luabind::error& e)  { error_log("[LUA] error/exception : %s , catched at %s %i",e.what() ,__FILE__ , __LINE__ ); } \
	                                           catch(std::runtime_error& e) { error_log("[LUA] error/exception : %s , catched at %s %i",e.what()  ,__FILE__ , __LINE__ ); } \
                                               catch(...) { error_log("[LUA] unhandled error/exception , catched at %s %i ",__FILE__ , __LINE__);}

#endif
