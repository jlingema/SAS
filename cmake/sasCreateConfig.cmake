include(CMakePackageConfigHelpers)

configure_file(cmake/sasConfig.cmake.in "${PROJECT_BINARY_DIR}/sasConfig.cmake" @ONLY)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/sasConfigVersion.cmake
                                 VERSION ${sas_VERSION}
                                 COMPATIBILITY SameMajorVersion )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/sasConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/sasConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_PREFIX}/cmake )
