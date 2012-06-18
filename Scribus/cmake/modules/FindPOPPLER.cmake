IF (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} LESS 2.5)
	INCLUDE(UsePkgConfig)
	PKGCONFIG(poppler _libPopplerIncDir _libPopplerLinkDir _libPopplerLinkFlags _libPopplerCflags)
    SET(PKG_POPPLER_INCLUDE_DIRS ${_libPopplerIncDir})
    SET(PKG_POPPLER_LIBRARIES ${_libPopplerLinkDir})
 ELSE (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} LESS 2.5)
    INCLUDE(FindPkgConfig)
    pkg_search_module(POPPLER libpoppler>=0.17.1 poppler>=0.17.1)
 ENDIF (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} LESS 2.5)
FIND_PATH(POPPLER_INCLUDE_DIR 
  NAMES poppler-config.h
  PATHS ${PKG_POPPLER_INCLUDE_DIRS} ${POPPLER_INCLUDE_DIRS} /usr/local/include /usr/include
  PATH_SUFFIXES poppler
  NO_DEFAULT_PATH
)

FIND_LIBRARY(POPPLER_LIBRARY
  NAMES libpoppler poppler
<<<<<<< HEAD
  PATHS ${PKG_POPPLER_LIBRARIES} ${POPPLER_LIBRARY_DIRS} /usr/local/lib /usr/lib /usr/lib/x86_64-linux-gnu
=======
  PATHS ${PKG_POPPLER_LIBRARIES} ${POPPLER_LIBRARY_DIRS} /usr/local/lib /usr/lib
>>>>>>> bea5ac5c4844d7b78798edca794c0a7bf0155c96
  NO_DEFAULT_PATH
)
IF (POPPLER_LIBRARY)
  IF (POPPLER_INCLUDE_DIR)
	SET( FOUND_POPPLER 1 )
    SET( POPPLER_LIBRARIES ${POPPLER_LIBRARY} )
    SET( POPPLER_INCLUDES ${POPPLER_INCLUDE_DIR})
  ENDIF (POPPLER_INCLUDE_DIR)
ENDIF (POPPLER_LIBRARY)