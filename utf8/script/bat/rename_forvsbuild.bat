@echo off
title rename for visual studio(pap)

cd ../../src/common/sys/
if exist util.cc ren util.cc sys_util.cc

cd ../../src/server/share_memory/main/
if exit share_memory.cc ren share_memory.cc main_share_memory.cc

pause