--[[  Mango.Scripts, made by SinnerG

	License:
		This program is free software; you can redistribute it and/or
		modify it under the terms of the GNU General Public License
		as published by the Free Software Foundation; either version 2
		of the License, or (at your option) any later version.

		This program is distributed in the hope that it will be useful,
		but WITHOUT ANY WARRANTY; without even the implied warranty of
		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
		GNU General Public License for more details.

		You should have received a copy of the GNU General Public License
		along with this program(see GLP.txt); if not, write to the Free Software
		Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
--]]

printf("LuaScript: Loading Mango Scripts library...\n")
-- Mango Scripts Library (Frontend actually)

Mango.Scripts = {
	Base = {};
	Create = function (scriptname)
		return Mango.Scripts.Base.Create(scriptname)
	end;

}

-- The Scripts Base
Mango.Scripts.Base = {
	m_instances = {};
	m_forcelua = false;
	m_active = false;

	new = function (scriptname)
		return setmetatable( {m_scriptname = scriptname}, Mango.Scripts.BaseClass)
	end;

	Create = function (scriptname)
		return Mango.Scripts.Base.new(scriptname)
	end;

	ClearInstances = function ()
		Mango.Scripts.Base.m_instances = {};
	end;

	Activate = function (self)
		self.m_active = true;
		-- If m_forcelua is true, disable CPP usage (NOTE: Not possible to switch back to the CPP version!)
		if (self.m_forcelua) then
			self.m_forcelua = false;
			DisableCppScript(self.m_scriptname);
		end;
		-- Publish the script
		m_scripts[self.m_scriptname] = {}
		m_scripts[self.m_scriptname]["GossipHello"] 		= self.GossipHello;
		m_scripts[self.m_scriptname]["GossipSelect"]		= self.GossipSelect;
		m_scripts[self.m_scriptname]["GossipSelectWithCode"] 	= self.GossipSelectWithCode;
		m_scripts[self.m_scriptname]["QuestAccept"] 		= self.QuestAccept;
		m_scripts[self.m_scriptname]["QuestSelect"] 		= self.QuestSelect;
		m_scripts[self.m_scriptname]["QuestComplete"] 		= self.QuestComplete;
		m_scripts[self.m_scriptname]["ChooseReward"] 		= self.ChooseReward;
		m_scripts[self.m_scriptname]["NPCDialogStatus"] 	= self.NPCDialogStatus;
	end;

	Deactive = function (self)
		self.m_active = false;
		-- Deactivate the script
		m_scripts[self.m_scriptname] = {}
	end;

	IsActive = function(self)
		return self.m_active;
	end;

	GetScriptName = function(self)
		return self.m_scriptname;
	end;

	-- Force LUA usage instead of CPP (if valid)
	ForceLUA = function (self)
		self.m_forcelua = true;
	end;

	-- Default functions
	UnhandledEvent = function (...)
		return RETURN_NOK
	end;

	UnhandledEvent_NPCDialogStatus = function (...)
		return(128)
	end;

	-- The function variables
	GossipHello 		= UnhandledEvent;
	GossipSelect		= UnhandledEvent;
	GossipSelectWithCode	= UnhandledEvent;
	QuestAccept			= UnhandledEvent;
	QuestSelect			= UnhandledEvent;
	QuestComplete		= UnhandledEvent;
	ChooseReward		= UnhandledEvent;
	NPCDialogStatus		= UnhandledEvent_NPCDialogStatus;
}

-- Create the class
Mango.Scripts.BaseClass = Class(Mango.Scripts.Base)
printf("LuaScript: Loaded Mango Scripts library!\n")
