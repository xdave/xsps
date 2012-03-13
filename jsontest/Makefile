all:
	valac -b src -d . \
		--pkg=gee-1.0 --pkg=json-glib-1.0 \
		-o jsontest src/*.vala
clean:
	rm -f jsontest

.PHONY: all clean
