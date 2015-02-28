########################################################################
#                          -*- Makefile -*-                            #
########################################################################

COMPILER = g++

########################################################################
## Flags
FLAGS   = -g
LDFLAGS =
PREPRO  = 
DEBUG   = -D DEBUG
OPT     = -O2
WARN    =

### generate directory obj, if not yet existing
$(shell mkdir -p build)

########################################################################
## Paths

WORKINGDIR = $(shell pwd)
PARENTDIR  = $(WORKINGDIR)/..

########################################################################
## search for the files and set paths

vpath %.cpp $(WORKINGDIR)
vpath %.o $(WORKINGDIR)/build
UINCLUDE = $(WORKINGDIR)/include

########################################################################
## Includes
CXX  = $(COMPILER) $(FLAGS) $(OPT) $(WARN) $(DEBUG) $(PREPRO) -I$(UINCLUDE)
INCLUDE = $(wildcard *.h $(UINCLUDE)/*.h)

%.o: %.cpp $(INCLUDE)
	$(CXX) -c -o build/$@ $<

%.o: %.m $(INCLUDE)
	$(CXX) -c -o build/$@ $<


# Libraries
LIB = 

# Frameworks
FRM = -framework SDL -framework SDL_image -framework SDL_ttf -framework SDL_mixer -framework Cocoa

########################################################################
## Linker files

### USER Files ###
USER = main.o SDLMain.o SDL_Init.o Button.o PopUp.o PopupScreens.o SmallButton.o Splash.o


########################################################################
## Rules
## type make -j4 [rule] to speed up the compilation

BUILD = $(USER)

Jeopardy: $(BUILD)
	  $(CXX) $(patsubst %,build/%,$(BUILD)) $(LDFLAGS) $(LIB) $(FRM) -o $@

clean:
	rm -f build/*.o Jeopardy

########################################################################
#                       -*- End of Makefile -*-                        #
########################################################################
