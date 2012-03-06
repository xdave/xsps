do_install() {
	if [ "${XBPS_MACHINE}" = "i686" ]; then
		arch=i386
	else
		arch=${XBPS_MACHINE}
	fi

	tar xfz ${XBPS_SRCDISTDIR}/install_flash_player_11_linux.${arch}.tar.gz

	vinstall libflashplayer.so 755 usr/lib/mozilla/plugins
	#vinstall usr/lib/kde4/kcm_adobe_flash_player.so 755 usr/lib/kde4
	vinstall usr/bin/flash-player-properties 755 usr/bin
	for i in 16x16 22x22 24x24 32x32 48x48; do
		vinstall usr/share/icons/hicolor/${i}/apps/flash-player-properties.png \
		644 usr/share/icons/hicolor/${i}/apps
	done
	vinstall usr/share/applications/flash-player-properties.desktop 644 \
		usr/share/applications
	vinstall usr/share/kde4/services/kcm_adobe_flash_player.desktop 644 \
		usr/share/kde4/services
	vinstall ${XBPS_SRCDISTDIR}/PlatformClients_PC_WWEULA_Combined_20100108_1657.pdf 644 \
		usr/share/licenses/${pkgname} LICENSE.pdf
}
