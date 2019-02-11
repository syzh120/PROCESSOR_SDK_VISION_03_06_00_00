SHELL=C:/Windows/System32/cmd.exe

VSDK= ../bin/vsdk_win32.exe

all:
	@echo #
	@echo ### TESTCASE - Error Case - File not present
	@echo #
	$(VSDK) -file tes
	@echo # 

	@echo #
	@echo ### TESTCASE - Correct Case
	@echo #
	$(VSDK) -file test
	@echo #

	@echo #	
	@echo ### TESTCASE - Error Case - Path not provided
	@echo #
	$(VSDK) -file test -path
	@echo #

	@echo #
	@echo ### TESTCASE - Correct Case
	@echo #
	-mkdir output
	$(VSDK) -file -img test -path ./output
	@echo #
	
	@echo #
	@echo ### TESTCASE - Correct Case 
	@echo #
	-mkdir output
	$(VSDK) -file -log test -path ./output
	@echo #

	@echo #
	@echo ### TESTCASE - Error Case - Capture cannot have previous link
	@echo #
	$(VSDK) -file test1
	@echo #

	@echo #
	@echo ### TESTCASE - Error Case - Instances should be named in pattern linkname_string(Capture_1)
	@echo #
	$(VSDK) -file test2
	@echo #
	
	@echo #
	@echo ### TESTCASE - Error Case - Processor Type should be [IPU1_0, IPU1_1, IPU2, A15, DSP1, DSP2, EVE1, EVE2, EVE3, EVE4] 
	@echo #
	$(VSDK) -file test3
	@echo #
	
	@echo #
	@echo ### TESTCASE - Error Case - AvbRx has no input 
	@echo #
	$(VSDK) -file test4
	@echo #
	
	@echo #
	@echo ### TESTCASE - Error Case - Capture cannot have more than two instance 
	@echo #
	$(VSDK) -file test5
	@echo #
	
	@echo #
	@echo ### TESTCASE - Error Case - New Links should be named as DefLink_linkname 
	@echo #
	$(VSDK) -file test6
	@echo #
	
	@echo #
	@echo ### TESTCASE - Warning Case - In case of New Links, LinkID is not assigned  
	@echo #
	$(VSDK) -file test7
	@echo #
	
	@echo #
	@echo ### TESTCASE - Error Case - Same link assigned two different CPU types  
	@echo #
	$(VSDK) -file test8
	@echo #
	
	@echo #
	@echo ### TESTCASE - Error Case - Incorrect CPU given  
	@echo #
	$(VSDK) -file test9
	@echo #
	
clean:
	-rm *.c *.h 
	-rm -rf output
	