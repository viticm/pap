@echo off
title rename lib for visual studio(pap)
color 02
cls
echo select your need change model.
echo (1)all (2)vnet (3)vengine
set /p select=your select?
echo revert to standard?
set revert=-1
set /p revert=(yes/no)?
set all="vnet vengine"
if 1 == %select% echo "php ../php/vcbuild.php" %all% %revert%
if 2 == %select% php ../php/vcbuild.php "vnet" %revert%
if 3 == %select% php ../php/vcbuild.php "vengine" %revert%
pause