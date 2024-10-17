function(set_private_include_directories)
    foreach(target ${ARGN})
        target_include_directories(${target} PRIVATE
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")
    endforeach()
endfunction()

function(deploy_qt)
    if(APPLE)
        foreach(target ${ARGN})
            set_target_properties(${target} PROPERTIES
                    MACOSX_BUNDLE TRUE)
        endforeach()
    elseif(WIN32)
        find_program(DEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}" REQUIRED)
        foreach(target ${ARGN})
            set_target_properties(${target} PROPERTIES
                    WIN32_EXECUTABLE TRUE)
            add_custom_command(TARGET ${target} POST_BUILD
                    COMMAND "${CMAKE_COMMAND}" -E
                    env PATH="${_qt_bin_dir}" "${DEPLOYQT_EXECUTABLE}"
                    --no-compiler-runtime
                    \"$<TARGET_FILE:${target}>\")
        endforeach()
    endif()
endfunction()

function(target_add_content target)
    foreach(content ${ARGN})
        if(APPLE)
            add_custom_command(
                    TARGET ${target} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_CURRENT_SOURCE_DIR}/${content}
                    ${CMAKE_CURRENT_BINARY_DIR}/${target}.app/Contents/MacOS/${content})
        elseif(WIN32)
            add_custom_command(
                    TARGET ${target} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_CURRENT_SOURCE_DIR}/${content}
                    ${CMAKE_CURRENT_BINARY_DIR}/${content})
        endif()
    endforeach()
endfunction()