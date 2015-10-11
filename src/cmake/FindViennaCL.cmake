#
# Try to find ViennaCL library and include path.
# Once done this will define
#
# ViennaCL_FOUND
# ViennaCL_INCLUDE_DIRS
# 

IF (WIN32)

  set(ViennaCL_PATH_WIN32 $ENV{PROGRAMFILES}/ViennaCL CACHE PATH "ViennaCL root directory.")

  find_path(ViennaCL_INCLUDE_DIRS viennacl/forwards.h
    PATHS ${ViennaCL_PATH_WIN32}/include
	DOC "The ViennaCL include path")
  set(ViennaCL_FOUND ON)

ELSEIF(APPLE)

  find_path(ViennaCL_INCLUDE_DIRS viennacl/forwards.h
    PATHS /usr/local/include
    DOC "The ViennaCL include path")
    set(ViennaCL_FOUND ON)

ELSE (WIN32) #Linux

  find_path(ViennaCL_INCLUDE_DIRS viennacl/forwards.h
    PATHS /usr/local/include
    DOC "The ViennaCL include path")
  set(ViennaCL_FOUND ON)

ENDIF (WIN32)

