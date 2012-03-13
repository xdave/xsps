all:
	PKG_CONFIG_DIR=../pkgconfig valac --save-temps \
		--Xcc=-Wshadow --Xcc=-Wnested-externs --Xcc=-Wvla \
		--Xcc=-Wno-overlength-strings --Xcc=-ggdb --Xcc=-Werror \
		--Xcc=-Wmissing-declarations --Xcc=-Wdisabled-optimization \
		--Xcc=-lconfuse --Xcc=-Wl,--as-needed \
		--vapidir=. --pkg=confuse test-confuse.vala

clean:
	rm -f test-confuse test-confuse.c

.PHONY: all clean
