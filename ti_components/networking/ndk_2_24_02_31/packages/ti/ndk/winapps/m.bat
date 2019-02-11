REM "c:\Program Files\Microsoft Visual Studio .NET 2003\Vc7\bin\vcvars32.bat"

cl echoc.c wsock32.lib ws2_32
cl send.c wsock32.lib ws2_32
cl recv.c wsock32.lib ws2_32
cl testudp.c wsock32.lib ws2_32
cl helloWorld.c wsock32.lib ws2_32
cl sndpkt.c wsock32.lib ws2_32

del *.obj

