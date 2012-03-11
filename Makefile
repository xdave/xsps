TARGET   := xsps
XSPS_CONFIG_DIR := config

CC := gcc
VALAC := valac

PKGCONFIG := pkg-config
PKGS := glib-2.0 gobject-2.0 gee-1.0
PKG_CFLAGS  := `$(PKGCONFIG) --cflags $(PKGS)`
PKG_LDFLAGS := `$(PKGCONFIG) --libs $(PKGS)`

SRC_DIR  := src
TMP_DIR  := tmp
INC_DIR  := include

VGEN_DIR := generated

VSRC_DIR := $(SRC_DIR)/vala
VINC_DIR := $(VOUT_DIR)/include

VAPI_OUT := $(TARGET).vapi
VHEADER  := $(VGEN_DIR)/$(TARGET).h

VSRC  := $(shell find $(VSRC_DIR) -type f -name '*.vala')
VCSRC := $(VGEN_DIR)/$(TARGET).c
VPKGS := $(foreach pkg,$(PKGS),$(subst $(pkg),--pkg=$(pkg),$(pkg)))

CSRC := $(shell find $(SRC_DIR) -type f -name '*.c')

VOBJ :=	$(patsubst $(VGEN_DIR)/%.c,$(TMP_DIR)/%.vo,$(VCSRC))
COBJ := $(patsubst $(SRC_DIR)/%.c,$(TMP_DIR)/%.o,$(CSRC))
OBJ  := $(VOBJ) $(COBJ)

STD   := -std=c99
OPTZ  := -O2 -pipe -mtune=generic -fPIC -funroll-loops -fno-exceptions
SSP   := -fstack-protector-all -D_FORTIFY_SOURCE=2 --param ssp-buffer-size=1
DEBUG := -ggdb -DXSPS_DEBUG
DEF := -DXSPS_CONFIG_DIR=\"$(XSPS_CONFIG_DIR)\" -D_REENTRANT -D_XOPEN_SOURCE=600
WARN_COMMON :=  -Werror -Wshadow -Wnested-externs -Wvla -Wno-overlength-strings\
		-Wmissing-declarations -Wdisabled-optimization
# With these below warning flags, gcc doesn't like the code Vala generates.
#WARN := -Wextra -Wformat=2 -Wformat-security -Wconversion $(WARN_COMMON)
WARN := $(WARN_COMMON)
VWARN := $(WARN_COMMON)
INCLUDE := -I$(INC_DIR) -I$(VGEN_DIR)
STATIC :=
CFLAGS := $(STC) $(STD) $(OPTZ) $(SSP) $(DEBUG) $(DEF) $(INCLUDE) $(PKG_CFLAGS)
LDFLAGS := $(STC) $(PKG_LDFLAGS) -lconfuse -Wl,--as-needed

all: $(TARGET)

$(VGEN_DIR)/xsps.vala: $(VSRC)
	@mkdir -p ${@D}
	@echo "[GEN]	$@"
	@cat $^ > $@

$(VGEN_DIR)/%.c: $(VGEN_DIR)/%.vala
	@mkdir -p ${@D}
	@echo "[GEN]	$@"
	@$(VALAC) --cc=true -C -c -b $(VGEN_DIR) -d $(VGEN_DIR) -H $(VHEADER) \
		--library=xsps --vapidir=$(INC_DIR) --pkg=xsps_c $^

$(TARGET): $(OBJ)
	@echo "[LD]	$@"
	@$(CC) -o $@ $^ $(LDFLAGS)

$(TMP_DIR)/%.vo: $(VGEN_DIR)/%.c
	@mkdir -p ${@D}
	@echo "[CC]	$@"
	@$(CC) $(VWARN) $(CFLAGS) -c $< -o $@

$(TMP_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p ${@D}
	@echo "[CC]	$@"
	@$(CC) $(WARN) $(CFLAGS) -c $< -o $@

clean:
	@echo "[RM]	Clean."
	@rm -rf $(TMP_DIR) $(TARGET) $(VGEN_DIR)

.PHONY: all clean
.PRECIOUS: $(VHEADER) $(VCSRC)
