# List all header .hpp files. If CHECK_RECURSIVELY is set to TRUE
# traverse all subdirectories
macro(ListHeaderFiles CHECK_RECURSIVELY OUTPUT CURRENT_DIR)
  if(${CHECK_RECURSIVELY})
	file(GLOB_RECURSE ${OUTPUT} ${CURRENT_DIR}/include/*.hpp)
  else()
	file(GLOB ${OUTPUT} ${CURRENT_DIR}/include/*.hpp)
  endif()
endmacro()

# List all source .cpp files. If CHECK_RECURSIVELY is set to TRUE
# traverse all subdirectories
macro(ListSourceFiles CHECK_RECURSIVELY OUTPUT CURRENT_DIR)
  if(${CHECK_RECURSIVELY})
	file(GLOB_RECURSE ${OUTPUT} ${CURRENT_DIR}/source/*.cpp)
  else()
	file(GLOB ${OUTPUT} ${CURRENT_DIR}/source/*.cpp)
  endif()
endmacro()