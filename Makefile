TARGET := xsps
XSPS_CONFIG_DIR := config

PREFIX := /usr/local
DESTDIR :=
INSTALL_DIR := $(DESTDIR)$(PREFIX)/bin
INSTALL_TARGET := $(INSTALL_DIR)/$(TARGET)

SRC := $(shell find src -type f -name '*.c')
OBJ := $(patsubst src/%.c,tmp/%.o,$(SRC))

LIBS := -lconfuse

WARN := -Wall -Werror -pedantic
OPTZ := -O2 -pipe -mtune=generic\
	-fPIC -funroll-loops -fno-exceptions\
	-fstack-protector-all -D_FORTIFY_SOURCE=2
DEBUG := -ggdb -DXSPS_DEBUG
STATIC :=
INCLUDE := -Iinclude
DEFINES := -DXSPS_CONFIG_DIR=\"$(XSPS_CONFIG_DIR)\" -D_REENTRANT\
	   -D_POSIX_C_SOURCE=200112L
CFLAGS := $(WARN) $(STATIC) $(OPTZ) $(DEFINES) $(DEBUG) $(INCLUDE) $(LIBS)
LDFLAGS := $(STATIC) -Wl,--as-needed $(LIBS)

all: $(TARGET)

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
