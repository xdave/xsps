TARGET := xsps

PREFIX := /usr/local
DESTDIR :=
INSTALL_DIR := $(DESTDIR)$(PREFIX)/bin
INSTALL_TARGET := $(INSTALL_DIR)/$(TARGET)
XSPS_CONFIG_DIR := ./config

SRC := $(shell find src -type f -name '*.c')
OBJ := $(patsubst src/%.c,tmp/%.o,$(SRC))

STD := -std=c99
WARN := -Wall -Werror -pedantic
OPTZ := -O2 -pipe -mtune=generic\
	-funroll-loops -fno-exceptions\
	-fstack-protector-all -D_FORTIFY_SOURCE=2
DEBUG := -ggdb -DXSPS_DEBUG
STATIC :=
INCLUDE := -Isrc/xsps
DEFINES := -DXSPS_CONFIG_DIR=\"$(XSPS_CONFIG_DIR)\" -D_REENTRANT\
	   -D_POSIX_C_SOURCE=200112L
CFLAGS := $(STD) $(WARN) $(STATIC) $(OPTZ) $(DEFINES) $(DEBUG) $(INCLUDE)
LDFLAGS := $(STD) $(STATIC) -Wl,--as-needed

all: $(TARGET)
	@echo "[DONE]	Nothing more to be done for \`$^'."

tmp/%.o: src/%.c
	@mkdir -p ${@D}
	@echo "[CC]	$@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	@echo "[LD]	$@"
	@$(CC) $(LDFLAGS) $^ -o $@

clean:
	@rm -rf tmp $(TARGET)
	@echo "[CLEAN]"

install: $(INSTALL_TARGET)

$(INSTALL_TARGET): $(TARGET)
	@echo "[INSTALL]	$@"
	@mkdir -p $(INSTALL_DIR)
	@install -m0755 $< $@

uninstall:
	@echo "[UNINSTALL]	$(INSTALL_TARGET)"
	@rm -f $(INSTALL_TARGET)

.PHONY: all clean install uninstall
