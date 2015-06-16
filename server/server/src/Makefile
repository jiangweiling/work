CXX = g++
#STD =
STD = -std=c++11
INCLUDE = -I../.. -I. -I../../socket/include
CXXFLAGS = $(STD) -g -Wall $(INCLUDE)
LD = $(CXX)
LIBS = -L../../socket/lib -lsocket
LDFLAGS = $(STD) $(LIBS)

TARGET = test
SRC_DIR = .
OBJ_DIR = ./objs
LIB_DIR = ../lib
HEADER_DIR = ../include/server

MAKE_HEADER_DIR := $(shell mkdir -p $(HEADER_DIR))
MAKE_OBJECT_DIR := $(shell mkdir -p $(OBJ_DIR))
MAKE_LIB_DIR := $(shell mkdir -p $(LIB_DIR))
OBJS = $(addsuffix .o, $(subst $(SRC_DIR),$(OBJ_DIR),$(basename $(wildcard $(SRC_DIR)/*.cpp))))

$(TARGET): $(OBJS)
	$(LD) -o $@ $^ $(LDFLAGS)
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

build : $(OBJS)
	cp ./*.h $(HEADER_DIR)
	rm -f $(LIB_DIR)/libserver.a
	ar -r $(LIB_DIR)/libserver.a $(OBJ_DIR)/server.o

.PHONY : clean cleanall
clean:
	@echo "rm -rf $(OBJ_DIR)"
	@echo "rm -f $(TARGET)"
	@echo "make cleanall = rm -rf $(TARGET) $(OBJ_DIR)"
cleanall:
	rm -f *~
	rm -f $(SRC_DIR)/*~
	rm -f $(OBJ_DIR)/*
	rmdir $(OBJ_DIR)
	rm -f $(TARGET)
	rm -f $(LIB_DIR)/*
	rmdir $(LIB_DIR)
