# $FreeBSD$

.PATH:	${.CURDIR:H:H}/src/dev/drm

KMOD= 	sis
SRCS=	sis_drv.c sis_ds.c sis_mm.c
SRCS+=	device_if.h bus_if.h pci_if.h opt_drm.h

CFLAGS+= -I${.CURDIR:H}/../src/

.include <bsd.kmod.mk>
