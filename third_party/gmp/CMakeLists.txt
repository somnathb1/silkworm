# # Copyright 2025 The Silkworm Authors
# # SPDX-License-Identifier: Apache-2.0

# function(expand_config_gen_expr expr build_type var)
#   string(REGEX MATCH "<CONFIG:${build_type}>:[^>]+" VALUE "${expr}")
#   string(REPLACE "<CONFIG:${build_type}>:" "" VALUE "${VALUE}")
#   set(${var}
#       "${VALUE}"
#       PARENT_SCOPE
#   )
# endfunction()

# if(GMP_LIBRARY STREQUAL "GMP_LIBRARY-NOTFOUND")
#   unset(GMP_LIBRARY CACHE)
#   unset(GMP_INCLUDE_DIR CACHE)
# endif()

if(DEFINED GMP_LIBRARY)
  add_library(gmplib STATIC IMPORTED)
  set_target_properties(gmplib PROPERTIES IMPORTED_LOCATION "${GMP_LIBRARY}")
  if(DEFINED GMP_INCLUDE_DIR)
    set_target_properties(gmplib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "${GMP_INCLUDE_DIR}")
  else()
    message(FATAL_ERROR "GMP_INCLUDE_DIR is required if a custom GMP_LIBRARY is provided")
  endif()
endif()
# else()
#   find_package(gmp REQUIRED)
#   add_custom_target(gmplib DEPENDS gmp::gmp)

#   # derive the path variables from the package for intx, libff
#   get_target_property(GMP_INCLUDE_DIR_EXPR gmp::libgmp INTERFACE_INCLUDE_DIRECTORIES)
#   expand_config_gen_expr("${GMP_INCLUDE_DIR_EXPR}" ${CMAKE_BUILD_TYPE} GMP_INCLUDE_DIR)
#   set(GMP_INCLUDE_DIR
#       "${GMP_INCLUDE_DIR}"
#       CACHE PATH ""
#   )
#   get_target_property(GMP_LIBRARY_DIR_EXPR gmp::libgmp INTERFACE_LINK_DIRECTORIES)
#   expand_config_gen_expr("${GMP_LIBRARY_DIR_EXPR}" ${CMAKE_BUILD_TYPE} GMP_LIBRARY_DIR)
#   find_library(
#     GMP_LIBRARY gmp
#     PATHS "${GMP_LIBRARY_DIR}" REQUIRED
#     NO_DEFAULT_PATH
#   )
# endif()


# ------------------------------------------------------------------
# 1. Let users override with -DGMP_LIBRARY/-DGMP_INCLUDE_DIR first
# ------------------------------------------------------------------
# if (DEFINED GMP_LIBRARY)
#     add_library(gmplib STATIC IMPORTED)
#     set_target_properties(gmplib PROPERTIES
#         IMPORTED_LOCATION "${GMP_LIBRARY}"
#         INTERFACE_INCLUDE_DIRECTORIES "${GMP_INCLUDE_DIR}")
#     return()
# endif()

# set(GMP_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/_gmp)   # staged sys-root

# # --host is the *target* triple; --build is the build machine
# set(CONFIGURE_HOST   "${CMAKE_C_COMPILER_TARGET}")
# set(CONFIGURE_BUILD  "${CMAKE_HOST_SYSTEM_PROCESSOR}-unknown-elf")

# ExternalProject_Add(gmp_external
#     SOURCE_DIR   ${CMAKE_CURRENT_LIST_DIR}/gmp-6.3.0
#     CONFIGURE_COMMAND
#         ${CMAKE_COMMAND} -E env
#             CC=${CMAKE_C_COMPILER}
#             CXX=${CMAKE_CXX_COMPILER}
#             AR=${CMAKE_AR}
#             RANLIB=${CMAKE_RANLIB}
#             ABI=32                                       # 32-bit limbs :contentReference[oaicite:0]{index=0}
#         ${CMAKE_CURRENT_LIST_DIR}/gmp-6.3.0/configure
#             --build=${CONFIGURE_BUILD}
#             --host=${CONFIGURE_HOST}
#             --prefix=<INSTALL_DIR>
#             --enable-cxx
#             --disable-assembly                           # generic C path :contentReference[oaicite:1]{index=1}
#     BUILD_COMMAND    make -j${CMAKE_JOB_POOLS_COMPILE}
#     INSTALL_COMMAND  make install
#     BUILD_IN_SOURCE  1
#     LOG_CONFIGURE ON
#     LOG_BUILD     ON
#     LOG_INSTALL   ON
# )

# # ------------------------------------------------------------------
# # 3. Surface the library + headers as an IMPORTED target
# # ------------------------------------------------------------------
# ExternalProject_Get_Property(gmp_external install_dir)

# add_library(gmplib STATIC IMPORTED GLOBAL)
# set_target_properties(gmplib PROPERTIES
#         IMPORTED_LOCATION             ${install_dir}/lib/libgmp.a
#         INTERFACE_INCLUDE_DIRECTORIES ${install_dir}/lib
#     )

# add_dependencies(gmplib gmp_external)
