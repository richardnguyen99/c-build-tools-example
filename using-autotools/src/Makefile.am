lib_LTLIBRARIES=libwhois.la
libwhois_la_SOURCES=whois.c ../include/whois.h

bin_PROGRAMS=whoisclient whoisserver

whoisclient_SOURCES=whoisclient.c
whoisserver_SOURCES=whoisserver.c

whoisclient_LDADD=libwhois.la
whoisserver_LDADD=libwhois.la
