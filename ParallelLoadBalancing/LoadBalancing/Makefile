OS = linux
ARCH = x86

OBJDIR = obj
BINDIR = bin

SRCS = \
Utils.cpp \
BinaryFile.cpp \
StandartLuaModule.cpp \
DomainModel.cpp \
LuaFunction.cpp \
Rebalancer.cpp \
LoadBalancingAlgorithm.cpp \
SampleFunction.cpp \
Environment.cpp \
main.cpp \
StandartLuaModule/DomainModelModule.cpp \
StandartLuaModule/LoadBalancingAlgorithmModule.cpp \
StandartLuaModule/RebalancerModule.cpp \
StandartLuaModule/LuaFunctionModule.cpp \
StandartLuaModule/EnvironmentModule.cpp \
LuaAPI/LuaAPI.cpp \
LuaAPI/IEnvironment.cpp \
LuaAPI/IRebalancer.cpp \
LuaAPI/IDomainModel.cpp \
LuaAPI/ILoadBalancingAlgorithm.cpp


HEADERS = \
LoadBalancingAlgorithm.h \
MPIWorldCommunicator.h \
Environment.h \
Utils.h \
DomainModel.h \
LuaFunction.h \
SampleFunction.h \
ProblemBuilder.h \
Rebalancer.h \
BinaryFile.h \
StandartLuaModule.h \
StandartLuaModule/RebalancerModule.h \
StandartLuaModule/EnvironmentModule.h \
StandartLuaModule/LoadBalancingAlgorithmModule.h \
StandartLuaModule/DomainModelModule.h \
StandartLuaModule/LuaFunctionModule.h \
include/LoadBalancing/IProblemBuilder.h \
include/LoadBalancing/IEnvironment.h \
include/LoadBalancing/IInputFile.h \
include/LoadBalancing/IRebalancer.h \
include/LoadBalancing/IMPI.h \
include/LoadBalancing/LuaAPI/IEnvironment.h \
include/LoadBalancing/LuaAPI/IRebalancer.h \
include/LoadBalancing/LuaAPI/LuaAPI.h \
include/LoadBalancing/LuaAPI/IDomainModel.h \
include/LoadBalancing/LuaAPI/ILoadBalancingAlgorithm.h \
include/LoadBalancing/IDomainModel.h \
include/LoadBalancing/ILoadBalancingAlgorithm.h \
include/LoadBalancing/IMPICommunicator.h \
include/LoadBalancing/IFunction.h \
include/LoadBalancing/Values.h


THIRDPARTY_PATH = ../../thirdparty

LUA_PATH = $(THIRDPARTY_PATH)/lua5.2
LUA_INC_PATH = $(LUA_PATH)/include
LUA_LIB_PATH = $(LUA_PATH)/lib/$(OS)/$(ARCH)

EXECUTABLE = load-balancing

CC = mpic++
CFLAGS = -O3 -I$(LUA_INC_PATH) -Iinclude

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

$(OBJDIR)/StandartLuaModule: | $(OBJDIR)
	mkdir -p $(OBJDIR)/StandartLuaModule

$(OBJDIR)/LuaAPI: | $(OBJDIR)
	mkdir -p $(OBJDIR)/LuaAPI

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)
	
$(BINDIR)/liblua52.so: | $(BINDIR)
	cp $(LUA_LIB_PATH)/liblua52.so $(BINDIR)/liblua52.so
	
$(OBJDIR)/%.o: %.cpp | $(OBJDIR) $(OBJDIR)/StandartLuaModule $(OBJDIR)/LuaAPI
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj
	rm -rf bin
