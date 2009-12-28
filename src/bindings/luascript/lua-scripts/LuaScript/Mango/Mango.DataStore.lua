printf("LuaScript: Loading Mango DataStore library...\n")
-- Mango Input/Output Library
Mango.DataStore = {
	m_DataStore = {};

	get = function (...)
		if (Mango.m_DataStore[string.format(unpack(arg))] == nil) then
			Mango.DataStore.m_DataStore[string.format(unpack(arg))] = {};
		end

		return Mango.DataStore.m_DataStore[string.format(unpack(arg))];		
	end;

	clear = function (...)
		Mango.DataStore.m_DataStore[string.format(unpack(arg))] = {};
	end;	
	
}
printf("LuaScript: Loaded Mango DataStore library!\n")