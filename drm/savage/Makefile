# $FreeBSD$

.PATH:	${.CURDIR:H:H}/src/dev/drm

KMOD= 	savage
CFLAGS += -I${SRCTOP}/sys/dev/drm
SRCS=	savage_bci.c savage_drv.c savage_state.c
SRCS+=	device_if.h bus_if.h pci_if.h opt_drm.h

CFLAGS+= -I${.CURDIR:H}/../src/

.include <bsd.kmod.mk>
