TARGET := h5n_print
SRCDIR := ./src
BUILDDIR := ./build
SCRIPTDIR := ./scripts

SRCS := $(shell find $(SRCDIR) -type f \( -name "*.c" -or -name "*.cpp" \))
OBJS := $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SRCS:$(SRCDIR)/%=%))))
$(warning $(OBJS))
DEPS := $(OBJS:.o=.d)

INCDIR := $(SRCDIR)/include
INCFLAGS := $(addprefix -I, $(INCDIR))

$(warning $(INCFLAGS))

CC := clang
CXX := clang++
LD := ld.lld

CFLAGS := -g -O2 -Wall -Wextra
CXXFLAGS := -g -O2 -Wall -Wextra
LDFLAGS := -g -O2 -Wall -Wextra
# -e start -static

CPPFLAGS := $(INCFLAGS)

.PHONY: all clean run test

all: executable

executable: $(BUILDDIR)/$(TARGET)

$(BUILDDIR)/$(TARGET): $(OBJS)
	mkdir -p $(dir $@)
	$(CXX) $(LDFLAGS) $(CPPFLAGS) $^ -o $@
#	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)/*

run:
	$(SCRIPTDIR)/print_test.sh

test:
	$(SCRIPTDIR)/print_test.sh

-include $(DEPS)
