OS = linux
ARCH = x86

OBJDIR = obj
BINDIR = bin

SRCS = \
BinaryFile.cpp \
DomainModel.cpp \
Environment.cpp \
LoadBalancingAlgorithm.cpp \
LuaFunction.cpp \
main.cpp \
Rebalancer.cpp \
SampleFunction.cpp \
Utils.cpp

HEADERS = \
BinaryFile.h \
DomainModel.h \
Environment.h \
IDomainModel.h \
IEnvironment.h \
IFunction.h \
IInputFile.h \
ILoadBalancingAlgorithm.h \
IMPICommunicator.h \
IMPI.h \
IProblemBuilder.h \
IRebalancer.h \
LoadBalancingAlgorithm.h \
LuaFunction.h \
MPIWorldCommunicator.h \
ProblemBuilder.h \
Rebalancer.h \
SampleFunction.h \
Utils.h \
Values.h \

THIRDPARTY_PATH = ../../thirdparty

LUA_PATH = $(THIRDPARTY_PATH)/lua5.2
LUA_INC_PATH = $(LUA_PATH)/include
LUA_LIB_PATH = $(LUA_PATH)/$(OS)/$(ARCH)

EXECUTABLE = load-balancing

CC = mpic++
CFLAGS = -O3 -I$(LUA_INC_PATH)/include

LDFLAGS = -L $(LUA_LIB_PATH)
LDLIBS = -llua52 -lm

ifeq ($(configuration),EMULATE_MPI)
	CFLAGS += -D$(configuration)
else
	SRCS += MPIWorldCommunicator.cpp
	HEADRES += MPIWorldCommunicator.h
endif

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))

all: $(BINDIR)/$(EXECUTABLE) $(BINDIR)/liblua52.so
	
$(BINDIR)/$(EXECUTABLE): $(OBJS) | $(BINDIR)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(BINDIR)/$(EXECUTABLE)

$(OBJS): $(HEADERS)| $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)
	
$(BINDIR)/liblua52.so: | $(BINDIR)
	cp $(LUA_PATH)/liblua52.so $(BINDIR)/liblua52.so
	
$(OBJDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj
	rm -rf bin
