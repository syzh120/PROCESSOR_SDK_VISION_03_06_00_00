This directory has examples for the different platforms. The directory name has the following format <platform_name>_<hostos>_<image_format>.
(e.g DRA7XX_bios_elf : Indicates examples intended for DRA7XX platform with host core running BIOS. (executable binaries will be created in elf format)
     K2G_linux_elf: Indicates examples indended for K2G platform with primary host running linux (executable binaries will be created in elf format)

The examples have been separated into their own stand-alone folders or .zip
files and they can be built independent of the IPC makefiles.  ( But they can be built also using the IPC products make, if the examples are unzipped in place)

Examples if in zip form, can be extracted by using the unzip command. 
Remember to protect wildcard characters from the shell 
(unzip must see the wildcard).

Some examples:

1. From the platform specific folder, unzip or copy all examples to a
destination folder.

% cd DRA7XX_*
% unzip \*.zip -d /home/examples
or if in unzipped form
% cd DRA7XX_*
% cp -r * /home/examples/

2. Optionally, All the examples can be unzipped for a particular platformand built using the makefile in the top level  ipc_<version>/example directory
Make sure to update the ipc_<version>/products.mak with the appropriate path names for xdctools.

Note: The following lines can be skipped if the examples directories are already unzipped.

% cd ipc_<version>/example
% make PLATFORM=<platform_name> HOSTOS=<bios|linux> extract

(e.g) 
% make PLATFORM=66AK2G HOSTOS=bios extract

To build all the examples for a particular platform, execute the following steps.
Make sure to update the ipc_<version>/products.mak with the appropriate path names of dependent components and tools.

% cd ipc_<version>/example
% make PLATFORM=<platform_name> [HOSTOS=<bios|linux>]

(e.g) make PLATFORM=66AK2G
