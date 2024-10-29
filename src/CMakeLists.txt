
set(sources 
   
)

foreach(sourceFile IN LISTS sources)

    get_filename_component(targetSourceName ${sourceFile} NAME_WE)
    add_executable(${targetSourceName} ${sourceFile})
    target_link_libraries(${targetSourceName}  ${OpenCV_LIBS})
    target_include_directories(${targetSourceName} 
    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/extern 
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

endforeach()