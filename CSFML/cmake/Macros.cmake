
# some of these macros are inspired from the boost/cmake macros

# check if a value is contained in a list
# sets ${var} to TRUE if the value is found
macro(csfml_list_contains var value)
    set(${var})
    foreach(value2 ${ARGN})
        if(${value} STREQUAL ${value2})
            set(${var} TRUE)
        endif()
    endforeach()
endmacro()

# parse a list of arguments and options
# ex: sfml_parse_arguments(THIS "SOURCES;DEPENDS" "FLAG" FLAG SOURCES s1 s2 s3 DEPENDS d1 d2)
# will define the following variables:
# - THIS_SOURCES (s1 s2 s3)
# - THIS_DEPENDS (d1 d2)
# - THIS_FLAG TRUE
macro(csfml_parse_arguments prefix arg_names option_names)
    foreach(arg_name ${arg_names})
        set(${prefix}_${arg_name})
    endforeach()
    foreach(option_name ${option_names})
        set(${prefix}_${option_name} FALSE)
    endforeach()
    set(current_arg_name)
    set(current_arg_list)
    foreach(arg ${ARGN})
        csfml_list_contains(is_arg_name ${arg} ${arg_names})
        if(is_arg_name)
            set(${prefix}_${current_arg_name} ${current_arg_list})
            set(current_arg_name ${arg})
            set(current_arg_list)
        else()
            csfml_list_contains(is_option ${arg} ${option_names})
            if(is_option)
                set(${prefix}_${arg} TRUE)
            else()
                set(current_arg_list ${current_arg_list} ${arg})
            endif()
        endif()
    endforeach()
    set(${prefix}_${current_arg_name} ${current_arg_list})
endmacro()

# add a new target which is a CSFML library
# ex: csfml_add_library(sfml-graphics
#                       SOURCES sprite.cpp image.cpp ...
#                       DEPENDS sfml-window sfml-system)
macro(csfml_add_library target)

    # parse the arguments
    csfml_parse_arguments(THIS "SOURCES;DEPENDS" "" ${ARGN})

    # create the target
    add_library(${target} ${THIS_SOURCES})

    # adjust the output file prefix/suffix to match our conventions
    set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -d)
    if (WINDOWS AND COMPILER_GCC)
        set_target_properties(${target} PROPERTIES PREFIX "")
        set_target_properties(${target} PROPERTIES IMPORT_SUFFIX ".a")
    endif()

    # insert the major version number in the output filename
    string(REGEX REPLACE "csfml(-.*)" "csfml${VERSION_MAJOR}\\1" OUTPUT_NAME ${target})
    set_target_properties(${target} PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

    # for gcc 4.x on Windows, we add the -static-libgcc linker flag to get rid of an extra gcc DLL
    if(WINDOWS AND COMPILER_GCC)
        if(${GCC_VERSION} MATCHES "4\\..*")
            set_target_properties(${target} PROPERTIES LINK_FLAGS -static-libgcc)
        endif()
    endif()

    # link the target to its external dependencies (C++ SFML libraries)
    target_link_libraries(${target} ${THIS_DEPENDS})

    # add the install rule
    install(TARGETS ${target}
            RUNTIME DESTINATION bin COMPONENT bin
            LIBRARY DESTINATION lib COMPONENT bin 
            ARCHIVE DESTINATION lib COMPONENT devel)

endmacro()
