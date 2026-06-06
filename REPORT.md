# Отчет по лабораторной работе №3
## Выполнил: Артеменко Арина ИУ8-22

## Репозиторий: https://github.com/gest475/lab003

## Цель работы
Освоить систему сборки CMake, научиться описывать статические библиотеки и приложения.

## Выполненные команды и их вывод


### 1. Создание локального репозитория

`cd ~/workspace`


`mkdir -p projects/lab03 && cd projects/lab03`


`git init`
*Вывод:*

Initialized empty Git repository in /home/maryu/workspace/projects/lab03/.git

`echo "# Lab03 CMake" > README.md`


`git add README.md`


`git commit -m "Initial commit: add README.md"`
*Вывод:*

[master (root-commit) 2ff4ce9] Initial commit: add README.md

1 file changed, 1 insertion(+)

create mode 100644 README.md

### 2. Добавление исходных файлов

`mkdir -p sources include examples`

`git add .`


`git commit -m "added sources"`
*Вывод:*

[master 6e81afc] added sources

4 files changed, 33 insertions(+)

create mode 100644 examples/example1.cpp

create mode 100644 examples/example2.cpp

create mode 100644 include/print.hpp

create mode 100644 sources/print.cpp

### 3. Ручная компиляция (Tutorial)

`g++ -std=c++11 -I./include -c sources/print.cpp`

`ls print.o`
*Вывод:*

print.o

`nm print.o | grep print`
*Вывод:*

0000000000000000 T _Z5printRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERSo

000000000000002a T _Z5printRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERSt14basic_ofstreamIcS2_E

`ar rvs print.a print.o`
*Вывод:*

ar: creating print.a

a - print.o

`file print.a`
*Вывод:*

print.a: current ar archive

`g++ -std=c++11 -I./include -c examples/example1.cpp`

`ls example1.o`
*Вывод:*
example1.o

`g++ example1.o print.a -o example1`


`./example1 && echo`
*Вывод:*

hello

`g++ -std=c++11 -I./include -c examples/example2.cpp`

`ls example2.o`
*Вывод:*
example2.o

`g++ example2.o print.a -o example2`

`./example2`

`cat log.txt && echo`
*Вывод:*

hello

### 4. Сборка с помощью CMake

`rm -rf example1.o example2.o print.o print.a example1 example2 log.txt`


`cat > CMakeLists.txt <<EOF`

```cmake_minimum_required(VERSION 3.4)
project(print)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_library(print STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
```

`cmake -H. -B_build`
*Вывод:*
-- The C compiler identification is GNU 13.3.0

-- The CXX compiler identification is GNU 13.3.0

-- Configuring done

-- Generating done

-- Build files have been written to: /home/maryu/workspace/projects/lab03/_build

`cmake --build _build`
*Вывод:*
[ 16%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o

[ 33%] Linking CXX static library libprint.a

[ 33%] Built target print

[ 50%] Building CXX object CMakeFiles/example1.dir/examples/example1.cpp.o

[ 66%] Linking CXX executable example1

[ 66%] Built target example1

[ 83%] Building CXX object CMakeFiles/example2.dir/examples/example2.cpp.o

[100%] Linking CXX executable example2

[100%] Built target example2


`_build/example1 && echo`
*Вывод:*
hello

`_build/example2`


`cat log.txt && echo`
*Вывод:*
hello

### 5. Домашнее задание (CMakeLists.txt для модулей)

#### formatter_lib/CMakeLists.txt

`cat > formatter_lib/CMakeLists.txt <<EOF`

```
cmake_minimum_required(VERSION 3.10)
project(formatter_lib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(formatter STATIC ${CMAKE_CURRENT_SOURCE_DIR}/formatter.cpp)
target_include_directories(formatter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```
#### formatter_ex_lib/CMakeLists.txt

`cat > formatter_ex_lib/CMakeLists.txt <<EOF`

```cmake_minimum_required(VERSION 3.10)
project(formatter_ex_lib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(formatter_ex STATIC ${CMAKE_CURRENT_SOURCE_DIR}/formatter_ex.cpp)
target_include_directories(formatter_ex PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(formatter_ex formatter)
```
#### hello_world_application/CMakeLists.txt

`cat > hello_world_application/CMakeLists.txt <<EOF`

```cmake_minimum_required(VERSION 3.10)
project(hello_world_application)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hello_world ${CMAKE_CURRENT_SOURCE_DIR}/hello_world.cpp)
target_link_libraries(hello_world formatter_ex)
```
#### solver_lib/CMakeLists.txt

`cat > solver_lib/CMakeLists.txt <<EOF`

```cmake_minimum_required(VERSION 3.10)
project(solver_lib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(solver STATIC ${CMAKE_CURRENT_SOURCE_DIR}/solver.cpp)
target_include_directories(solver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
```
#### solver_application/CMakeLists.txt

`cat > solver_application/CMakeLists.txt <<EOF`

```cmake_minimum_required(VERSION 3.10)
project(solver_application)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(solver ${CMAKE_CURRENT_SOURCE_DIR}/solver.cpp)
target_link_libraries(solver formatter_ex solver)
```
#### Главный CMakeLists.txt

`cat > CMakeLists.txt <<EOF`

```cmake_minimum_required(VERSION 3.10)
project(lab03)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex_lib)
add_subdirectory(hello_world_application)
add_subdirectory(solver_lib)
add_subdirectory(solver_application)
```

`git add .`

`git commit -m "add CMakeLists.txt for all modules"`
*Вывод:*

[master 7e76299] add CMakeLists.txt for all modules

 6 files changed, 52 insertions(+)
 
 create mode 100644 CMakeLists.txt
 
 create mode 100644 formatter_ex_lib/CMakeLists.txt
 
 create mode 100644 formatter_lib/CMakeLists.txt
 
 create mode 100644 hello_world_application/CMakeLists.txt
 
 create mode 100644 solver_application/CMakeLists.txt
 
 create mode 100644 solver_lib/CMakeLists.txt

`git remote add origin https://github.com/gest475/lab003.git`

`git push -u origin main`
Вывод:

Enumerating objects: 25, done.

Counting objects: 100% (25/25), done.

Delta compression using up to 8 threads

Compressing objects: 100% (16/16), done.

Writing objects: 100% (25/25), 2.40 KiB | 1.20 MiB/s, done.

Total 25 (delta 4), reused 0 (delta 0), pack-reused 0

To https://github.com/gest475/lab003.git

 * [new branch]      main -> main

branch 'main' set up to track 'origin/main'

`git log --oneline`
Вывод:

327ea81 (HEAD -> main, origin/main) Merge branch 'main' of https://github.com/gest475/lab003

6091a73 added CMakeLists.txt

61d95d6 Update REPORT.md

c131a22 Update REPORT.md

6d31741 Update REPORT.md

9f4cada Update REPORT.md

8c1439c Add report for lab03

7e76299 add CMakeLists.txt for all modules

6e81afc added sources

2ff4ce9 Initial commit: add README.md
