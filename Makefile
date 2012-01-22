CPP  = i686-pc-mingw32-g++.exe
CC   = gcc.exe
RES  = 
OBJ  = 3dCube.o 3dDisplayBody.o 3dGravity.o 3dInit.o 3dTree.o 3dUtils.o 3dWorldMain.o InitPlayfield.o MainCosmos.o MathsVector.o $(RES)
LINKOBJ  = 3dCube.o 3dDisplayBody.o 3dGravity.o 3dInit.o 3dTree.o 3dUtils.o 3dWorldMain.o InitPlayfield.o MainCosmos.o MathsVector.o $(RES)
LIBS =  -L"C:\Users\scala\Desktop\Mayhem\mayhem" -lalleg
INCS =   
CXXINCS = -I"C:\cygwin\usr\i686-pc-mingw32\sys-root\mingw\include" -I"allegro442_include"
BIN  = "Cosmos.exe"
CXXFLAGS = $(CXXINCS)  
CFLAGS = $(INCS)

.PHONY: all all-before all-after clean clean-custom

all: all-before "Cosmos.exe" all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "Cosmos.exe" $(LIBS)

3dCube.o: 3dCube.cpp
	$(CPP) -c 3dCube.cpp -o 3dCube.o $(CXXFLAGS)

3dDisplayBody.o: 3dDisplayBody.cpp
	$(CPP) -c 3dDisplayBody.cpp -o 3dDisplayBody.o $(CXXFLAGS)

3dGravity.o: 3dGravity.cpp
	$(CPP) -c 3dGravity.cpp -o 3dGravity.o $(CXXFLAGS)

3dInit.o: 3dInit.cpp
	$(CPP) -c 3dInit.cpp -o 3dInit.o $(CXXFLAGS)

3dTree.o: 3dTree.cpp
	$(CPP) -c 3dTree.cpp -o 3dTree.o $(CXXFLAGS)

3dUtils.o: 3dUtils.cpp
	$(CPP) -c 3dUtils.cpp -o 3dUtils.o $(CXXFLAGS)

3dWorldMain.o: 3dWorldMain.cpp
	$(CPP) -c 3dWorldMain.cpp -o 3dWorldMain.o $(CXXFLAGS)

InitPlayfield.o: InitPlayfield.cpp
	$(CPP) -c InitPlayfield.cpp -o InitPlayfield.o $(CXXFLAGS)

MainCosmos.o: MainCosmos.cpp
	$(CPP) -c MainCosmos.cpp -o MainCosmos.o $(CXXFLAGS)

MathsVector.o: MathsVector.cpp
	$(CPP) -c MathsVector.cpp -o MathsVector.o $(CXXFLAGS)
