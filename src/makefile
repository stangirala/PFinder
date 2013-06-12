
PROJ_PATH := $(shell pwd)/..

-include $(PROJ_PATH)/make.include

# library source files --------------------

CORE_LIBFILES = hist_distance.cpp 
CORE_LIB      = libPROJcore.a


# application source files --------------------

APPFILES = personfinder.cpp

# intermediate and final build locations ------
BIN_DIR  = $(PROJ_PATH)/_bin
TEMP_DIR = _intermediates


# derived variables on source files -- for library and applications
CORE_LIBOBJS = ${addprefix ${TEMP_DIR}/core/,$(CORE_LIBFILES:.cpp=.o)}
#EXTRA_LIBOBJS = ${addprefix ${TEMP_DIR}/extra/,$(EXTRA_LIBFILES:.cpp=.o)}
LIBOBJS = $(CORE_LIBOBJS) 
#$(EXTRA_LIBOBJS)

APPOBJS   = ${addprefix ${TEMP_DIR}/apps/,$(APPFILES:.cpp=.o)}
DEPS      = ${LIBOBJS:.o=.d} $(APPOBJS:.o=.d)
PROJ_APPS = ${addprefix ${BIN_DIR}/,$(APPFILES:.cpp=)}
PROJ_LIBS = $(BIN_DIR)/$(CORE_LIB) 
#$(BIN_DIR)/$(EXTRA_LIB)

CFLAGS += -Icore -I$(PROJ_PATH)/include

CXXFLAGS = -std=gnu++0x

PROJ_SRC_DIRS  = core apps


.PHONY: clean

all: make_dirs $(PROJ_LIBS) $(PROJ_APPS) 

make_dirs:
	mkdir -p $(TEMP_DIR)
	mkdir -p $(BIN_DIR)
	for subdir in $(PROJ_SRC_DIRS); do mkdir -p $(TEMP_DIR)/$$subdir; done

$(BIN_DIR)/$(CORE_LIB):	$(CORE_LIBOBJS)
	ar rcs $@ $(CORE_LIBOBJS)

# app rules: should be after the explicit library rule above -----------
$(BIN_DIR)/% : ${TEMP_DIR}/apps/%.o $(PROJ_LIBS)
	$(CCC) $< $(PROJ_LIBS) $(LFLAGS) -o $@

${TEMP_DIR}/%.o : %.cpp
	@$(call make-depend,$<,$@,$(subst .o,.d,$@))
	$(CCC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

define make-depend
	gcc -MM -MF $3 -MP -MT $2 $(CFLAGS) $1
endef


clean:
	-rm $(PROJ_LIBS)
	-rm $(LIBOBJS)
	-rm $(PROJ_APPS)
	-rm $(APPOBJS)
	-rm $(DEPS)
	-for subdir in $(PROJ_SRC_DIRS); do rmdir $(TEMP_DIR)/$$subdir; done
	-rmdir $(TEMP_DIR)
	-rmdir -rf $(BIN_DIR)

-include $(DEPS)


