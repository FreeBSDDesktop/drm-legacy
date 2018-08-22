# $FreeBSD$

.if ${MACHINE_CPUARCH} == "amd64" || ${MACHINE_CPUARCH} == "i386"
_i915kms=	i915kms
_radeonkms=	radeonkms
.endif

.if ${MACHINE_CPUARCH} == "powerpc"
_radeonkms=	radeonkms
.endif

SUBDIR = \
	drm2 \
	${_i915kms} \
	${_radeonkms} \

.include <bsd.subdir.mk>
