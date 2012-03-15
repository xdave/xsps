TARGET   := jsontest

## Programs
CCACHE :=
CC := $(CCACHE) gcc
VALAC := valac
PKGCONFIG := pkg-config

## pkg-config
PKGS := glib-2.0 gobject-2.0 gio-2.0 gee-1.0 json-glib-1.0
PKG_CFLAGS  := $(shell $(PKGCONFIG) --cflags $(PKGS))
PKG_LDFLAGS := $(shell $(PKGCONFIG) --libs $(PKGS)) -lconfuse
VPKGS := $(foreach pkg,$(PKGS),$(subst $(pkg),--pkg=$(pkg),$(pkg)))

## Directories
CONFIG_DIR	:= config
SRC_DIR		:= src
TMP_DIR		:= tmp
INC_DIR		:= include
VGEN_DIR	:= generated
VSRC_DIR	:= $(SRC_DIR)

## Sources
VHEADER   := $(VGEN_DIR)/$(TARGET).h
VSRC	  := $(shell find $(VSRC_DIR) -type f -name '*.vala')
VCSRC	  := $(patsubst $(VSRC_DIR)/%.vala,$(VGEN_DIR)/%.c,$(VSRC))
CSRC	  := $(shell find $(SRC_DIR) -type f -name '*.c')

## Object files
VOBJ :=	$(patsubst $(VGEN_DIR)/%.c,$(TMP_DIR)/%.vala.o,$(VCSRC))
COBJ :=	$(patsubst $(SRC_DIR)/%.c,$(TMP_DIR)/%.c.o,$(CSRC))

## Compiler flags
#NOTE: With these below warning flags, gcc doesn't like the code Vala generates
# -Wextra -Wformat=2 -Wformat-security -Wconversion
STD     := -std=c99
OPTZ    := -O2 -pipe -mtune=generic -fPIC -funroll-loops -fno-exceptions
SSP     := -fstack-protector-all -D_FORTIFY_SOURCE=2 --param ssp-buffer-size=1
DEBUG   := -ggdb -DXSPS_DEBUG
DEF     := -DCONFIG_DIR=\"$(CONFIG_DIR)\" -D_REENTRANT -D_XOPEN_SOURCE=600
WARN    := -Werror -Wshadow -Wnested-externs -Wvla -Wno-overlength-strings \
		-Wmissing-declarations -Wdisabled-optimization
INCLUDE := -I. -I$(INC_DIR) -I$(VGEN_DIR)
STATIC  :=
CFLAGS  := $(STC) $(STD) $(OPTZ) $(SSP) $(DEBUG) $(DEF) $(INCLUDE) $(PKG_CFLAGS)
LDFLAGS := $(STC) $(PKG_LDFLAGS) -Wl,--as-needed

## Targets

all: $(TARGET)

$(TARGET): $(VOBJ) $(COBJ)
	@echo "[LD]	$@"
	@$(CC) -o $@ $^ $(LDFLAGS)

$(VHEADER): $(VSRC)
	@mkdir -p ${@D}
	@echo "[VALAC]	$@"
	@$(VALAC) --nostdpkg --ccode --library=$(TARGET) --vapi=$(TARGET).vapi \
		--basedir=$(VSRC_DIR) --directory=$(VGEN_DIR) --header=$@ \
		--vapidir=$(INC_DIR)  --use-header=$@ $(VPKGS) $^

$(VGEN_DIR)/%.c: $(VSRC_DIR)/%.vala $(VHEADER)
	@mkdir -p ${@D}
	@touch $@

$(TMP_DIR)/%.vala.o: $(VGEN_DIR)/%.c $(VHEADER)
	@mkdir -p ${@D}
	@echo "[CC]	$@"
	@$(CC) $(WARN) $(CFLAGS) -c $< -o $@

$(TMP_DIR)/%.c.o: $(SRC_DIR)/%.c $(VHEADER)
	@mkdir -p ${@D}
	@echo "[CC]	$@"
	@$(CC) $(WARN) $(CFLAGS) -c $< -o $@

clean:
	@echo "[RM]	Clean."
	@rm -rf $(TMP_DIR) $(VGEN_DIR) $(TARGET)

.PHONY: all clean
.PRECIOUS: $(VHEADERS) $(VAPI) $(VCSRC)
