#ifndef _FIRMWARE_H_
#define _FIRMWARE_H_

const struct firmware *
drm_firmware_get(const char *name, struct device *device);

#endif
