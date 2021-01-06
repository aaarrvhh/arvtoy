SUMMARY = "An OEM IPMI command handler example"
DESCRIPTION = "This recipe will provide an example to implement OEM IPMI command."
HOMEPAGE = "https://example.com"
LICENSE = "CLOSED"

PR = "r0"

inherit autotools
inherit obmc-phosphor-ipmiprovider-symlink

DEPENDS = "phosphor-ipmi-host"
#DEPENDS += "sdbusplus \
#            sdbusplus-native \
#            sdbus++-native"

#below is for github
#SRC_URI = "git://github.com/aaarrrvhh/aci_oemipmihandler;protocol=https;branch=master"
#SRC_URI[md5sum] = "cf1f360ea788a7916f14397ab63ed0bf"

#below is for local
SRC_URI= "file://git"
#SRC_URI = "file://Makefile.am \
#           file://configure.ac \
#           file://oemhandler.cpp"
#SRC_URI = "file://oemhandler.cpp \
#           file://chassis \
#           "
SRCREV = "${AUTOREV}"
#SRCREV = "c58b1ec32753f3380ae35f36944417bdd0627723"

# ‘S’ = The location in the Build Directory where unpacked recipe source code resides.
S = "${WORKDIR}/git"
# S = "${WORKDIR}/src"

# ‘B’ = The directory within the Build Directory in which the OpenEmbedded build system
#         places generated objects during a recipe's build process.
# B = "${WORKDIR}/build"

HOSTIPMI_PROVIDER_LIBRARY_append = " libarv-ipmi-oem.so"
NETIPMI_PROVIDER_LIBRARY_append = " libarv-ipmi-oem.so"

# Installs files to image
FILES_${PN}_append = " ${libdir}/ipmid-providers/lib*${SOLIBS}"
FILES_${PN}_append = " ${libdir}/host-ipmid/lib*${SOLIBS}"
FILES_${PN}_append = " ${libdir}/net-ipmid/lib*${SOLIBS}"
FILES_${PN}-dev_append = " ${libdir}/ipmid-providers/lib*${SOLIBSDEV}"

