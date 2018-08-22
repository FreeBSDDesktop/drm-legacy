# $FreeBSD$

.PATH:	${.CURDIR:H:H}/src/dev/drm

KMOD	= r128
SRCS	= r128_cce.c r128_drv.c r128_irq.c r128_state.c
SRCS	+=device_if.h bus_if.h pci_if.h opt_drm.h

.include <bsd.kmod.mk>

CFLAGS+= -I${.CURDIR:H}/../src/

CWARNFLAGS.r128_cce.c=		-Wno-unused ${NO_WCONSTANT_CONVERSION}
CWARNFLAGS.r128_state.c=	-Wno-unused
