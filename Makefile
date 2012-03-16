# Copyright (c) 2012 davehome <davehome@redthumb.info.tm>.
# All rights reserved.
# Distributed under a modified BSD-style license.
# See the COPYING file in the toplevel directory for license details.

### TODO: (un)install targets

## Program name and version
NAME    := xsps
MAJVER  := 0
MINVER  := 0
PATVER  := 0
VERSION := $(MAJVER).$(MINVER).$(PATVER)

## Directories
SDIR := src
IDIR := include
TDIR := tmp
CDIR := config

## Targets
XSPS           := $(NAME)
XSPS_STATIC    := $(XSPS).static
LIBXSPS        := lib$(NAME).so.$(VERSION)
LIBXSPS_STATIC := lib$(NAME).a
XSPS_TARGETS   := $(XSPS_STATIC) $(XSPS)

## Vala and C source/headers/objects
XSPS_C      := $(shell find $(SDIR) -type f -name '*.c')
XSPS_V      := $(shell find $(SDIR) -type f -name '*.vala')
XSPS_VM     := $(shell find $(SDIR) -type f -name 'main.*')
XSPS_VC     := $(patsubst $(SDIR)/%.vala,$(TDIR)/%.c,$(XSPS_V))
XSPS_VHEAD  := $(IDIR)/$(NAME)/$(XSPS).h
XSPS_VOBJ   := $(patsubst $(TDIR)/%.c,$(TDIR)/%.vala.o,$(XSPS_VC))
XSPS_COBJ   := $(patsubst $(SDIR)/%.c,$(TDIR)/%.c.o,$(XSPS_C))
XSPS_OBJ    := $(XSPS_VOBJ) $(XSPS_COBJ)
XSPS_MOBJ   := $(patsubst $(SDIR)/%,$(TDIR)/%.o,$(XSPS_VM))
LIBXSPS_OBJ := $(subst $(XSPS_MOBJ),,$(XSPS_OBJ))

## Build programs
PKGC   := pkg-config
VALAC  := valac

## Required packages -- internal and external
PKGS  := glib-2.0 gobject-2.0 gee-1.0 json-glib-1.0
VPKGS := $(foreach pkg,$(PKGS),$(subst $(pkg),--pkg=$(pkg),$(pkg))) \
		--pkg=posix --pkg=stdlib --pkg=defs

## Common C Compiler flags
STD  := -std=c99
WARN := -Werror -Wshadow -Wnested-externs -Wno-overlength-strings \
	-Wvla -Wmissing-declarations -Wdisabled-optimization -pedantic
OPT  := -O2 -pipe -mtune=generic -fPIC -funroll-loops -fno-exceptions
SSP  := -fstack-protector-all -D_FORTIFY_SOURCE=2 --param ssp-buffer-size=1
DEB  := -ggdb -DXSPS_DEBUG
DEF  := -DXSPS_NAME=\"$(NAME)\" -DXSPS_MAJOR=\"$(MAJVER)\" \
	-DXSPS_MINOR=\"$(MINVER)\" -DXSPS_PATCH=\"$(PATVER)\" \
	-DXSPS_CONFIG_DIR=\"$(CDIR)\" 

## CFLAGS, LDFLAGS and options passed to gcc/valac
PKG_CFLAGS   := $(shell $(PKGC) --cflags $(PKGS))
PKG_LFLAGS   := $(shell $(PKGC) --libs   $(PKGS))
CINC         := -I. -I$(IDIR)
XSPS_CFLAGS  := $(STD) $(WARN) $(OPT) $(SSP) $(DEF) $(DEB) $(PKG_CFLAGS) $(CINC)
XSPS_LDFLAGS := $(PKG_LFLAGS) -Wl,--as-needed
VFLAGS       := --nostdpkg --ccode --basedir=$(SDIR) --directory=$(TDIR) \
		--vapidir=$(IDIR)/$(NAME) $(VPKGS)

## pkg-config and hack to build all glib stuff statically into a shared
## executable
PKG_STATIC := $(PKG_STATIC) $(shell $(PKGC) --libs --static $(PKGS))
PKG_STATIC := $(subst -ldl,,$(PKG_STATIC))
PKG_STATIC := -Wl,-Bstatic $(PKG_STATIC) -lpcre -Wl,-Bdynamic -ldl

BINS := $(XSPS) $(XSPS_STATIC) $(LIBXSPS) $(LIBXSPS_STATIC)
		 
## Targets
all: $(XSPS_TARGETS)

## This builds the half-static executable
$(XSPS_STATIC): $(LIBXSPS_STATIC)
	@echo "[LD]	$@"
	@$(CC) -o $@ $(XSPS_MOBJ) $^ $(LDFLAGS) $(PKG_STATIC) -Wl,--as-needed

## This builds the static library
$(LIBXSPS_STATIC): $(XSPS_OBJ)
	@echo "[AR]	$@"
	@rm -f $@ && ar rcs $@ $(LIBXSPS_OBJ)

## This builds the shared executable
$(XSPS): $(LIBXSPS)
	@echo "[LD]	$@ [shared]"
	@$(CC) $(LDFLAGS) $(XSPS_LDFLAGS) -o $@ \
		$(XSPS_MOBJ) lib$(NAME).so.$(MAJVER) 

## This builds the shared library
$(LIBXSPS): $(XSPS_OBJ)
	@echo "[LD]	$@ [lib$(NAME).so.$(MAJVER)]"
	@$(CC) -shared -Wl,-soname,lib$(NAME).so.$(MAJVER) \
		$(LDFLAGS) $(XSPS_LDFLAGS) -o $@ $(LIBXSPS_OBJ)
	@ln -sf $@ lib$(NAME).so.$(MAJVER)
	@ln -sf $@ lib$(NAME).so

## This builds all plain C files
$(TDIR)/%.c.o: $(SDIR)/%.c
	@echo "[CC]	$@"
	@mkdir -p ${@D}
	@$(CC) -c $< -o $@ $(CFLAGS) $(XSPS_CFLAGS) 

## This builds all Vala-generated C files
$(TDIR)/%.vala.o: $(TDIR)/%.c
	@echo "[CC]	$@"
	@mkdir -p ${@D}
	@$(CC) -c $< -o $@ $(CFLAGS) $(XSPS_CFLAGS)

## This generates all C code/header from all of the Vala files
$(TDIR)/%.c: $(SDIR)/%.vala
	@mkdir -p ${@D}
	@echo "[VALA]	Generating source..."
	@$(VALAC) $(VFLAGS) --header=$(XSPS_VHEAD) --library=$(NAME) $(XSPS_V)

## Strips debugging symbols from binaries
strip:
	@for f in $(BINS); do \
		if [ -f $$f ]; then \
			echo "[STRIP]	$$f" && \
			strip --strip-debug $$f; \
		fi; \
	done

## Shows the CFLAGS and LDFLAGS to help you find the required libs to build
show-flags:
	@echo "cflags: \"$(PKG_CFLAGS)\"\n"
	@echo "ldflags: \"$(PKG_LFLAGS)\"\n"
	@echo "static ldflags: \"$(PKG_STATIC)\""

## This removes all Vala-generated files, object files, the shared
## library/executable and the static library/executable
clean:
	@rm -rf $(XSPS_VHEAD) $(TDIR) $(BINS) *.so*
	@echo "[Clean]"

## Shortcut for 'clean'
c: clean

## Prevents Make from removing some files (it thinks they are temporary
## intermediate files)
.PRECIOUS: $(XSPS_VC)

## Tell Make to not do filesystem lookups for these targets
.PHONY: all strip show-flags clean c
