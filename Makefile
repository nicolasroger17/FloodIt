CXX = g++
CXXFLAGS = -Wall -MMD
GRAPH = -lX11
EXEC = flood-graphical
OBJECTS = flood.o cell.o textdisplay.o grid.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${GRAPH}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
