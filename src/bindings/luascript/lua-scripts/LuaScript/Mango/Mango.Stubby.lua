--[[  Mango.Stubby, Based on Stubby 

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

local cleanList
local config = {
	hooks = { functions={}, origFuncs={} },
	calls = { functions={}, callList={} },
	loads = {},
	events = {},
}

-- Function prototypes
local getOrigFunc					-- getOrigFunc(triggerFunction)
local hookCall						-- hookCall(funcName, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20)
local hookInto						-- hookInto(triggerFunction)
local rebuildNotifications			-- rebuildNotifications(notifyItems)
local registerFunctionHook			-- registerFunctionHook(triggerFunction, position, hookFunc, ...)
local unregisterFunctionHook		-- unregisterFunctionHook(triggerFunction, hookFunc)


-- Function definitions

-- This function takes all the items and their requested orders
-- and assigns an actual ordering to them.
function rebuildNotifications(notifyItems)
	local notifyFuncs = {}
	for hookType, hData in notifyItems do
		notifyFuncs[hookType] = {}

		-- Sort all hooks for this type in ascending numerical order.
		local sortedPositions = {}
		for requestedPos,_ in hData do
			table.insert(sortedPositions, requestedPos)
		end
		table.sort(sortedPositions)

		-- Process the sorted request list and insert in correct
		-- order into the call list.
		for _,requestedPos in sortedPositions do
			local func = hData[requestedPos]
			table.insert(notifyFuncs[hookType], func)
		end
	end
	return notifyFuncs
end

-- This function's purpose is to execute all the attached
-- functions in order and the original call at just before
-- position 0.
function hookCall(funcName, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20)
	local result, r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20
	local orig = Mango.Stubby.GetOrigFunc(funcName)
	if (not orig) then return end

	local res;
	local retVal = nil
	local returns = false

	local callees
	if config.calls and config.calls.callList and config.calls.callList[funcName] then
		callees = config.calls.callList[funcName]
	end

	if (callees) then
		for _,func in ipairs(callees) do
			if (orig and func.p >= 0) then
				result, r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20
					= pcall(orig, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20)
				if (result) then
					if r1 or r2 or r3 or r4 or r5 or r6 or r7 or r8 or r9 or r10 or r11 or r12 or r13 or r14 or r15 or r16 or r17 or r18 or r19 or r20 then
						retVal = { r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20 }
						returns = true
					end
				else
					Mango.IO.printf("Error occured while running hooks for: ", tostring(funcName), "\n", r1, "\nCall Chain:\n", debugstack(2, 3, 6))
				end
				orig = nil
			end
			local result, res, addit = pcall(func.f, func.a, retVal, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20);
			if (result) then
				if (type(res) == 'string') then
					if (res == 'abort') then return end
					if (res == 'killorig') then orig = nil end
					if (res == 'setreturn') then
						retVal = addit
						returns = true
					end
					if (res == 'setparams') then
						a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20 = unpack(addit)
					end
				end
			else
				Mango.IO.printf("Error occured while running hooks for: ", tostring(funcName), "\n", res, "\nCall Chain:\n", debugstack(2, 3, 6))
			end
		end
	end
	if (orig) then
		result, r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20
			= pcall(orig, a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20)
		if (result) then
			if r1 or r2 or r3 or r4 or r5 or r6 or r7 or r8 or r9 or r10 or r11 or r12 or r13 or r14 or r15 or r16 or r17 or r18 or r19 or r20 then
				returns = true
			end
		else
			Mango.IO.printf("Error occured while running hooks for: ", tostring(funcName), "\n", r1, "\nCall Chain:\n", debugstack(2, 3, 6))
		end
	end
	if (returns) then
		return r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,r13,r14,r15,r16,r17,r18,r19,r20
	end
end

-- This function automatically hooks Stubby in place of the
-- original function, dynamically.
Stubby_OldFunction = nil
Stubby_NewFunction = nil
function hookInto(triggerFunction)
	if (config.hooks.origFuncs[triggerFunction]) then return end
	RunScript("Stubby_OldFunction = "..triggerFunction)
	RunScript("Stubby_NewFunction = function(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20) return Mango.Stubby.HookCall('"..triggerFunction.."', a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20) end")
	RunScript(triggerFunction.." = Stubby_NewFunction")
	config.hooks.functions[triggerFunction] = Stubby_NewFunction;
	config.hooks.origFuncs[triggerFunction] = Stubby_OldFunction;
	Stubby_NewFunction = nil
	Stubby_OldFunction = nil
end

function getOrigFunc(triggerFunction)
	if (config.hooks) and (config.hooks.origFuncs) then
		return config.hooks.origFuncs[triggerFunction]
	end
end


-- This function causes a given function to be hooked by stubby and
-- configures the hook function to be called at the given position.
-- The original function gets executed a position 0. Use a negative
-- number to get called before the original function, and positive
-- number to get called after the original function. Default position
-- is 200. If someone else is already using your number, you will get
-- automatically moved up for after or down for before. Please also
-- leave space for other people who may need to position their hooks
-- in between your hook and the original.
function registerFunctionHook(triggerFunction, position, hookFunc, ...)
	local insertPos = tonumber(position) or 200
	local funcObj = { f=hookFunc, a=arg, p=position }
	if (table.getn(arg) == 0) then funcObj.a = nil; end

	if (not config.calls) then config.calls = {} end
	if (not config.calls.functions) then config.calls.functions = {} end
	if (config.calls.functions[triggerFunction]) then
		while (config.calls.functions[triggerFunction][insertPos]) do
			if (position >= 0) then
				insertPos = insertPos + 1
			else
				insertPos = insertPos - 1
			end
		end
		config.calls.functions[triggerFunction][insertPos] = funcObj
	else
		config.calls.functions[triggerFunction] = {}
		config.calls.functions[triggerFunction][insertPos] = funcObj
	end
	config.calls.callList = rebuildNotifications(config.calls.functions);
	hookInto(triggerFunction)
end

function unregisterFunctionHook(triggerFunction, hookFunc)
	if not (config.calls and config.calls.functions and config.calls.functions[triggerFunction]) then return end
	for pos, funcObj in config.calls.functions[triggerFunction] do
		if (funcObj and funcObj.f == hookFunc) then
			config.calls.functions[triggerFunction][pos] = nil
		end
	end
end

-- Setup our Stubby global object. All interaction is done
-- via the methods exposed here.
Mango.Stubby = {
	HookCall = hookCall,
	GetOrigFunc = getOrigFunc,
	RegisterFunctionHook = registerFunctionHook,
	UnregisterFunctionHook = unregisterFunctionHook,
}

function testHookStubby()
	Mango.IO.printf("Mango.Stubby Hook test succeeded!\n")
end

function testCallStubby()
	Mango.IO.printf("Testing the Mango.Stubby Hook utility...\n")
end
Mango.Stubby.RegisterFunctionHook("testCallStubby", 1, testHookStubby);
testCallStubby()

