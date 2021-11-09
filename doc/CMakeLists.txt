# Handle doxygen stuff
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in" "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile" @ONLY)
	add_custom_target(doc "${DOXYGEN_EXECUTABLE}" "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile" WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}" COMMENT "Generating API documentation with Doxygen" VERBATIM)
	message(STATUS "Use target \"doc\" to run doxygen")
endif(DOXYGEN_FOUND)
