# $Id: Makefile,v 1.1 2013/03/07 16:26:07 gdimperi Exp $
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)

BINFILES = runTMVA_cutbased.cc #runTMVA_withRho.cc  # runTMVA_depthMax100.cc   #runTMVA_withHoverE.cc # runTMVA.cc  #runTMVA_timing.cc  #

PROGRAMS = $(patsubst %.cc,%,$(BINFILES))


# --- External configuration ---------------------------------
CC         = g++ -Wno-deprecated
CCFLAGS    =  -g 
MFLAGS     = -MM
INCLUDES   =
WORKDIR    = tmp/
LIBDIR     = $(WORKDIR)
OBJDIR=$(WORKDIR)/objects/
# -------------------------------------------------------------

ROOFIT_INCLUDE := $(shell cd $(CMSSW_BASE); scram tool info roofitcore | grep INCLUDE= | sed 's|INCLUDE=||')
ROOFIT_LIBDIR := $(shell cd $(CMSSW_BASE); scram tool info roofitcore | grep LIBDIR= | sed 's|LIBDIR=||')
ROOFIT_LIBS := $(shell cd $(CMSSW_BASE); scram tool info roofitcore | grep LIB= | sed 's|LIB=||')
ROOFIT_LIBS += $(shell cd $(CMSSW_BASE); scram tool info roofit | grep LIB= | sed 's|LIB=||') 


INCLUDES += -I.  -I.. -I$(ROOTSYS)/include  -I$(ROOFIT_INCLUDE)/
ROOTSYS  ?= ERROR_RootSysIsNotDefined

EXTRALIBS  :=  -L$(ROOTSYS)/lib -L$(ROOFIT_LIBDIR)/ -lHtml -lMathCore -lGenVector -lMinuit -lEG -lRooFitCore -lRooFit -lRIO -lTMVA

# CC files excluding the binaries
CCFILES=$(filter-out $(BINFILES),$(wildcard *.cc))

# List of all object files to build
OLIST=$(patsubst %.cc,$(OBJDIR)/%.o,$(CCFILES))

# Implicit rule to compile all classes
$(OBJDIR)/%.o : %.cc
	@echo "Compiling $<"
	@mkdir -p $(OBJDIR)
	@$(CC) $(CCFLAGS) -c $< -o $@ $(INCLUDES)


$(PROGRAMS) : $(OLIST)
	@echo "Linking $@"
	@$(CC) $(CCFLAGS)  $(INCLUDES) $(OLIST) \
	$(ROOTLIBS) $(EXTRALIBS) -o $(WORKDIR)/$@   $(patsubst %,%.cc,$@)

default : runTMVA_cutbased.cc  #runTMVA_timing.cc  #runTMVA_withRho.cc  # runTMVA_depthMax100.cc   #runTMVA_withHoverE.cc # runTMVA.cc  #

all : ${PROGRAMS}

clean:
	rm -Rf $(WORKDIR)/*
	@#rm -f $(LIBFILE)
	@rm -Rf *.o

veryclean:
	rm -Rf $(WORKDIR)

#.PHONY : shlib lib default clean
