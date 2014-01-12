IF(WIN32)
	SET(LMMS_BUILD_WIN32 1)
ELSE(WIN32)
	IF(APPLE)
		SET(LMMS_BUILD_APPLE 1)
	ELSE(APPLE)
		SET(LMMS_BUILD_LINUX 1)
	ENDIF(APPLE)
ENDIF(WIN32)

MESSAGE("PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
SET(LMMS_HOST_X86 FALSE)
SET(LMMS_HOST_X86_64 FALSE)

IF(WIN32)
	IF(WIN64)
		SET(IS_X86_64 TRUE)
		SET(LMMS_BUILD_WIN64 TRUE)
	ELSE(WIN64)
		SET(IS_X86 TRUE)
	ENDIF(WIN64)
ELSE(WIN32)
	EXEC_PROGRAM( ${CMAKE_C_COMPILER} ARGS "-dumpmachine" OUTPUT_VARIABLE Machine )
	MESSAGE("Machine: ${Machine}")
	STRING(REGEX MATCH "i.86" IS_X86 "${Machine}")
	STRING(REGEX MATCH "86_64" IS_X86_64 "${Machine}")
ENDIF(WIN32)

IF(IS_X86)
	MESSAGE("-- Target host is 32 bit")
	SET(LMMS_HOST_X86 TRUE)
ELSEIF(IS_X86_64)
	MESSAGE("-- Target host is 64 bit")
	SET(LMMS_HOST_X86_64 TRUE)
ELSE(IS_X86)
	MESSAGE("Can't identify target host. Assuming 32 bit platform.")
ENDIF(IS_X86)

IF(CMAKE_INSTALL_LIBDIR)
	SET(LIB_DIR "${CMAKE_INSTALL_LIBDIR}")
ELSE(CMAKE_INSTALL_LIBDIR)
	SET(LIB_DIR lib)
ENDIF(CMAKE_INSTALL_LIBDIR)


IF(LMMS_BUILD_WIN32)
	SET(PLUGIN_DIR plugins)
	SET(DATA_DIR data)
	SET(LMMS_DATA_DIR data)
ELSE(LMMS_BUILD_WIN32)
	SET(PLUGIN_DIR ${LIB_DIR}/lmms)
	SET(DATA_DIR share)
	SET(LMMS_DATA_DIR ${DATA_DIR}/lmms)
ENDIF(LMMS_BUILD_WIN32)


