cmake_minimum_required(VERSION 3.15)
project(VirtualMemorySimulator)

set(CMAKE_CXX_STANDARD 14)

add_executable(VirtualMemorySimulator main.cpp Classes/Page.cpp Classes/page.h Classes/dummy.cpp Classes/dummy.h Classes/PaginationTable.cpp Classes/PaginationTable.h Classes/Instruction.cpp Classes/Instruction.h  Classes/RealMemory.cpp Classes/RealMemory.h)