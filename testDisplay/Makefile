ROOTCONFIG   = root-config
ROOTCFLAGS   = $(shell $(ROOTCONFIG) --cflags)
ROOTLDFLAGS  = $(shell $(ROOTCONFIG) --ldflags)
ROOTLIBS     = $(shell $(ROOTCONFIG) --libs)
ROOTGLIBS    = $(shell $(ROOTCONFIG) --glibs)


#CXXFLAGS  =${ROOTCFLAGS} -Wall
CXXFLAGS  = -O2 -pipe -Wall -W -Woverloaded-virtual $(ROOTCFLAGS) 
CXXLIBS   =${ROOTGLIBS}
#CC        =g++
CC        =clang++

TARGET    =dispGUI
#OBJS      =fframe.o frame.o PixelStream.o frame_view_main.o
#OBJS      =frameView.o frameViewGUI.o classDict.o  
#OBJS      =dispGUI.o classEASIROCSpectrum.o classSpectrumGUI.o classDict.o
OBJS      =dispGUI.o classEASIROCDisplay.o classDict.o

${TARGET} : ${OBJS}
	#${CC} ${CXXLIBS} ${OBJS} -o $@
	${CC} ${CXXLIBS} -lSpectrum ${OBJS} -o $@

.cc.o:
	${CC} ${CXXFLAGS} -c $<

clean:
	rm -f ${OBJS}
	rm -f classDict.cc classDict.h 

classDict.cc : $(HDRS) LinkDef.h
	@echo ----------------------------------
	@echo --- Generating dictionary .... ---
	@echo ----------------------------------
	rootcint -f classDict.cc -c classEASIROCDisplay.h LinkDef.h
