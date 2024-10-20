function(target_add_content target)
    get_target_property(is_${target}_macos_bundle ${target} MACOSX_BUNDLE)
    if(is_${target}_macos_bundle)
        foreach(content ${ARGN})
            add_custom_command(
                    TARGET ${target} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_CURRENT_SOURCE_DIR}/${content}
                    ${CMAKE_CURRENT_BINARY_DIR}/${target}.app/Contents/Resources/${content})
        endforeach()
    else()
        foreach(content ${ARGN})
            add_custom_command(
                    TARGET ${target} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy
                    ${CMAKE_CURRENT_SOURCE_DIR}/${content}
                    ${CMAKE_CURRENT_BINARY_DIR}/${content})
        endforeach()
    endif()
endfunction()

function(deploy_qt target)
    if(APPLE)
        find_program(DEPLOYQT_EXECUTABLE macdeployqt PATHS ${_qt_bin_dir} REQUIRED)
        add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${DEPLOYQT_EXECUTABLE} ${target}.app
                -always-overwrite)
    elseif(WIN32)
        find_program(DEPLOYQT_EXECUTABLE windeployqt PATHS ${_qt_bin_dir} REQUIRED)
        add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E
                env PATH=${_qt_bin_dir}
                ${DEPLOYQT_EXECUTABLE} --no-compiler-runtime
                $<TARGET_FILE:${target}>)
    endif()
endfunction()