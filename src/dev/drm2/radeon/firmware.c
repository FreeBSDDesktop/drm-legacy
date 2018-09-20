#include <sys/param.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/linker.h>
#include <sys/malloc.h>
#include <sys/firmware.h>
#include <sys/bus.h>

#include "firmware.h"

MALLOC_DEFINE(M_DRM_FW, "drmfw", "DRM Firmware");


const struct firmware *
drm_firmware_get(const char *name, struct device *device)
{
	const struct firmware *fw;
	char *mapped_name, *pindex;
	linker_file_t result;
	int rc, retries;

	mapped_name = NULL;

	retries = 0;
	fw = firmware_get(name);
	if (fw == NULL) {
		pause("fwwait", hz/2);
		fw = firmware_get(name);
	}
	if (fw == NULL &&
	    ((index(name, '/') != NULL) || (index(name, '.') != NULL))) {
		mapped_name = strdup(name, M_DRM_FW);
		if (mapped_name == NULL) {
			rc = -ENOMEM;
			goto fail;
		}
		while ((pindex = index(mapped_name, '/')) != NULL)
			*pindex = '_';
		while ((pindex = index(mapped_name, '.')) != NULL)
			*pindex = '_';
		if (linker_reference_module(mapped_name, NULL, &result)) {
			rc = -ENOENT;
			goto fail;
		}
	retry:
		pause("fwwait", hz/4);
		fw = firmware_get(name);
		if (fw == NULL) {
			fw = firmware_get(mapped_name);
			if (fw == NULL) {
				if (retries++ < 10)
					goto retry;
			}
		}

#ifdef __notyet__
		/* XXX leave dangling ref */
		linker_file_unload(result,  0);
#endif
	}
	if (fw == NULL) {
		if (mapped_name)
			device_printf(device, "Failed to load firmware "
			    "image with name (mapped name): %s (%s)\n", name, mapped_name);
		else
			device_printf(device, "Failed to load firmware "
			    "image with name: %s\n", name);
		goto fail;
	}

	if (mapped_name)
		device_printf(device, "Successfully loaded firmware "
		    "image with name (mapped name): %s (%s)\n", name, mapped_name);
	else
		device_printf(device, "Successfully loaded firmware "
		    "image with name: %s\n", name);

	free(mapped_name, M_DRM_FW);
	return fw;
fail:
	free(mapped_name, M_DRM_FW);
	return NULL;
}
