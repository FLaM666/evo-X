printf("LuaScript: Loading Mango IO library...\n")
-- Mango Input/Output Library
Mango.IO = {
	printf  = function (...)
		io.write(string.format(unpack(arg)));
	end;
	print  = function (...)
		io.write(string.format(unpack(arg)));
	end;
	log = function (...)
		log_debug(string.format(unpack(arg)));
	end;
	logerror = function (...)
		log_error(string.format(unpack(arg)));
	end;
}
printf("LuaScript: Loaded Mango IO library!\n")