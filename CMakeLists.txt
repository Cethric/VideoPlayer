cmake_minimum_required(VERSION 3.9)
project(VideoPlayer)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG -O3")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DNDEBUG -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)

set(wxBUILD_SHARED ON CACHE BOOL "" FORCE)
set(wxBUILD_MONOLITHIC OFF CACHE BOOL "" FORCE)
set(wxBUILD_SAMPLES "OFF" CACHE STRING "" FORCE)
set(wxBUILD_TESTS OFF CACHE BOOL "" FORCE)
set(wxBUILD_DEMOS OFF CACHE BOOL "" FORCE)
set(wxBUILD_PRECOMP OFF CACHE BOOL "" FORCE)
set(wxBUILD_INSTALL OFF CACHE BOOL "" FORCE)
set(wxBUILD_COMPATIBILITY "3.1" CACHE STRING "" FORCE)
set(wxBUILD_VENDOR "custom" CACHE STRING "" FORCE)
set(wxBUILD_USE_STATIC_RUNTIME OFF CACHE BOOL "" FORCE)

set(wxUSE_STL OFF CACHE BOOL "" FORCE)
set(wxUSE_STD_CONTAINERS OFF CACHE BOOL "" FORCE)
set(wxUSE_UNICODE ON CACHE BOOL "" FORCE)
set(wxUSE_COMPILER_TLS ON CACHE BOOL "" FORCE)
set(wxUSE_VISIBILITY ON CACHE BOOL "" FORCE)

set(wxUSE_OPENGL ON CACHE BOOL "" FORCE)

set(wxUSE_LIBICONV OFF CACHE BOOL "" FORCE)
set(wxUSE_INTL ON CACHE BOOL "" FORCE)
set(wxUSE_XLOCALE ON CACHE BOOL "" FORCE)
set(wxUSE_CONFIG ON CACHE BOOL "" FORCE)

set(wxUSE_URL ON CACHE BOOL "" FORCE)
set(wxUSE_PROTOCOL ON CACHE BOOL "" FORCE)
set(wxUSE_PROTOCOL_FTP ON CACHE BOOL "" FORCE)
set(wxUSE_PROTOCOL_HTTP ON CACHE BOOL "" FORCE)
set(wxUSE_PROTOCOL_FILE ON CACHE BOOL "" FORCE)
set(wxUSE_SOCKETS ON CACHE BOOL "" FORCE)
set(wxUSE_IPV6 ON CACHE BOOL "" FORCE)

set(wxUSE_OLE ON CACHE BOOL "" FORCE)

set(wxUSE_DATAOBJ ON CACHE BOOL "" FORCE)

set(wxUSE_IPC ON CACHE BOOL "" FORCE)

set(wxUSE_CONSOLE_EVENTLOOP ON CACHE BOOL "" FORCE)

set(wxUSE_ANY ON CACHE BOOL "" FORCE)
set(wxUSE_APPLE_IEEE ON CACHE BOOL "" FORCE)
set(wxUSE_ARCHIVE_STREAMS ON CACHE BOOL "" FORCE)
set(wxUSE_BASE64 ON CACHE BOOL "" FORCE)
set(wxUSE_STACKWALKER ON CACHE BOOL "" FORCE)
set(wxUSE_ON_FATAL_EXCEPTION ON CACHE BOOL "" FORCE)
set(wxUSE_CMDLINE_PARSER ON CACHE BOOL "" FORCE)
set(wxUSE_DATETIME ON CACHE BOOL "" FORCE)
set(wxUSE_DEBUGREPORT ON CACHE BOOL "" FORCE)
set(wxUSE_DIALUP_MANAGER OFF CACHE BOOL "" FORCE)
set(wxUSE_DYNLIB_CLASS ON CACHE BOOL "" FORCE)
set(wxUSE_DYNAMIC_LOADER ON CACHE BOOL "" FORCE)
set(wxUSE_EXCEPTIONS ON CACHE BOOL "" FORCE)
set(wxUSE_EXTENDED_RTTI OFF CACHE BOOL "" FORCE)
set(wxUSE_FFILE ON CACHE BOOL "" FORCE)
set(wxUSE_FILE ON CACHE BOOL "" FORCE)
set(wxUSE_FILE_HISTORY ON CACHE BOOL "" FORCE)
set(wxUSE_FILESYSTEM ON CACHE BOOL "" FORCE)
set(wxUSE_FONTENUM ON CACHE BOOL "" FORCE)
set(wxUSE_FONTMAP ON CACHE BOOL "" FORCE)
set(wxUSE_FS_ARCHIVE ON CACHE BOOL "" FORCE)
set(wxUSE_FS_INET ON CACHE BOOL "" FORCE)
set(wxUSE_FS_ZIP ON CACHE BOOL "" FORCE)
set(wxUSE_FSVOLUME ON CACHE BOOL "" FORCE)
set(wxUSE_FSWATCHER ON CACHE BOOL "" FORCE)
set(wxUSE_GEOMETRY ON CACHE BOOL "" FORCE)
set(wxUSE_LOG ON CACHE BOOL "" FORCE)
set(wxUSE_LONGLONG ON CACHE BOOL "" FORCE)
set(wxUSE_MIMETYPE ON CACHE BOOL "" FORCE)
set(wxUSE_PRINTF_POS_PARAMS OFF CACHE BOOL "" FORCE)
set(wxUSE_SECRETSTORE OFF CACHE BOOL "" FORCE)
set(wxUSE_SNGLINST_CHECKER ON CACHE BOOL "" FORCE)
set(wxUSE_SOUND OFF CACHE BOOL "" FORCE)
set(wxUSE_STDPATHS ON CACHE BOOL "" FORCE)
set(wxUSE_STOPWATCH ON CACHE BOOL "" FORCE)
set(wxUSE_STREAMS ON CACHE BOOL "" FORCE)
set(wxUSE_SYSTEM_OPTIONS ON CACHE BOOL "" FORCE)
set(wxUSE_TARSTREAM ON CACHE BOOL "" FORCE)
set(wxUSE_TEXTBUFFER ON CACHE BOOL "" FORCE)
set(wxUSE_TEXTFILE ON CACHE BOOL "" FORCE)
set(wxUSE_TIMER ON CACHE BOOL "" FORCE)
set(wxUSE_VARIANT ON CACHE BOOL "" FORCE)
set(wxUSE_ZIPSTREAM ON CACHE BOOL "" FORCE)

set(wxUSE_THREADS ON CACHE BOOL "" FORCE)

set(wxUSE_DBGHELP_DEFAULT ON CACHE BOOL "" FORCE)
set(wxUSE_DBGHELP ON CACHE BOOL "" FORCE)

set(wxUSE_INICONF ON CACHE BOOL "" FORCE)
set(wxUSE_REGKEY ON CACHE BOOL "" FORCE)


set(wxUSE_GUI ON CACHE BOOL "" FORCE)

set(wxUSE_DOC_VIEW_ARCHITECTURE OFF CACHE BOOL "" FORCE)
set(wxUSE_HELP ON CACHE BOOL "" FORCE)
set(wxUSE_MS_HTML_HELP ON CACHE BOOL "" FORCE)
set(wxUSE_WXHTML_HELP ON CACHE BOOL "" FORCE)
set(wxUSE_XRC ON CACHE BOOL "" FORCE)
set(wxUSE_AUI ON CACHE BOOL "" FORCE)
set(wxUSE_PROPGRID ON CACHE BOOL "" FORCE)
set(wxUSE_RIBBON OFF CACHE BOOL "" FORCE)
set(wxUSE_STC OFF CACHE BOOL "" FORCE)
set(wxUSE_CONSTRAINTS ON CACHE BOOL "" FORCE)
set(wxUSE_LOGGUI ON CACHE BOOL "" FORCE)
set(wxUSE_LOGWINDOW ON CACHE BOOL "" FORCE)
set(wxUSE_LOGDIALOG OFF CACHE BOOL "" FORCE)
set(wxUSE_MDI OFF CACHE BOOL "" FORCE)
set(wxUSE_MDI_ARCHITECTURE OFF CACHE BOOL "" FORCE)
set(wxUSE_MEDIACTRL ON CACHE BOOL "" FORCE)
set(wxUSE_RICHTEXT ON CACHE BOOL "" FORCE)
set(wxUSE_POSTSCRIPT OFF CACHE BOOL "" FORCE)
set(wxUSE_PRINTING_ARCHITECTURE OFF CACHE BOOL "" FORCE)
set(wxUSE_SVG OFF CACHE BOOL "" FORCE)
set(wxUSE_WEBKIT OFF CACHE BOOL "" FORCE)
set(wxUSE_WEBVIEW ON CACHE BOOL "" FORCE)
set(wxUSE_GRAPHICS_CONTEXT OFF CACHE BOOL "" FORCE)
set(wxUSE_CLIPBOARD ON CACHE BOOL "" FORCE)
set(wxUSE_DRAG_AND_DROP ON CACHE BOOL "" FORCE)

set(wxUSE_CONTROLS ON CACHE BOOL "" FORCE)
set(wxUSE_MARKUP ON CACHE BOOL "" FORCE)
set(wxUSE_ACCEL ON CACHE BOOL "" FORCE)
set(wxUSE_ACTIVITYINDICATOR OFF CACHE BOOL "" FORCE)
set(wxUSE_ADDREMOVECTRL OFF CACHE BOOL "" FORCE)
set(wxUSE_ANIMATIONCTRL OFF CACHE BOOL "" FORCE)
set(wxUSE_BANNERWINDOW OFF CACHE BOOL "" FORCE)
set(wxUSE_ARTPROVIDER_STD ON CACHE BOOL "" FORCE)
set(wxUSE_ARTPROVIDER_TANGO ON CACHE BOOL "" FORCE)
set(wxUSE_BMPBUTTON ON CACHE BOOL "" FORCE)
set(wxUSE_BITMAPCOMBOBOX OFF CACHE BOOL "" FORCE)
set(wxUSE_BUTTON ON CACHE BOOL "" FORCE)
set(wxUSE_CALENDARCTRL ON CACHE BOOL "" FORCE)
set(wxUSE_CARET ON CACHE BOOL "" FORCE)
set(wxUSE_CHECKBOX ON CACHE BOOL "" FORCE)
set(wxUSE_CHECKLISTBOX ON CACHE BOOL "" FORCE)
set(wxUSE_CHOICE ON CACHE BOOL "" FORCE)
set(wxUSE_CHOICEBOOK OFF CACHE BOOL "" FORCE)
set(wxUSE_COLLPANE ON CACHE BOOL "" FORCE)
set(wxUSE_COLOURPICKERCTRL ON CACHE BOOL "" FORCE)
set(wxUSE_COMBOBOX ON CACHE BOOL "" FORCE)
set(wxUSE_COMBOCTRL ON CACHE BOOL "" FORCE)
set(wxUSE_COMMANDLINKBUTTON OFF CACHE BOOL "" FORCE)
set(wxUSE_DATAVIEWCTRL ON CACHE BOOL "" FORCE)
set(wxUSE_DATEPICKCTRL ON CACHE BOOL "" FORCE)
set(wxUSE_DETECT_SM OFF CACHE BOOL "" FORCE)
set(wxUSE_DIRPICKERCTRL ON CACHE BOOL "" FORCE)
set(wxUSE_DISPLAY ON CACHE BOOL "" FORCE)
set(wxUSE_EDITABLELISTBOX ON CACHE BOOL "" FORCE)
set(wxUSE_FILECTRL ON CACHE BOOL "" FORCE)
set(wxUSE_FILEPICKERCTRL ON CACHE BOOL "" FORCE)
set(wxUSE_FONTPICKERCTRL ON CACHE BOOL "" FORCE)
set(wxUSE_GAUGE ON CACHE BOOL "" FORCE)
set(wxUSE_GRID ON CACHE BOOL "" FORCE)
set(wxUSE_HEADERCTRL ON CACHE BOOL "" FORCE)
set(wxUSE_HYPERLINKCTRL ON CACHE BOOL "" FORCE)
set(wxUSE_IMAGLIST ON CACHE BOOL "" FORCE)
set(wxUSE_INFOBAR OFF CACHE BOOL "" FORCE)
set(wxUSE_LISTBOOK OFF CACHE BOOL "" FORCE)
set(wxUSE_LISTBOX ON CACHE BOOL "" FORCE)
set(wxUSE_LISTCTRL ON CACHE BOOL "" FORCE)
set(wxUSE_NOTEBOOK ON CACHE BOOL "" FORCE)
set(wxUSE_NOTIFICATION_MESSAGE OFF CACHE BOOL "" FORCE)
set(wxUSE_ODCOMBOBOX ON CACHE BOOL "" FORCE)
set(wxUSE_POPUPWIN ON CACHE BOOL "" FORCE)
set(wxUSE_PREFERENCES_EDITOR ON CACHE BOOL "" FORCE)
set(wxUSE_RADIOBOX ON CACHE BOOL "" FORCE)
set(wxUSE_RADIOBTN ON CACHE BOOL "" FORCE)
set(wxUSE_RICHMSGDLG ON CACHE BOOL "" FORCE)
set(wxUSE_RICHTOOLTIP ON CACHE BOOL "" FORCE)
set(wxUSE_REARRANGECTRL OFF CACHE BOOL "" FORCE)
set(wxUSE_SASH ON CACHE BOOL "" FORCE)
set(wxUSE_SCROLLBAR ON CACHE BOOL "" FORCE)
set(wxUSE_SEARCHCTRL ON CACHE BOOL "" FORCE)
set(wxUSE_SLIDER ON CACHE BOOL "" FORCE)
set(wxUSE_SPINBTN ON CACHE BOOL "" FORCE)
set(wxUSE_SPINCTRL ON CACHE BOOL "" FORCE)
set(wxUSE_SPLITTER ON CACHE BOOL "" FORCE)
set(wxUSE_STATBMP ON CACHE BOOL "" FORCE)
set(wxUSE_STATBOX ON CACHE BOOL "" FORCE)
set(wxUSE_STATLINE ON CACHE BOOL "" FORCE)
set(wxUSE_STATTEXT ON CACHE BOOL "" FORCE)
set(wxUSE_STATUSBAR ON CACHE BOOL "" FORCE)
set(wxUSE_TASKBARBUTTON ON CACHE BOOL "" FORCE)
set(wxUSE_TASKBARICON ON CACHE BOOL "" FORCE)
set(wxUSE_TOOLBAR_NATIVE ON CACHE BOOL "" FORCE)
set(wxUSE_TEXTCTRL ON CACHE BOOL "" FORCE)
set(wxUSE_TIMEPICKCTRL ON CACHE BOOL "" FORCE)
set(wxUSE_TIPWINDOW ON CACHE BOOL "" FORCE)
set(wxUSE_TOGGLEBTN ON CACHE BOOL "" FORCE)
set(wxUSE_TOOLBAR ON CACHE BOOL "" FORCE)
set(wxUSE_TOOLBOOK ON CACHE BOOL "" FORCE)
set(wxUSE_TREEBOOK ON CACHE BOOL "" FORCE)
set(wxUSE_TREECTRL ON CACHE BOOL "" FORCE)
set(wxUSE_TREELISTCTRL ON CACHE BOOL "" FORCE)

set(wxUSE_COMMONDLGS ON CACHE BOOL "" FORCE)
set(wxUSE_ABOUTDLG ON CACHE BOOL "" FORCE)
set(wxUSE_CHOICEDLG ON CACHE BOOL "" FORCE)
set(wxUSE_COLOURDLG ON CACHE BOOL "" FORCE)
set(wxUSE_FILEDLG ON CACHE BOOL "" FORCE)
set(wxUSE_FINDREPLDLG ON CACHE BOOL "" FORCE)
set(wxUSE_FONTDLG ON CACHE BOOL "" FORCE)
set(wxUSE_DIRDLG ON CACHE BOOL "" FORCE)
set(wxUSE_MSGDLG ON CACHE BOOL "" FORCE)
set(wxUSE_NUMBERDLG ON CACHE BOOL "" FORCE)
set(wxUSE_TEXTDLG ON CACHE BOOL "" FORCE)
set(wxUSE_STARTUP_TIPS ON CACHE BOOL "" FORCE)
set(wxUSE_PROGRESSDLG ON CACHE BOOL "" FORCE)
set(wxUSE_WIZARDDLG ON CACHE BOOL "" FORCE)

set(wxUSE_MENUS ON CACHE BOOL "" FORCE)
set(wxUSE_MINIFRAME ON CACHE BOOL "" FORCE)
set(wxUSE_TOOLTIPS ON CACHE BOOL "" FORCE)
set(wxUSE_SPLINES ON CACHE BOOL "" FORCE)
set(wxUSE_MOUSEWHEEL ON CACHE BOOL "" FORCE)
set(wxUSE_VALIDATORS ON CACHE BOOL "" FORCE)
set(wxUSE_BUSYINFO ON CACHE BOOL "" FORCE)
set(wxUSE_HOTKEY ON CACHE BOOL "" FORCE)
set(wxUSE_JOYSTICK ON CACHE BOOL "" FORCE)
set(wxUSE_METAFILE ON CACHE BOOL "" FORCE)
set(wxUSE_DRAGIMAGE ON CACHE BOOL "" FORCE)
set(wxUSE_ACCESSIBILITY OFF CACHE BOOL "" FORCE) # MinGW 64 (MSYS2) does not like this. (Multiple definitions)
set(wxUSE_UIACTIONSIMULATOR ON CACHE BOOL "" FORCE)
set(wxUSE_DC_TRANSFORM_MATRIX ON CACHE BOOL "" FORCE)
set(wxUSE_WEBVIEW_WEBKIT ON CACHE BOOL "" FORCE)

set(wxUSE_PALETTE ON CACHE BOOL "" FORCE)
set(wxUSE_IMAGE ON CACHE BOOL "" FORCE)
set(wxUSE_GIF ON CACHE BOOL "" FORCE)
set(wxUSE_PCX ON CACHE BOOL "" FORCE)
set(wxUSE_TGA ON CACHE BOOL "" FORCE)
set(wxUSE_IFF ON CACHE BOOL "" FORCE)
set(wxUSE_PNM ON CACHE BOOL "" FORCE)
set(wxUSE_XPM ON CACHE BOOL "" FORCE)
set(wxUSE_ICO_CUR ON CACHE BOOL "" FORCE)

set(wxUSE_DC_CACHEING ON CACHE BOOL "" FORCE)
set(wxUSE_POSTSCRIPT_ARCHITECTURE_IN_MSW OFF CACHE BOOL "" FORCE)
set(wxUSE_OWNER_DRAWN ON CACHE BOOL "" FORCE)
set(wxUSE_UXTHEME ON CACHE BOOL "" FORCE)
set(wxUSE_DIB OFF CACHE BOOL "" FORCE)
set(wxUSE_WEBVIEW_IE ON CACHE BOOL "" FORCE)
set(wxDEFAULT_wxUSE_AUTOID_MANAGEMENT ON CACHE BOOL "" FORCE)
set(wxUSE_AUTOID_MANAGEMENT ON CACHE BOOL "" FORCE)

add_subdirectory(ext/wxWidgets)

include(ExternalProject)

if (WIN32)
    set(MSYS_CMD D:\\MSYS2\\msys2_shell.cmd -no-start -mingw64 -defterm -where ${CMAKE_BINARY_DIR}/ext/FFmpeg -full-path)
    #    set(FF_CONFIGURE "${MSYS_CMD} -c ${CMAKE_SOURCE_DIR}/ext/FFmpeg/configure --prefix=${CMAKE_BINARY_DIR}/ext/FFmpeg/INSTALL")
    set(FF_CONFIGURE ${CMAKE_COMMAND} -E echo configure) # TODO Don't rely on external configure (jobserver-auth invalid)
    #    set(FF_BUILD "${MSYS_CMD} make")
    set(FF_BUILD ${CMAKE_COMMAND} -E echo build) # TODO Don't rely on external build (jobserver-auth invalid)
    #    set(FF_INSTALL ${MSYS_CMD} -c make install)
    set(FF_INSTALL ${CMAKE_COMMAND} -E echo install) # TODO Don't rely on external install (jobserver-auth invalid)
else ()
    set(FF_CONFIGURE "${CMAKE_SOURCE_DIR}/ext/FFmpeg/configure --prefix=${CMAKE_BINARY_DIR}/ext/FFmpeg/INSTALL")
    set(FF_BUILD "make")
    set(FF_INSTALL "make install")
endif (WIN32)

ExternalProject_Add(
        FFmpegBuild
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/ext/FFmpeg
        CONFIGURE_COMMAND ${FF_CONFIGURE}
        CMAKE_COMMAND ""
        BINARY_DIR ${CMAKE_BINARY_DIR}/ext/FFmpeg
        BUILD_COMMAND ${FF_BUILD}
        BUILD_IN_SOURCE 0
        INSTALL_DIR ${CMAKE_BINARY_DIR}/ext/FFmpeg/INSTALL
        INSTALL_COMMAND ${FF_INSTALL}
        TEST_BEFORE_INSTALL 0
        TEST_AFTER_INSTALL 0
        TEST_EXCLUDE_FROM_MAIN 0
        TEST_COMMAND ""
        USES_TERMINAL_CONFIGURE 1
)

ExternalProject_Get_Property(FFmpegBuild install_dir)

if (WIN32)
    set(
            AV_LIBRARIES
            ${install_dir}/lib/libavcodec.dll.a
            ${install_dir}/lib/libavdevice.dll.a
            ${install_dir}/lib/libavfilter.dll.a
            ${install_dir}/lib/libavformat.dll.a
            ${install_dir}/lib/libavutil.dll.a
            ${install_dir}/lib/libswresample.dll.a
            ${install_dir}/lib/libswscale.dll.a
            CACHE INTERNAL "" FORCE
            #            PARENT_SCOPE
    )
elseif (APPLE) # TODO Check that these link values are correct
    set(
            AV_LIBRARIES
            ${install_dir}/lib/libavcodec.dylib
            ${install_dir}/lib/libavdevice.dylib
            ${install_dir}/lib/libavfilter.dylib
            ${install_dir}/lib/libavformat.dylib
            ${install_dir}/lib/libavutil.dylib
            ${install_dir}/lib/libswresample.dylib
            ${install_dir}/lib/libswscale.dylib
            CACHE INTERNAL "" FORCE
            #            PARENT_SCOPE
    )
else () # TODO Check that these link values are correct
    set(
            AV_LIBRARIES
            ${install_dir}/lib/libavcodec.so
            ${install_dir}/lib/libavdevice.so
            ${install_dir}/lib/libavfilter.so
            ${install_dir}/lib/libavformat.so
            ${install_dir}/lib/libavutil.so
            ${install_dir}/lib/libswresample.so
            ${install_dir}/lib/libswscale.so
            CACHE INTERNAL "" FORCE
            #            PARENT_SCOPE
    )
endif ()

set(
        AV_INCLUDES
        ${install_dir}/include
        CACHE INTERNAL "" FORCE
        #        PARENT_SCOPE
)

set(
        VP_SOURCES
        src/main.cpp
)

set(GLM_DYNAMIC_LIBRARY_ENABLE ON CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE_CXX_17 ON CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE_LANG_EXTENSIONS ON CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE_FAST_MATH ON CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE_SIMD_SSE2 ON CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE_SIMD_SSE3 ON CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE_SIMD_AVX ON CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE_SIMD_AVX2 ON CACHE BOOL "" FORCE)
set(GLM_INSTALL_ENABLE OFF CACHE BOOL "" FORCE)
add_subdirectory(ext/glm)

set(GLAD_PROFILE "core" CACHE STRING "" FORCE)
set(GLAD_API "gl=4.6" CACHE STRING "" FORCE)
set(GLAD_GENERATOR "c" CACHE STRING "" FORCE)
set(GLAD_EXTENSIONS "" CACHE STRING "" FORCE)
set(GLAD_SPEC "gl" CACHE STRING "" FORCE)
set(GLAD_NO_LOADER OFF CACHE BOOL "" FORCE)
set(GLAD_EXPORT ON CACHE BOOL "" FORCE)
set(GLAD_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(ext/glad)

add_subdirectory(application)
add_subdirectory(player)

add_executable(VideoPlayer ${VP_SOURCES})

add_dependencies(VideoPlayer FFmpegBuild)

target_include_directories(
        VideoPlayer
        PUBLIC
        ${AV_INCLUDES}
)

target_link_libraries(
        VideoPlayer
        ${AV_LIBRARIES}
)

target_include_directories(
        VideoPlayer
        PUBLIC
        ${GLAD_INCLUDE_DIRS}
)

target_link_libraries(
        VideoPlayer
        ${GLAD_LIBRARIES}
)

target_include_directories(VideoPlayer PUBLIC ${CMAKE_SOURCE_DIR}/ext/glm/glm)
target_link_libraries(VideoPlayer glm_shared)

target_link_libraries(
        VideoPlayer
        adv aui html net propgrid qa richtext webview xml xrc gl media core base
)

target_link_libraries(
        VideoPlayer
        VideoPlayerApplication VideoPlayerPlayer
)

if (WIN32)
    add_custom_command(
            TARGET VideoPlayer
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${install_dir}/bin/avcodec-58.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/avcodec-58.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${install_dir}/bin/avdevice-58.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/avdevice-58.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${install_dir}/bin/avfilter-7.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/avfilter-7.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${install_dir}/bin/avformat-58.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/avformat-58.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${install_dir}/bin/avutil-56.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/avutil-56.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${install_dir}/bin/swresample-3.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/swresample-3.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${install_dir}/bin/swscale-5.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/swscale-5.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/lib/gcc_dll/wxbase311ud_gcc_custom.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/wxbase311ud_gcc_custom.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/lib/gcc_dll/wxbase311ud_net_gcc_custom.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/wxbase311ud_net_gcc_custom.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/lib/gcc_dll/wxbase311ud_xml_gcc_custom.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/wxbase311ud_xml_gcc_custom.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/lib/gcc_dll/wxmsw311ud_adv_gcc_custom.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/wxmsw311ud_adv_gcc_custom.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/lib/gcc_dll/wxmsw311ud_aui_gcc_custom.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/wxmsw311ud_aui_gcc_custom.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/lib/gcc_dll/wxmsw311ud_core_gcc_custom.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/wxmsw311ud_core_gcc_custom.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/lib/gcc_dll/wxmsw311ud_gl_gcc_custom.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/wxmsw311ud_gl_gcc_custom.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/lib/gcc_dll/wxmsw311ud_html_gcc_custom.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/wxmsw311ud_html_gcc_custom.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/lib/gcc_dll/wxmsw311ud_media_gcc_custom.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/wxmsw311ud_media_gcc_custom.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/lib/gcc_dll/wxmsw311ud_propgrid_gcc_custom.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/wxmsw311ud_propgrid_gcc_custom.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/lib/gcc_dll/wxmsw311ud_qa_gcc_custom.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/wxmsw311ud_qa_gcc_custom.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/lib/gcc_dll/wxmsw311ud_richtext_gcc_custom.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/wxmsw311ud_richtext_gcc_custom.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/lib/gcc_dll/wxmsw311ud_webview_gcc_custom.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/wxmsw311ud_webview_gcc_custom.dll
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_BINARY_DIR}/lib/gcc_dll/wxmsw311ud_xrc_gcc_custom.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/wxmsw311ud_xrc_gcc_custom.dll
            COMMENT "Copy Thirdparty Libraries Win32"
    )
elseif (APPLE) # TODO Is a copy neccisary for this platform for testing in an IDE?
    message(STATUS "Copy Thirdparty Libraries Apple")
else () # TODO Is a copy neccisary for this platform for testing in an IDE?
    message(STATUS "Copy Thirdparty Libraries *nix")
endif ()