CXX = g++
STD =
#STD = -std=c++11
INCLUDE = -I.
CXXFLAGS = $(STD) -g -Wall $(INCLUDE)
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
	@echo "rm -rf $(OBJ_DIR)"
	@echo "rm -f $(TARGET)"
	@echo "make cleanall = rm -rf $(TARGET) $(OBJ_DIR)"
cleanall:
	rm -f *~
	rm -f $(SRC_DIR)/*~
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET)
