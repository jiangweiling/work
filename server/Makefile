CXX = g++
STD = -std=c++11
#STD =
INCLUDE = -I./include
CXXFLAGS = $(STD) -g -O2 -Wall $(INCLUDE)
LD = $(CXX)
LIBS = -L.
LDFLAGS = $(STD) $(LIBS)

TARGET = main
SRC_DIR = .
OBJ_DIR = ./objs

MAKE_OBJECT_DIR := $(shell mkdir -p $(OBJ_DIR))
OBJS = $(addsuffix .o, $(subst $(SRC_DIR),$(OBJ_DIR),$(basename $(wildcard $(SRC_DIR)/*.cpp))))

$(TARGET): $(OBJS)
	$(LD) -o $@ $^ $(LDFLAGS)
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

build : $(OBJS)

.PHONY : clean cleanall
clean:
	@echo "rm -f $(OBJ_DIR)/*"
	@echo "rm -f $(TARGET)"
	@echo "make cleanall = rm -rf $(TARGET) $(OBJ_DIR)"
cleanall:
	rm -f *~
	rm -f $(SRC_DIR)/*~
	rm -f $(OBJ_DIR)/*
	rmdir $(OBJ_DIR)
	rm -f $(TARGET)
