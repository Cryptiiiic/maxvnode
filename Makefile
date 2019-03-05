export ARCHS = armv7 arm64
export TARGET = iphone:clang:9.2:6.0
DEBUG = 0
FINALPACKAGE = 1
PACKAGE_VERSION = $(THEOS_PACKAGE_BASE_VERSION)

include $(THEOS)/makefiles/common.mk

TOOL_NAME = maxvnode++
maxvnode++_FILES = maxvnode++.c
maxvnode++_CFLAGS += -fvisibility=hidden
maxvnode++_FRAMEWORKS = CoreFoundation
maxvnode++_CODESIGN_FLAGS = -Sent.xml

include $(THEOS_MAKE_PATH)/tool.mk

purge::
	@rm -Rf .theos packages
	@find . -name .DS_Store -delete
	$(ECHO_BEGIN)$(PRINT_FORMAT_RED) "Purging"$(ECHO_END); $(ECHO_PIPEFAIL)

after-stage::
	$(FAKEROOT) chown 0:0 $(THEOS_STAGING_DIR)/Library/LaunchDaemons/com.cryptic.maxvnode++.plist
	$(FAKEROOT) chmod 6755 $(THEOS_STAGING_DIR)/Library/LaunchDaemons/com.cryptic.maxvnode++.plist
