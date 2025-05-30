#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)
project(gatoranalysis)

set(CMAKE_INSTALL_PREFIX $ENV{HOME}/PhD/Gator)

include_directories(${PROJECT_SOURCE_DIR}/../include)




#----------------------------------------------------------------------------
#Find all the sourcefiles in src directory
set(_sources_gatoranalysis
  ${PROJECT_SOURCE_DIR}/../src/GatorCounter.cc
  ${PROJECT_SOURCE_DIR}/../src/GatorDataLoader.cc
  ${PROJECT_SOURCE_DIR}/../src/GatorSampleAnalysis.cc
  )

set(_sources_trigrate
  ${PROJECT_SOURCE_DIR}/../src/trigrate.cc
  )

set(_sources_general
  ${PROJECT_SOURCE_DIR}/../src/loadSPE.cc
  ${PROJECT_SOURCE_DIR}/../src/convert_histo_ENR.cc
  ${PROJECT_SOURCE_DIR}/../src/formatdigits.cc
  ${PROJECT_SOURCE_DIR}/../src/misc.cc
  )

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(sampleanalysis sampleanalysis_v2.1.cpp ${_sources_gatoranalysis} ${_sources_general})
target_link_libraries(sampleanalysis ${ROOT_LIBRARIES})

add_executable(sample_rates sample_rates.cpp ${_sources_trigrate} ${_sources_general})
target_link_libraries(sample_rates ${ROOT_LIBRARIES})

install(TARGETS sampleanalysis DESTINATION bin)
install(TARGETS sample_rates DESTINATION bin)