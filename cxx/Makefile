TARGET := xsps
SRC := $(shell find -type f -name '*.cxx')
OBJ := $(patsubst %.cxx,%.o,$(SRC))

OPTZ := -Os -pipe -mtune=generic -march=i686
DEBUG := -DDEBUG
STATIC :=
INCLUDE := -Isrc -Isrc/include
CFLAGS := -Werror $(STATIC) $(OPTZ) $(DEBUG) $(INCLUDE)
CXXFLAGS := -std=c++0x $(CFLAGS)
LDFLAGS := $(STATIC) -Wl,--as-needed

PREFIX := /usr/local
DESTDIR :=
INSTALL_DIR := $(DESTDIR)$(PREFIX)/bin
INSTALL_TARGET := $(INSTALL_DIR)/$(TARGET)

all: $(TARGET)
	@echo "[DONE]	Nothing more to be done for \`$^'."

%.o: %.cxx
	@echo "[CXX]	$@"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	@echo "[LD]	$@"
	@$(CXX) $(LDFLAGS) $^ -o $@

clean:
	@rm -rf $(OBJ) $(TARGET)
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
