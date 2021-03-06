
set(KIT ${PROJECT_NAME})
set(CMAKE_TESTDRIVER_AFTER_TESTMAIN  "DEBUG_LEAKS_ENABLE_EXIT_ERROR();")
set(TEST_SOURCES
  qMRMLCheckableNodeComboBoxTest.cxx
  qMRMLCheckableNodeComboBoxTest1.cxx
  qMRMLClipNodeWidgetTest1.cxx
  qMRMLColorListViewTest1.cxx
  qMRMLColorModelTest.cxx
  qMRMLColorModelTest1.cxx
  qMRMLColorPickerWidgetTest1.cxx
  qMRMLColorPickerWidgetTest2.cxx
  qMRMLColorPickerWidgetTest3.cxx
  qMRMLColorTableComboBoxTest1.cxx
  qMRMLColorTableViewTest1.cxx
  qMRMLDisplayNodeViewComboBoxTest.cxx
  qMRMLDisplayNodeWidgetTest1.cxx
  qMRMLLayoutManagerTest1.cxx
  qMRMLLayoutManagerTest2.cxx
  qMRMLLayoutManagerTest3.cxx
  qMRMLLayoutManagerTest4.cxx
  qMRMLLinearTransformSliderTest1.cxx
  qMRMLListWidgetTest1.cxx
  qMRMLMatrixWidgetTest1.cxx
  qMRMLModelInfoWidgetTest1.cxx
  qMRMLModelTest1.cxx
  qMRMLModelTreeViewTest1.cxx
  qMRMLLabelComboBoxTest.cxx
  qMRMLNavigationViewTest1.cxx
  qMRMLNodeComboBoxTest1.cxx
  qMRMLNodeComboBoxTest2.cxx
  qMRMLNodeComboBoxTest3.cxx
  qMRMLNodeComboBoxTest4.cxx
  qMRMLNodeComboBoxTest5.cxx
  qMRMLNodeComboBoxTest6.cxx
  qMRMLNodeComboBoxTest7.cxx
  qMRMLNodeComboBoxLazyUpdateTest1.cxx
  qMRMLNodeFactoryTest1.cxx
  qMRMLScalarInvariantComboBoxTest1.cxx
  qMRMLSceneCategoryModelTest1.cxx
  qMRMLSceneColorTableModelTest1.cxx
  qMRMLSceneFactoryWidgetTest1.cxx
  qMRMLSceneHierarchyModelTest1.cxx
  qMRMLSceneModelTest.cxx
  qMRMLSceneModelTest1.cxx
  qMRMLSceneModelHierarchyModelTest1.cxx
  qMRMLSceneModelHierarchyModelTest2.cxx
  #qMRMLTransformProxyModelTest1.cxx
  qMRMLSceneTransformModelTest1.cxx
  qMRMLSceneTransformModelTest2.cxx
  qMRMLSceneDisplayableModelTest1.cxx
  qMRMLSceneDisplayableModelTest2.cxx
  qMRMLSliceControllerWidgetTest.cxx
  qMRMLSliceWidgetTest1.cxx
  qMRMLSliceWidgetTest2.cxx
  qMRMLTransformSlidersTest1.cxx
  qMRMLThreeDViewTest1.cxx
  qMRMLThreeDWidgetTest1.cxx
  qMRMLTreeViewTest1.cxx
  qMRMLUtf8Test1.cxx
  qMRMLUtilsTest1.cxx
  qMRMLVolumeInfoWidgetTest1.cxx
  qMRMLVolumeThresholdWidgetTest1.cxx
  qMRMLVolumeThresholdWidgetTest2.cxx
  qMRMLWidgetsExportTest1.cxx
  qMRMLWindowLevelWidgetTest1.cxx
  EXTRA_INCLUDE vtkMRMLDebugLeaksMacro.h
  )

if(Slicer_USE_QtTesting)
  list(APPEND TEST_SOURCES
    qMRMLCheckableNodeComboBoxEventTranslatorPlayerTest1.cxx
    qMRMLClipNodeWidgetEventTranslatorPlayerTest1.cxx
    qMRMLCollapsibleButtonEventTranslatorPlayerTest1.cxx
    qMRMLColorListViewEventTranslatorPlayerTest1.cxx
    qMRMLColorPickerWidgetEventTranslatorPlayerTest1.cxx
    qMRMLColorTableComboBoxEventTranslatorPlayerTest1.cxx
    qMRMLColorTableViewEventTranslatorPlayerTest1.cxx
    qMRMLDisplayNodeWidgetEventTranslatorPlayerTest1.cxx
    qMRMLLabelComboBoxEventTranslatorPlayerTest1.cxx
    qMRMLLinearTransformSliderEventTranslatorPlayerTest1.cxx
    qMRMLListWidgetEventTranslatorPlayerTest1.cxx
    qMRMLMatrixWidgetEventTranslatorPlayerTest1.cxx
    qMRMLNavigationViewEventTranslatorPlayerTest1.cxx
    qMRMLNodeComboBoxEventTranslatorPlayerTest1.cxx
    qMRMLRangeWidgetEventTranslatorPlayerTest1.cxx
    qMRMLROIWidgetEventTranslatorPlayerTest1.cxx
    qMRMLScalarInvariantComboBoxEventTranslatorPlayerTest1.cxx
    qMRMLSliceControllerWidgetEventTranslatorPlayerTest1.cxx
    qMRMLSliceWidgetEventTranslatorPlayerTest1.cxx
    qMRMLThreeDViewControllerWidgetEventTranslatorPlayerTest1.cxx
    qMRMLThreeDWidgetEventTranslatorPlayerTest1.cxx
    qMRMLTransformSlidersEventTranslatorPlayerTest1.cxx
    qMRMLTreeViewEventTranslatorPlayerTest1.cxx
    qMRMLVolumeInfoWidgetEventTranslatorPlayerTest1.cxx
    qMRMLVolumeThresholdWidgetEventTranslatorPlayerTest1.cxx
    qMRMLWindowLevelWidgetEventTranslatorPlayerTest1.cxx
    )
endif()

create_test_sourcelist(Tests ${KIT}CppTests.cxx
  ${TEST_SOURCES}
  )

set(Tests_MOC_SRCS qMRMLNodeObject.h)
set(Tests_UtilityFiles
  qMRMLNodeObject.cxx
  qMRMLNodeObject.h
  )

QT4_WRAP_CPP(Tests_MOC_CXX ${Tests_MOC_SRCS})
QT4_GENERATE_MOCS(
  qMRMLCheckableNodeComboBoxTest.cxx
  qMRMLColorModelTest.cxx
  qMRMLDisplayNodeViewComboBoxTest.cxx
  qMRMLLabelComboBoxTest.cxx
  qMRMLSceneModelTest.cxx
  qMRMLSliceControllerWidgetTest.cxx
  )

include_directories( ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${KIT}CxxTests ${Tests} ${Tests_MOC_CXX} ${Tests_UtilityFiles})
target_link_libraries(${KIT}CxxTests ${KIT})

macro(SCENE_TEST TESTNAME SCENEFILENAME)
  add_test(
    NAME ${TESTNAME}_${SCENEFILENAME}
    COMMAND ${Slicer_LAUNCH_COMMAND} $<TARGET_FILE:${KIT}CxxTests> ${TESTNAME} ${MRMLCore_SOURCE_DIR}/Testing/${SCENEFILENAME}
    )
endmacro()

SIMPLE_TEST( qMRMLCheckableNodeComboBoxTest )
SIMPLE_TEST( qMRMLCheckableNodeComboBoxTest1 )
SIMPLE_TEST( qMRMLClipNodeWidgetTest1 )
SIMPLE_TEST( qMRMLColorListViewTest1 )
SIMPLE_TEST( qMRMLColorModelTest )
SIMPLE_TEST( qMRMLColorModelTest1 )
SIMPLE_TEST( qMRMLColorPickerWidgetTest1 )
SIMPLE_TEST( qMRMLColorPickerWidgetTest2 )
SIMPLE_TEST( qMRMLColorPickerWidgetTest3 )
SIMPLE_TEST( qMRMLColorTableComboBoxTest1 )
SIMPLE_TEST( qMRMLColorTableViewTest1 )
SIMPLE_TEST( qMRMLDisplayNodeViewComboBoxTest )
SIMPLE_TEST( qMRMLDisplayNodeWidgetTest1 )
SIMPLE_TEST( qMRMLLayoutManagerTest1 )
SIMPLE_TEST( qMRMLLayoutManagerTest2 )
SIMPLE_TEST( qMRMLLayoutManagerTest3 )
SIMPLE_TEST( qMRMLLayoutManagerTest4 )
SIMPLE_TEST( qMRMLLinearTransformSliderTest1 )
SIMPLE_TEST( qMRMLListWidgetTest1 )
SIMPLE_TEST( qMRMLMatrixWidgetTest1 )
SIMPLE_TEST( qMRMLModelInfoWidgetTest1 )
SIMPLE_TEST( qMRMLModelTest1 )
SIMPLE_TEST( qMRMLModelTreeViewTest1 )
SIMPLE_TEST( qMRMLLabelComboBoxTest )
SIMPLE_TEST( qMRMLNavigationViewTest1 )
SIMPLE_TEST( qMRMLNodeComboBoxTest1 )
SIMPLE_TEST( qMRMLNodeComboBoxTest2 )
SCENE_TEST(  qMRMLNodeComboBoxTest3 diffusionEditor.mrml )
SIMPLE_TEST( qMRMLNodeComboBoxTest4 )
SIMPLE_TEST( qMRMLNodeComboBoxTest5 )
SIMPLE_TEST( qMRMLNodeComboBoxTest6 )
SIMPLE_TEST( qMRMLNodeComboBoxTest7 )
SIMPLE_TEST( qMRMLNodeComboBoxLazyUpdateTest1 )
SIMPLE_TEST( qMRMLNodeFactoryTest1 )
SIMPLE_TEST( qMRMLScalarInvariantComboBoxTest1 )
SIMPLE_TEST( qMRMLSceneCategoryModelTest1 )
SIMPLE_TEST( qMRMLSceneColorTableModelTest1 )
SIMPLE_TEST( qMRMLSceneFactoryWidgetTest1 )
SIMPLE_TEST( qMRMLSceneModelTest )
SIMPLE_TEST( qMRMLSceneModelTest1 )
SIMPLE_TEST( qMRMLSceneModelHierarchyModelTest1 )
SIMPLE_TEST( qMRMLSceneModelHierarchyModelTest2 vol_and_cube.mrml)
SIMPLE_TEST( qMRMLSceneTransformModelTest1 )
SCENE_TEST(  qMRMLSceneTransformModelTest2 vol_and_cube.mrml )
SIMPLE_TEST( qMRMLSceneDisplayableModelTest1 )
SCENE_TEST(  qMRMLSceneDisplayableModelTest2 vol_and_cube.mrml )
SIMPLE_TEST( qMRMLSliceControllerWidgetTest )
SCENE_TEST( qMRMLSliceWidgetTest1 vol_and_cube.mrml)
SCENE_TEST( qMRMLSliceWidgetTest2 fixed.nrrd)
SIMPLE_TEST( qMRMLTransformSlidersTest1 )
SIMPLE_TEST( qMRMLThreeDViewTest1 )
SIMPLE_TEST( qMRMLThreeDWidgetTest1 )
SCENE_TEST(  qMRMLTreeViewTest1 vol_and_cube.mrml )
SCENE_TEST(  qMRMLUtf8Test1 cube-utf8.mrml )
SIMPLE_TEST( qMRMLUtilsTest1 )
SIMPLE_TEST( qMRMLVolumeInfoWidgetTest1 )
SCENE_TEST( qMRMLVolumeThresholdWidgetTest1 vol_and_cube.mrml)
SCENE_TEST( qMRMLVolumeThresholdWidgetTest2 vol_and_cube.mrml)
SIMPLE_TEST( qMRMLWidgetsExportTest1 )
SCENE_TEST( qMRMLWindowLevelWidgetTest1 vol_and_cube.mrml)

if(Slicer_USE_QtTesting)
  macro(QtTesting_TEST testname)
    SIMPLE_TEST(${testname} ${ARGN})
    set_tests_properties(${testname} PROPERTIES RUN_SERIAL ON)
  endmacro()
  QtTesting_TEST(qMRMLCheckableNodeComboBoxEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLClipNodeWidgetEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLCollapsibleButtonEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLColorListViewEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLColorPickerWidgetEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLColorTableComboBoxEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLColorTableViewEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLDisplayNodeWidgetEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLLabelComboBoxEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLLinearTransformSliderEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLListWidgetEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLMatrixWidgetEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLNavigationViewEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLNodeComboBoxEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLRangeWidgetEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLROIWidgetEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLScalarInvariantComboBoxEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLSliceControllerWidgetEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLSliceWidgetEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR} "${MRMLCore_SOURCE_DIR}/Testing/vol_and_cube.mrml")
  QtTesting_TEST(qMRMLThreeDViewControllerWidgetEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLThreeDWidgetEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLTransformSlidersEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLTreeViewEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR} "${MRMLCore_SOURCE_DIR}/Testing/vol_and_cube.mrml")
  QtTesting_TEST(qMRMLVolumeInfoWidgetEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR})
  QtTesting_TEST(qMRMLVolumeThresholdWidgetEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR} "${MRMLCore_SOURCE_DIR}/Testing/vol_and_cube.mrml")
  QtTesting_TEST(qMRMLWindowLevelWidgetEventTranslatorPlayerTest1 ${Slicer_SOURCE_DIR} "${MRMLCore_SOURCE_DIR}/Testing/vol_and_cube.mrml")
endif()
