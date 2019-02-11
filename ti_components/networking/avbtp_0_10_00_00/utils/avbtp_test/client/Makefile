SOURCES := $(wildcard source/*.cpp)
OBJS := $(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))

EXEC_NAME=avbtp_test_client

CFLAGS := -MMD -O3 -std=c++11 -Wall
INCLUDES := -Iinclude
LFLAGS := -pthread
LIBS := -lavformat -lavcodec

.PHONY: all clean objdir

all: objdir $(EXEC_NAME)

objdir:
	@mkdir -p obj

$(EXEC_NAME): $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $(OBJS) $(LFLAGS) $(LIBS)

obj/%.o: source/%.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	$(RM) -r obj
	$(RM) $(EXEC_NAME)

-include $(OBJS:.o=.d)
