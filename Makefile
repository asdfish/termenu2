CC ?= cc
CFLAGS ?= -O2 -march=native -pipe
COMMONFLAGS := -std=c99 $\
							 -Wall -Wextra -Wpedantic $\
							 -Iinclude

# uncomment/comment to enable/disable
# PROCESS_HEADER_FILES := yes
PROCESSED_HEADER_FILES := $(if ${PROCESS_HEADER_FILES},$\
														$(subst .h,$\
															$(if $(findstring clang,${CC}),$\
																.h.pch,$\
																.h.gch),$\
															$(shell find include -name '*.h' -type f)))

OBJECT_FILES := $(patsubst src/%.c,$\
									build/%.o,$\
									$(shell find src -name '*.c' -type f))

TERMENU_REQUIREMENTS := ${PROCESSED_HEADER_FILES} ${OBJECT_FILES}

define COMPILE
${CC} -c $(1) ${CFLAGS} ${COMMONFLAGS} -o $(2)

endef
define REMOVE
$(if $(wildcard $(1)),$\
	rm $(1))

endef
define REMOVE_LIST
$(foreach ITEM,$\
	$(1),$\
	$(call REMOVE,${ITEM}))
endef

all: termenu

termenu: ${TERMENU_REQUIREMENTS}
	${CC} ${OBJECT_FILES} ${CFLAGS} ${COMMONFLAGS} -o $@

build/%.o: src/%.c
	$(call COMPILE,$<,$@)
%.gch: %
	$(call COMPILE,$<,$@)
%.pch: %
	$(call COMPILE,$<,$@)

clean:
	$(call REMOVE_LIST,${TERMENU_REQUIREMENTS})
	$(call REMOVE,termenu)

.PHONY: all clean install uninstall
