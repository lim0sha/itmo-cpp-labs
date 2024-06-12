# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/ITMO/2_SEM/OP/OPLAB9/cmake-build-debug/_deps/curl-src"
  "D:/ITMO/2_SEM/OP/OPLAB9/cmake-build-debug/_deps/curl-build"
  "D:/ITMO/2_SEM/OP/OPLAB9/cmake-build-debug/_deps/curl-subbuild/curl-populate-prefix"
  "D:/ITMO/2_SEM/OP/OPLAB9/cmake-build-debug/_deps/curl-subbuild/curl-populate-prefix/tmp"
  "D:/ITMO/2_SEM/OP/OPLAB9/cmake-build-debug/_deps/curl-subbuild/curl-populate-prefix/src/curl-populate-stamp"
  "D:/ITMO/2_SEM/OP/OPLAB9/cmake-build-debug/_deps/curl-subbuild/curl-populate-prefix/src"
  "D:/ITMO/2_SEM/OP/OPLAB9/cmake-build-debug/_deps/curl-subbuild/curl-populate-prefix/src/curl-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/ITMO/2_SEM/OP/OPLAB9/cmake-build-debug/_deps/curl-subbuild/curl-populate-prefix/src/curl-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/ITMO/2_SEM/OP/OPLAB9/cmake-build-debug/_deps/curl-subbuild/curl-populate-prefix/src/curl-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
