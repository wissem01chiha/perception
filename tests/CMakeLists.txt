set(testSources 
    testCamera.cpp 
    testDepth.cpp 
    testDisplay.cpp 
    testFeature.cpp 
    testMath.cpp 
    testPreproc.cpp 
    testUtils.cpp 
)

foreach(testFile IN LISTS testSources)

    get_filename_component(targetName ${testFile} NAME_WE)
    add_executable(${targetName} ${testFile})
    target_link_libraries(${targetName}  ${OpenCV_LIBS} Eigen3::Eigen)
    target_include_directories(${targetName} 
    PRIVATE 
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/extern 
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

endforeach()