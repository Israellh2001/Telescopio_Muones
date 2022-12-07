#Version minima de cmake para correr el prgrama
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
#Nombre del proyecto
project(muon_telescope)

#Encontrar el paquete de geant e incluirlo
#El cual debe encontrarse en el PATH
find_package(${Geant4_USE_FILE})
include(${Geant4_USE_FILE})

#De la carpeta src incluir todos los archivos con terminación .cc
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
#De la carpeta include incluir todos los archivos con terminacion .hh
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#Aqui deben de ir todos los macros

#Crear ejecutable indicando el programa principal incluyendo todos los archivos anteriores
add_executable(telescope main.cc ${sources} ${headers})
target_link_libraries(telescope ${Geant4_LIBRARIES})

add_custom_target(muonTelescope DEPENDS telescope)
