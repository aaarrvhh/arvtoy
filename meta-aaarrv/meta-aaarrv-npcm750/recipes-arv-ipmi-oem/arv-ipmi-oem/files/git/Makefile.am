AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = -I m4

libdir = $(prefix)/lib/ipmid-providers

lib_LTLIBRARIES = libarv-ipmi-oem.la
libarv_ipmi_oem_la_SOURCES = oemhandler.cpp
libarv_ipmi_oem_la_LDFLAGS = -version-info 0:1:0 -shared
