function(target_add_content target)
    foreach(content ${ARGN})
        if(APPLE)
            add_custom_command(
                    TARGET ${target} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_CURRENT_SOURCE_DIR}/${content}
                    ${CMAKE_CURRENT_BINARY_DIR}/${target}.app/Contents/Resources/${content})
        elseif(WIN32)
            add_custom_command(
                    TARGET ${target} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_CURRENT_SOURCE_DIR}/${content}
                    ${CMAKE_CURRENT_BINARY_DIR}/${content})
        endif()
    endforeach()
endfunction()

function(set_private_include_directories)
    foreach(target ${ARGN})
        target_include_directories(${target} PRIVATE
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/${target}>
                $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/${target}>)
    endforeach()
endfunction()

function(set_platform_properties)
    if(APPLE)
        foreach(target ${ARGN})
            set_target_properties(${target} PROPERTIES
                    MACOSX_BUNDLE TRUE)
        endforeach()
    elseif(WIN32)
        foreach(target ${ARGN})
            set_target_properties(${target} PROPERTIES
                    WIN32_EXECUTABLE TRUE)
        endforeach()
    endif()
endfunction()

function(deploy_qt)
    if(APPLE)
        find_program(DEPLOYQT_EXECUTABLE macdeployqt PATHS ${_qt_bin_dir} REQUIRED)
        foreach(target ${ARGN})
            add_custom_command(TARGET ${target} POST_BUILD
                    COMMAND ${DEPLOYQT_EXECUTABLE} ${target}.app
                    -always-overwrite)
        endforeach()
    elseif(WIN32)
        find_program(DEPLOYQT_EXECUTABLE windeployqt PATHS ${_qt_bin_dir} REQUIRED)
        foreach(target ${ARGN})
            add_custom_command(TARGET ${target} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E
                    env PATH=${_qt_bin_dir}
                    ${DEPLOYQT_EXECUTABLE} --no-compiler-runtime
                    $<TARGET_FILE:${target}>)
        endforeach()
    endif()
endfunction()