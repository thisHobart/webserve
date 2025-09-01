# Find all source files
file(GLOB_RECURSE SOURCES "*.cpp")

# Define the library
add_library(sylar ${SOURCES})

# Specify public include directories
target_include_directories(sylar PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

# Link necessary libraries
# We'll need pthreads for the thread module
# We might need other libraries for hooks, ssl, etc. later
find_package(Threads REQUIRED)
target_link_libraries(sylar PRIVATE Threads::Threads)

# Note: For modules like 'config' that use yaml-cpp,
# you would add find_package(yaml-cpp REQUIRED) and link it.
# For now, we'll keep it simple.
