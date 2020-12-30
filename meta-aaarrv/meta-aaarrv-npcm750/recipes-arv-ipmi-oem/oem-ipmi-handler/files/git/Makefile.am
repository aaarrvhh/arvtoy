AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = -I m4

libdir = $(prefix)/lib/ipmid-providers

lib_LTLIBRARIES = liboem-ipmi-handler.la
liboem_ipmi_handler_la_SOURCES = oemhandler.cpp
liboem_ipmi_handler_la_LDFLAGS = -version-info 0:1:0 -shared
