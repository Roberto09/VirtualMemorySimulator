cmake_minimum_required(VERSION 3.15)
project(VirtualMemorySimulator)

set(CMAKE_CXX_STANDARD 14)


add_executable(VirtualMemorySimulator main.cpp Classes/Page.cpp Classes/page.h Classes/dummy.cpp Classes/dummy.h Classes/ProcessPaginationTable.cpp Classes/ProcessPaginationTable.h Classes/Instruction.cpp Classes/Instruction.h Classes/FifoQueue.cpp Classes/FifoQueue.h Classes/RealMemory.cpp Classes/RealMemory.h Classes/SecondaryMemory.cpp Classes/SecondaryMemory.h Classes/Controller.cpp Classes/Controller.h Classes/Process.cpp Classes/Process.h Classes/ReplacementQueue.cpp Classes/ReplacementQueue.h Classes/LRUQueue.cpp Classes/LRUQueue.h Classes/Status.cpp Classes/Status.h)



