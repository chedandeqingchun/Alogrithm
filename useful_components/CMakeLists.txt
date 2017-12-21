cmake_minimum_required(VERSION 3.5.1)

set(source_files_workqueue
    workqueue.c
)

add_executable(workqueue ${source_files_workqueue})
target_link_libraries(workqueue pthread)

