project(SlicerBaseLogic)

# --------------------------------------------------------------------------
# Third party library
# --------------------------------------------------------------------------
if(Slicer_BUILD_CLI_SUPPORT)
  find_package(SlicerExecutionModel REQUIRED ModuleDescriptionParser)
endif()

# --------------------------------------------------------------------------
# Subdirectories
# --------------------------------------------------------------------------
add_subdirectory(Resources)

# --------------------------------------------------------------------------
# Include dirs
# --------------------------------------------------------------------------
set(include_dirs
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${MRMLCore_INCLUDE_DIRS}
  ${MRMLLogic_INCLUDE_DIRS}
  ${vtkTeem_INCLUDE_DIRS}
  ${FreeSurfer_INCLUDE_DIRS}
  ${RemoteIO_INCLUDE_DIRS}
  ${LibArchive_INCLUDE_DIR}
  )

if(Slicer_BUILD_CLI_SUPPORT)
  list(APPEND include_dirs
    ${MRMLCLI_INCLUDE_DIRS}
    ${ModuleDescriptionParser_INCLUDE_DIRS}
    )
endif()

if(Slicer_USE_PYTHONQT)
  list(APPEND include_dirs
    ${PYTHON_INCLUDE_DIR}
    )
endif()

include_directories(${include_dirs})

# --------------------------------------------------------------------------
# Update Slicer_Base_INCLUDE_DIRS
# --------------------------------------------------------------------------
set(Slicer_Base_INCLUDE_DIRS ${Slicer_Base_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  CACHE INTERNAL "Slicer Base includes" FORCE)

# --------------------------------------------------------------------------
# Configure headers
# --------------------------------------------------------------------------
set(configure_header_file vtkSlicerBaseLogicConfigure.h)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/${configure_header_file}.in
  ${CMAKE_CURRENT_BINARY_DIR}/${configure_header_file}
  )

# --------------------------------------------------------------------------
# Install headers
# --------------------------------------------------------------------------
if(NOT DEFINED ${PROJECT_NAME}_INSTALL_NO_DEVELOPMENT)
  set(${PROJECT_NAME}_INSTALL_NO_DEVELOPMENT ON)
endif()
if(NOT ${PROJECT_NAME}_INSTALL_NO_DEVELOPMENT)
  file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
  install(
    FILES ${headers} ${CMAKE_CURRENT_BINARY_DIR}/${configure_header_file}
    DESTINATION include/${PROJECT_NAME} COMPONENT Development)
endif()

# --------------------------------------------------------------------------
# Sources
# --------------------------------------------------------------------------
set(SlicerBaseLogic_SRCS
  # Logic classes (data management and calculation)
  vtkSlicerApplicationLogic.cxx
  vtkSlicerModuleLogic.cxx
  vtkSlicerTask.cxx
  vtkSlicerFiducialsLogic.cxx
  vtkDataIOManagerLogic.cxx
  # slicer's vtk extensions (filters)
  vtkImageSlicePaint.cxx
  vtkImageFillROI.cxx
  vtkSlicerGlyphSource2D.cxx
  vtkSlicerROILogic.cxx
  vtkImageConnectivity.cxx
  vtkImageLabelChange.cxx
  vtkImageErode.cxx
  vtkSlicerTransformLogic.cxx
  vtkPichonFastMarching.cxx
  vtkPichonFastMarchingPDF.cxx
  vtkImageRectangularSource.cxx
  vtkSystemInformation.cxx
  vtkImageStash.cxx
  )

if(Slicer_USE_PYTHONQT)
  list(APPEND SlicerBaseLogic_SRCS
    vtkSlicerScriptedLoadableModuleLogic.cxx
    )
endif()

set_source_files_properties(
  vtkPichonFastMarchingPDF.cxx
  WRAP_EXCLUDE
  )

# --------------------------------------------------------------------------
## Create an instantiator for these classes
# set(VTK_USE_INSTANTIATOR_NEW 1)
# VTK_MAKE_INSTANTIATOR3("${lib_name}Instantiator"
#   Instantiator_SRCS
#   "${SlicerBaseLogic_SRCS}"
#   "VTK_SLICER_BASE_LOGIC_EXPORT"
#   ${Slicer_BINARY_DIR}
#   "vtkSlicerBaseLogic.h")

# --------------------------------------------------------------------------
# Build library
# --------------------------------------------------------------------------
set(lib_name SlicerBaseLogic)

#set(srcs ${SlicerBaseLogic_SRCS} ${Instantiator_SRCS})
set(srcs ${SlicerBaseLogic_SRCS})

add_library(${lib_name} ${srcs})

set(VTK_LIBRARIES
  #vtkCommon # Provided by MRMLLogic
  #vtkFiltering # Provided by MRMLLogic
  #vtkGraphics # Provided by MRMLLogic
  #vtkHybrid # Provided by MRMLLogic
  #vtkIO # Provided by MRMLLogic
  "" # Since no direct dependency to VTK libraries are required, let's explicitly set
     # the variable to an empty string to avoid complaints from vtkMacroKitPythonWraps.cmake.
  )

set(libs
  MRMLLogic
  ${VTK_LIBRARIES}
  )

# Archive support used by extensions and by slicer data bundle
list(APPEND libs
  ${LibArchive_LIBRARY}
  )

if(Slicer_BUILD_CLI_SUPPORT)
  list(APPEND libs
    MRMLCLI
    )
endif()

if(Slicer_USE_PYTHONQT)
  list(APPEND libs
    vtkCommonPythonD # For vtkPythonUtils
    ${PYTHON_LIBRARY} # At some point, VTK should be updated to expose VTK_PYTHON_LIBRARY
    )
endif()

target_link_libraries(${lib_name} ${libs})
set_target_properties(${lib_name} PROPERTIES LABELS ${lib_name})

# Apply user-defined properties to the library target.
if(Slicer_LIBRARY_PROPERTIES)
  set_target_properties(${lib_name} PROPERTIES ${Slicer_LIBRARY_PROPERTIES})
endif()

# --------------------------------------------------------------------------
# Export target
# --------------------------------------------------------------------------
set_property(GLOBAL APPEND PROPERTY Slicer_TARGETS ${lib_name})

# --------------------------------------------------------------------------
# Install library
# --------------------------------------------------------------------------
install(TARGETS ${lib_name}
  RUNTIME DESTINATION ${Slicer_INSTALL_BIN_DIR} COMPONENT RuntimeLibraries
  LIBRARY DESTINATION ${Slicer_INSTALL_LIB_DIR} COMPONENT RuntimeLibraries
  ARCHIVE DESTINATION ${Slicer_INSTALL_LIB_DIR} COMPONENT Development
  )

# --------------------------------------------------------------------------
# Python Wrapping
# --------------------------------------------------------------------------
if(VTK_WRAP_PYTHON)
  vtkMacroKitPythonWrap(
    KIT_NAME ${lib_name}
    KIT_SRCS ${SlicerBaseLogic_SRCS}
    KIT_PYTHON_LIBRARIES MRMLLogicPythonD
    KIT_INSTALL_BIN_DIR ${Slicer_INSTALL_BIN_DIR}
    KIT_INSTALL_LIB_DIR ${Slicer_INSTALL_LIB_DIR}
    )
  # Export target
  set_property(GLOBAL APPEND PROPERTY Slicer_TARGETS ${lib_name}Python ${lib_name}PythonD)
endif()

# --------------------------------------------------------------------------
# Testing (requires some of the examples)
# --------------------------------------------------------------------------
if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()

