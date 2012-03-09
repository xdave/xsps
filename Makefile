TARGET   := xsps

XSPS_CONFIG_DIR := config

SRC_DIR  := src
TMP_DIR  := tmp
INC_DIR  := include
VSRC_DIR := $(SRC_DIR)/vala
VOUT_DIR := $(TMP_DIR)/vala
VINC_DIR := $(VOUT_DIR)/include
VAPI_DIR := vapi

VAPI_OUT := $(TARGET).vapi
VHEADER  := $(VINC_DIR)/$(TARGET)_vala.h

VSRC := $(shell find $(VALA_SRC_DIR) -type f -name '*.vala')
VAPI := $(patsubst %,--use-fast-vapi=%,$(shell find $(VAPI_DIR) \
					 -type f -name '*.vapi'))
VALAC  := valac
VFLAGS := -C -c -b $(VSRC_DIR) -d $(VOUT_DIR) --library=$(TARGET) \
		--vapi=$(VAPI_OUT) -H $(VHEADER) $(VAPI)

CSRC := $(shell find $(SRC_DIR) -type f -name '*.c')
VCSRC := $(patsubst .$(VALA_SRC_DIR)/%.vala,$(VOUT_DIR)/%.c,$(VSRC))
VCSRC := $(subst src/vala,,$(VCSRC))

COBJ := $(patsubst $(SRC_DIR)/%.c,$(TMP_DIR)/%.o,$(CSRC))
VOBJ := $(patsubst $(VOUT_DIR)/%.c,$(VOUT_DIR)/%.v,$(VCSRC))

PKGCONFIG := pkg-config
PKGS := glib-2.0 gobject-2.0
PKG_CFLAGS  := `$(PKGCONFIG) --cflags $(PKGS)`
PKG_LDFLAGS := `$(PKGCONFIG) --libs $(PKGS)`

INCLUDE := -I$(INC_DIR) -I$(VINC_DIR)

STC :=
STD := -std=c99
OPTZ := -O2 -pipe -mtune=generic -fPIC -funroll-loops -fno-exceptions
SSP := -fstack-protector-all -D_FORTIFY_SOURCE=2 --param ssp-buffer-size=1
DEBUG := -ggdb -DXSPS_DEBUG

DEF :=-DXSPS_CONFIG_DIR=\"$(XSPS_CONFIG_DIR)\" -D_REENTRANT -D_XOPEN_SOURCE=600

WARN_COMMON := -Werror -Wshadow -Wformat=2 -Wformat-security -Wnested-externs\
		-Wvla -Wno-overlength-strings -Wmissing-declarations\
		-Wdisabled-optimization
WARN := -Wextra -Wconversion $(WARN_COMMON)
VWARN := $(WARN_COMMON)

CFLAGS := $(STC) $(STD) $(OPTZ) $(SSP) $(DEBUG) $(DEF) $(INCLUDE) $(PKG_CFLAGS)
LDFLAGS := $(STC) $(PKG_LDFLAGS) -lconfuse -Wl,--as-needed

all: $(VCSRC) $(TARGET)

$(VCSRC): $(VALA_SRC)
	@echo "[VALA]	Precompiling..."
	@$(VALAC) $(VFLAGS) $(VSRC)

$(TARGET): $(VOBJ) $(COBJ)
	@echo "[LD]	$@"
	@$(CC) -o $@ $^ $(LDFLAGS)

$(VOUT_DIR)/%.v: $(VOUT_DIR)/%.c
	@mkdir -p ${@D}
	@echo "[CC]	$@"
	@$(CC) $(VWARN) $(CFLAGS) -c $< -o $@

$(TMP_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p ${@D}
	@echo "[CC]	$@"
	@$(CC) $(WARN) $(CFLAGS) -c $< -o $@

clean:
	@echo "[RM]	Clean."
	@rm -rf $(TMP_DIR) $(TARGET)

.PHONY: all clean
