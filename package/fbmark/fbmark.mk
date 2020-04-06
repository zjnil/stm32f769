################################################################################
#
# fbmark
#
################################################################################

FBMARK_VERSION = master
FBMARK_SITE = $(call github,caramelli,fbmark,$(FBMARK_VERSION))
FBMARK_LICENSE = GPL-2.0
FBMARK_LICENSE_FILES = COPYING

define FBMARK_BUILD_CMDS
	$(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(@D) all
endef

define FBMARK_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/fb_mandelbrot $(TARGET_DIR)/usr/bin/fb_mandelbrot
	$(INSTALL) -D -m 0755 $(@D)/fb_rectangle $(TARGET_DIR)/usr/bin/fb_rectangle
	$(INSTALL) -D -m 0755 $(@D)/fb_sierpinski $(TARGET_DIR)/usr/bin/fb_sierpinski
endef

define FBMARK_PERMISSIONS
	/bin/fb_rectangle f 666 fbmark_rectangle
endef

$(eval $(generic-package))
