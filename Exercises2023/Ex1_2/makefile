CC=g++
FLAGS=-std=c++20 -w
TARGET= AnalyseData
OBJECTS=AnalyseData.o CustomFunctions.o
${TARGET}:${OBJECTS}
	@echo "Linking..."
	${CC} ${FLAGS} ${OBJECTS} -o ${TARGET}
	@make clean

AnalyseData.o : AnalyseData.cpp CustomFunctions.h
	${CC} ${FLAGS} -c AnalyseData.cpp

CustomFunctions.o : CustomFunctions.cpp CustomFunctions.h
	${CC} ${FLAGS} -c CustomFunctions.cpp

clean: 
	@rm -f *.o *~

cleantarget: 
	@rm -f ${TARGET}