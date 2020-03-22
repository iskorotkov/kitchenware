find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

include_directories (${TEST_SOURCE_DIR}/src
                     ${Boost_INCLUDE_DIRS}
                     )

add_definitions (-DBOOST_TEST_DYN_LINK)

include_directories(containers)

add_executable (kitchenware_tests
        containers/tree_tests.cpp
        )

target_link_libraries (kitchenware_tests
                       kitchenware_lib
                       ${Boost_FILESYSTEM_LIBRARY}
                       ${Boost_SYSTEM_LIBRARY}
                       ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )

add_test(NAME kitchenware_tests COMMAND kitchenware_tests)
