# gcc build scriptlet.
#
do_configure() {
	# As specified in the LFS book, disable installing libiberty.
	sed -i 's/install_to_$(INSTALL_DEST) //' libiberty/Makefile.in
	# Do not run fixincludes
	sed -i 's@\./fixinc\.sh@-c true@' gcc/Makefile.in

	./configure --libexecdir=/usr/lib \
		--enable-clocale=gnu --disable-bootstrap --libdir=/usr/lib \
		--enable-threads=posix --enable-__cxa_atexit --enable-multilib \
		--enable-languages=c,c++,objc,obj-c++,fortran,go,lto --enable-tls \
		--disable-rpath --with-system-zlib --enable-shared --enable-lto \
		--enable-linker-build-id --enable-gnu-unique-object \
		--enable-checking=release --disable-libstdcxx-pch \
		${CONFIGURE_SHARED_ARGS}
}

do_build() {
	make ${makejobs}
}

do_install() {
	if [ "$XBPS_MACHINE" = "x86_64" ]; then
		vmkdir usr/lib
		cd ${DESTDIR}/usr && ln -sf lib lib64
	fi
	cd ${wrksrc}
	make DESTDIR=${DESTDIR} install

	# Make version a symlink of major version to make all versions
	# from the same series work automagically.
	mv ${DESTDIR}/usr/lib/gcc/${_triplet}/${version} \
		${DESTDIR}/usr/lib/gcc/${_triplet}/${_majorver}
	ln -sf /usr/lib/gcc/${_triplet}/${_majorver} \
		${DESTDIR}/usr/lib/gcc/${_triplet}/${version}

	# Ditto for c++ headers.
	mv ${DESTDIR}/usr/include/c++/${version} \
		${DESTDIR}/usr/include/c++/${_majorver}
	ln -sf /usr/include/c++/${_majorver} \
		${DESTDIR}/usr/include/c++/${version}

	# cc symlink.
	ln -sf /usr/bin/gcc ${DESTDIR}/usr/bin/cc
	# rpcgen wants /lib/cpp, make a symlink.
	vmkdir lib
	ln -sf /usr/bin/cpp ${DESTDIR}/lib/cpp
	rm -f ${DESTDIR}/usr/lib64

	# Remove libffi stuff.
	rm -f ${DESTDIR}/usr/lib/libffi*
	rm -f ${DESTDIR}/usr/share/man/man3/ffi*

	# Remove unused stuff for multilib.
	if [ "${XBPS_MACHINE}" = "x86_64" ]; then
		rm -f ${DESTDIR}/usr/lib32/libffi*
		rm -f ${DESTDIR}/usr/lib32/libgfortran*
		rm -f ${DESTDIR}/usr/lib32/libgo.{a,so*}
		rm -f ${DESTDIR}/usr/lib32/libgobegin.a
		rm -f ${DESTDIR}/usr/lib32/libquadmath*
		rm -rf ${DESTDIR}/usr/lib32/go
	fi

	# Remove all python scripts in libdir.
	rm -f ${DESTDIR}/usr/lib/*.py

	# Remove more python stuff.
	if [ -d ${DESTDIR}/usr/share/gcc-${version}/python ]; then
		rm -rf ${DESTDIR}/usr/share/gcc-${version}/python
	fi

	# Install c89 and c99 wrappers and its manpages, from NetBSD.
	for f in c89 c99; do
		vinstall ${FILESDIR}/${f}.sh 755 usr/bin ${f}
		vinstall ${FILESDIR}/${f}.1 644 usr/share/man/man1 ${f}.1
	done
}
