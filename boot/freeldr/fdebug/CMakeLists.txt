
add_executable(fdebug fdebug.c rs232.c fdebug.rc)
add_dependencies(fdebug psdk)
set_module_type(fdebug win32gui UNICODE)
add_importlibs(fdebug comdlg32 user32 gdi32 msvcrt kernel32)
add_cd_file(TARGET fdebug DESTINATION loader NO_CAB NOT_IN_HYBRIDCD FOR bootcd livecd hybridcd)
