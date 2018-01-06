# VideoPlayer
A basic video player using FFmpeg, OpenGL4 and wxWidgets

At this point in time I have not made a new branch of wxWidgets with the changes I made to support building.

Change Format:
filename:line number (CMakeLists.txt:1)
original >> new


These changes are:

${wx}/build/cmake/functions.cmake:76
if (wxBUILD_CXX_STANDARD EQUAL 11 OR wxBUILD_CXX_STANDARD EQUAL 14) >> if (wxBUILD_CXX_STANDARD EQUAL 11 OR wxBUILD_CXX_STANDARD EQUAL 14 OR wxBUILD_CXX_STANDARD EQUAL 17)

${wx}/build/cmake/options.cmake:36
${wxCXX_STANDARD_DEFAULT} STRINGS COMPILER_DEFAULT 98 11 14) >> ${wxCXX_STANDARD_DEFAULT} STRINGS COMPILER_DEFAULT 98 11 14 17)