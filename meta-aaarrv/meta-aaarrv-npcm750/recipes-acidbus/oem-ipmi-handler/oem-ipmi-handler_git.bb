SUMMARY = "An OEM IPMI command handler example"
DESCRIPTION = "This recipe will provide an example to implement OEM IPMI command."
HOMEPAGE = "https://example.com"
LICENSE = "CLOSED"

PR = "r0"

inherit autotools
inherit obmc-phosphor-ipmiprovider-symlink

DEPENDS += "phosphor-ipmi-host systemd sdbusplus sdbusplus-native sdbus++-native"
DEPENDS += "autoconf-archive-native"

SRC_URI = "file://src"
SRCREV = "${AUTOREV}"

S = "${WORKDIR}/src"

HOSTIPMI_PROVIDER_LIBRARY_append = " liboem-ipmi-handler.so"
NETIPMI_PROVIDER_LIBRARY_append =  " liboem-ipmi-handler.so"

# Installs files to image
FILES_${PN}_append = " ${libdir}/ipmid-providers/lib*${SOLIBS}"
FILES_${PN}_append = " ${libdir}/host-ipmid/lib*${SOLIBS}"
FILES_${PN}_append = " ${libdir}/net-ipmid/lib*${SOLIBS}"
FILES_${PN}-dev_append = " ${libdir}/ipmid-providers/lib*${SOLIBSDEV}"