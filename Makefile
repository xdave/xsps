TARGET   := xsps

## Programs
CC := ccache gcc
VALAC := valac
PKGCONFIG := pkg-config

## pkg-config
PKGS := glib-2.0 gobject-2.0 gio-2.0 gee-1.0
PKG_CFLAGS  := $(shell $(PKGCONFIG) --cflags $(PKGS))
PKG_LDFLAGS := $(shell $(PKGCONFIG) --libs $(PKGS))
VPKGS := $(foreach pkg,$(PKGS),$(subst $(pkg),--pkg=$(pkg),$(pkg))) \
	--pkg=posix --pkg=stdlib --pkg=xsps_c --pkg=confuse

## Directories
CONFIG_DIR	:= config
SRC_DIR		:= src
TMP_DIR		:= tmp
INC_DIR		:= include
VGEN_DIR	:= generated
VSRC_DIR	:= $(SRC_DIR)/vala

## Sources
VHEADER   := $(VGEN_DIR)/$(TARGET).h
VSRC	  := $(shell find $(VSRC_DIR) -type f -name '*.vala')
VCSRC	  := $(patsubst $(VSRC_DIR)/%.vala,$(VGEN_DIR)/%.c,$(VSRC))
CSRC	  := $(shell find $(SRC_DIR) -type f -name '*.c')

## Object files
VOBJ :=	$(patsubst $(VGEN_DIR)/%.c,$(TMP_DIR)/%.vo,$(VCSRC))
COBJ :=	$(patsubst $(SRC_DIR)/%.c,$(TMP_DIR)/%.o,$(CSRC))

## Compiler flags
#NOTE: With these below warning flags, gcc doesn't like the code Vala generates
# -Wextra -Wformat=2 -Wformat-security -Wconversion $(WARN_COMMON)
STD     := -std=c99
OPTZ    := -O2 -pipe -mtune=generic -fPIC -funroll-loops -fno-exceptions
SSP     := -fstack-protector-all -D_FORTIFY_SOURCE=2 --param ssp-buffer-size=1
DEBUG   := -ggdb -DXSPS_DEBUG
DEF     := -DCONFIG_DIR=\"$(CONFIG_DIR)\" -D_REENTRANT -D_XOPEN_SOURCE=600
WARN    := -Werror -Wshadow -Wnested-externs -Wvla -Wno-overlength-strings \
		-Wmissing-declarations -Wdisabled-optimization
INCLUDE := -I$(INC_DIR) -I$(VGEN_DIR)
STATIC  :=
CFLAGS  := $(STC) $(STD) $(OPTZ) $(SSP) $(DEBUG) $(DEF) $(INCLUDE) $(PKG_CFLAGS)
LDFLAGS := $(STC) $(PKG_LDFLAGS) -lconfuse -Wl,--as-needed

## Targets
all: $(VHEADER) $(TARGET)

$(TARGET): $(VOBJ) $(COBJ)
	@echo "[LD]	$@"
	@$(CC) -o $@ $^ $(LDFLAGS)

$(VHEADER): $(VSRC)
	@mkdir -p ${@D}
	@echo "[VGEN]	$@"
	@$(VALAC) --nostdpkg --vapidir=$(INC_DIR) $(VPKGS) --ccode --compile \
		--basedir=$(VSRC_DIR) --directory=$(VGEN_DIR) \
		--library=$(TARGET) --header=$@ --thread $^

$(TMP_DIR)/%.vo: $(VGEN_DIR)/%.c
	@mkdir -p ${@D}
	@echo "[VCC]	$@"
	@$(CC) $(WARN) $(CFLAGS) -c $< -o $@

$(TMP_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p ${@D}
	@echo "[CC]	$@"
	@$(CC) $(WARN) $(CFLAGS) -c $< -o $@


clean:
	@echo "[RM]	Clean."
	@rm -rf $(TMP_DIR) $(VGEN_DIR) $(TARGET)

.PHONY: all clean
.PRECIOUS: $(VHEADERS) $(VAPI) $(VCSRC)
