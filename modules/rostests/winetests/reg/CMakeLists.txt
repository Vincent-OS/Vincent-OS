
add_executable(reg_winetest add.c copy.c delete.c export.c import.c query.c testlist.c)
set_module_type(reg_winetest win32cui)
add_importlibs(reg_winetest advapi32 msvcrt kernel32)
add_rostests_file(TARGET reg_winetest)
