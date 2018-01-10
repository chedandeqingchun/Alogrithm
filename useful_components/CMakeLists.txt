cmake_minimum_required(VERSION 3.5.1)

add_definitions("-fpermissive")

set(source_files_workqueue
    workqueue.c
)

add_executable(workqueue ${source_files_workqueue})
target_link_libraries(workqueue pthread)

set(source_files_dynamic
    vector.c
)
add_executable(vector ${source_files_dynamic})

set(source_files_avl
    avl.c
)
add_executable(avl ${source_files_avl})
