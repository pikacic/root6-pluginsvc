###############################################################################

ifeq ($(ROOTSYS),)
include /etc/root/Makefile.arch
else
include $(ROOTSYS)/etc/Makefile.arch
endif

###############################################################################

###############################################################################

TESTMACROO    := testMacro.$(ObjSuf) testMacroDict.$(ObjSuf) PluginService.$(ObjSuf)
TESTMACROS    := testMacro.$(SrcSuf) testMacroDict.$(SrcSuf) PluginService.$(SrcSuf)
TESTMACROSO   := libTestMacro.$(DllSuf)
MAIN          := testLoading$(ExeSuf)
ifeq ($(PLATFORM),win32)
TESTMACROLIB  := libTestMacro.lib
else
TESTMACROLIB  := $(TESTMACROSO)
endif
TESTMACROMAP  := testMacro.rootmap

MAINO          = testLoading.$(ObjSuf) PluginService.$(ObjSuf)
MAINS          = testLoading.$(SrcSuf) PluginService.$(SrcSuf)

OBJS           = $(TESTMACROO) $(MAINO)

PROGRAMS       = $(MAIN)

###############################################################################

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

all: $(PROGRAMS) $(TESTMACROMAP)

$(TESTMACROSO): $(TESTMACROO)
ifeq ($(PLATFORM),win32)
	bindexplib $* $^ > $*.def
	lib -nologo -MACHINE:IX86 $^ -def:$*.def \
	   $(OutPutOpt)$(TESTMACROLIB)
	$(LD) $(SOFLAGS) $(LDFLAGS) $^ $*.exp $(ROOTLIBS) \
	   $(EXTRALIBS) $(OutPutOpt)$@
	$(MT_DLL)
else
	$(LD) $(SOFLAGS) $(LDFLAGS) $^ $(ROOTLIBS) $(EXTRALIBS) $(OutPutOpt)$@
endif
	@echo "$@ done"

$(MAIN): $(TESTMACROSO) $(MAINO)
	$(LD) $(LDFLAGS) $(MAINO) $(ROOTLIBS) $(OutPutOpt)$@
	$(MT_EXE)
	@echo "$@ done"

###############################################################################

testMacroDict.$(SrcSuf): testMacro.cxx LinkDef.h
		@echo "Generating dictionary $@..."
		rootcint -f $@ -c $^

$(TESTMACROMAP): testMacro.cxx LinkDef.h
		@echo "Generating rootmap file $@..."
		rlibmap -o $@ -l $(TESTMACROSO) -c $^

clean:
		rm -f *.o *.obj *.res *.pdb *.def *.exp \
		      *.lib *.ilk *.manifest *.d *.def *Dict.*

distclean:  clean
		@rm -f $(PROGRAMS) $(TESTMACROSO) $(TESTMACROMAP)

###############################################################################

.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) $(EXTRAFLAGS) -c $<

###############################################################################


