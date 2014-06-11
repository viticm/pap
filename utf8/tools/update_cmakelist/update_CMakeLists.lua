require('ReadVcproj')

function  update_CMakeList(cmakefile, vcprog, include_path)
  local strNewContent = ""
  local f = io.open(cmakefile, "r")
  local filecontent = f:read("*all")
  local len = string.len(filecontent)
  local bpos1, bpos2= string.find(filecontent, '##update_begin')
  local strBeginText = string.sub(filecontent, 1, bpos2 + 1 );
  local strMakeFile = get_vcproj_cmake(vcprog, include_path)
  local epos = string.find(filecontent, '##update_end')
  local strEndText = string.sub(filecontent, epos - 1 );
  f:close()
  strNewContent = strBeginText .. '\n\n' .. strMakeFile .. '\n\n' ..strEndText
  local wf = io.open(cmakefile, "w")
  wf:write(strNewContent)
  wf:close()
end

local odbc_include_path = "/usr/local/unixODBC/include"
update_CMakeList(
    "../../src/server/sharememory/src/CMakeLists.txt", 
    "../../src/server/sharememory/scripts/sharememory.vc9.vcproj")

update_CMakeList(
    "../../src/server/billing/src/CMakeLists.txt", 
    "../../src/server/billing/scripts/billing.vc9.vcproj")
--[[
update_CMakeList("../../lib/common/vnet/src/CMakeLists.txt", 
                 "../../lib/common/vnet/scripts/vnet.vc9.vcproj")
]]--
