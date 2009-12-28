printf("LuaScript: Loading Mango Utils library...\n")
-- Mango Utils Library
Mango.Utils = {}

-- Next functions are used from gpeddler 2
function Mango.Utils.ShallowCopy(fromTable, toTable)
  toTable = toTable or {} -- new table if not given
  local inx = nil
  local val = nil
  repeat
    inx, val = next(fromTable, inx)
    if val then toTable[inx] = val end
    -- print("inx: ", inx, "val: ", val, "\n") -- (useful for debugging)
  until (inx == nil)
  return toTable
end

--
-- Call a function for every permutation of the numeric elements of a table,
-- starting from element <pos> (previous elements are left where they are)
-- Note: this function is destructive: elements are rearranged for efficiency
-- (minimal garbage creation), then replaced in their original position if
-- and when all permutations are done.
--
-- in:
--   t       = table with numeric elements
--   func(t) = function to be called for every permutation,
--             return a true value to exit from permutation loop
--   pos     = (default = 1) first element to be permutated
-- return:   
--   true = exit requested, false/nil = finished normally
--
function Mango.Utils.Permutate(t, func, pos)
  local exitRequest = false
  pos = pos or 1 -- start from element 1 if not given
  local size = table.getn(t)
  if pos == size then
    exitRequest = func(t)
  else
    local i = pos
    while (not exitRequest) and i <= size do
      t[pos], t[i] = t[i], t[pos] -- swap
      exitRequest = Mango.Utils.Permutate(t, func, pos + 1)
      t[pos], t[i] = t[i], t[pos] -- replace
      i = i + 1
    end
  end
  return exitRequest
end

printf("LuaScript: Loaded Mango Utils library!\n")

