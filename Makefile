###############################################################################

ifeq ($(ROOTSYS),)
include /etc/root/Makefile.arch
else
include $(ROOTSYS)/etc/Makefile.arch
endif

###############################################################################

###############################################################################

TESTMACROO    := testMacro.$(ObjSuf) testMacroFactories.$(ObjSuf) PluginService.$(ObjSuf)
TESTMACROS    := testMacro.$(SrcSuf) testMacroFactories.$(SrcSuf) PluginService.$(SrcSuf)
TESTMACROSO   := libTestMacro.$(DllSuf)
MAIN          := testLoading$(ExeSuf)
ifeq ($(PLATFORM),win32)
TESTMACROLIB  := libTestMacro.lib
else
TESTMACROLIB  := $(TESTMACROSO)
endif
TESTMACROMAP  := testMacro.rootmap

EXTRALIBS     := -lReflex -lCintex

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
	$(LD) $(LDFLAGS) $(MAINO) $(ROOTLIBS) $(EXTRALIBS) $(OutPutOpt)$@
	$(MT_EXE)
	@echo "$@ done"

###############################################################################

testMacroFactories.$(SrcSuf) $(TESTMACROMAP): testMacro.cxx
		@echo "Generating dictionary $@..."
		$(RM) $(TESTMACROMAP)
		genreflex $^ --output testMacroFactories.$(SrcSuf) \
		  --selection_file PluginService.xml \
		  --interpreteronly --no_membertypedefs \
		  --rootmap $(TESTMACROMAP) --rootmap-lib $(TESTMACROSO)

clean:
		rm -f *.o *.obj *.res *.pdb *.def *.exp \
		      *.lib *.ilk *.manifest *.d *.def *Factories.* \
		      $(PROGRAMS) $(TESTMACROSO) $(TESTMACROMAP)

distclean:  clean

###############################################################################

.$(SrcSuf).$(ObjSuf):
	$(CXX) $(CXXFLAGS) $(EXTRAFLAGS) -c $<

###############################################################################


