

#add_subdirectory(subdir2)
set(MY_VAL ${MY_VAL} " sub1" PARENT_SCOPE)
message("-- subdir1   , MY_VAL : " ${MY_VAL})
message("-- subdir1   , MY_VAL : " ${MY_VAL})

