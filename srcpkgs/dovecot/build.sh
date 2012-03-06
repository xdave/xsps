post_install() {
	local econfdir=usr/share/doc/dovecot/example-config
	local econfdird=${econfdir}/conf.d

	# install example conf files and ssl.conf
	vmkdir etc/dovecot/conf.d
	install -m644 ${DESTDIR}/${econfdird}/*.conf \
		${DESTDIR}/etc/dovecot/conf.d
	install -m644 ${DESTDIR}/${econfdird}/*.conf.ext \
		${DESTDIR}/etc/dovecot/conf.d
	install -m644 ${DESTDIR}/${econfdir}/dovecot.conf ${DESTDIR}/etc/dovecot
	vinstall doc/dovecot-openssl.cnf 644 etc/ssl
	vinstall doc/mkcert.sh 755 usr/sbin dovecot-mkcert.sh
	rm ${DESTDIR}/etc/dovecot/README

	# Remove development stuff.
	rm -rf ${DESTDIR}/usr/include
	rm -rf ${DESTDIR}/usr/share/aclocal
}
