#!/bin/sh
# This installs some basic required setup for building visionsdk
# This is one time setup only.
# This is built on ti baseline and user can add more things depending on user linux OS baseline


cmd="sudo apt-get install ssh corkscrew gawk uname sed u-boot-tools dos2unix dtrx git lib32z1 lib32ncurses5 lib32bz2-1.0 libc6-i386 libc6:i386  libstdc++6:i386 libncurses5:i386 libz1:i386 libc6-dev-i386 device-tree-compiler mono-complete lzop"
echo "--------------------------------------------------------------------------------"
echo "This step will make sure you have the proper host support packages installed"
echo "using the following command: $cmd"
echo
echo "Note! This command requires you to have administrator priviliges (sudo access) "
echo "on your host."
read -p "Press Enter to continue" REPLY

echo
$cmd

