#-------------------------------------------------
#
# Project created by QtCreator 2021-02-16T14:20:42
#
#-------------------------------------------------

QT       += core gui
RC_ICONS = AstraGUI.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AstraGUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    mainwindow.cpp \
    camera_settings.cpp \
    cloud_generate.cpp

HEADERS += \
    mainwindow.h \
    camera_settings.h \
    cloud_generate.h

FORMS += \
    mainwindow.ui \
    camera_settings.ui


LIBS += D:/software/opencv4.0.0/opencv/build/x64/vc14/lib/*.lib/
INCLUDEPATH += D:/software/opencv4.0.0/opencv/build/include
DEPENDPATH += D:/software/opencv4.0.0/opencv/build/include

INCLUDEPATH +=  D:/software/vtk7.0.0/include/vtk-7.0
LIBS += D:/software/vtk7.0.0/lib/*.lib/


INCLUDEPATH += D:\software\PCL1.8.0\3rdParty\OpenNI2\include\
INCLUDEPATH += D:\software\PCL1.8.0\include\pcl-1.8\pcl
INCLUDEPATH += D:\software\PCL1.8.0\include\pcl-1.8\
INCLUDEPATH += D:\software\PCL1.8.0\3rdParty\Boost\include\boost-1_61\
INCLUDEPATH += D:\software\PCL1.8.0\3rdParty\Eigen\eigen3\
INCLUDEPATH += D:\software\PCL1.8.0\3rdParty\FLANN\include\
INCLUDEPATH += D:\software\PCL1.8.0\3rdParty\FLANN\include\flann\
INCLUDEPATH += D:\software\PCL1.8.0\3rdParty\OpenNI2\Include\
INCLUDEPATH += D:\software\PCL1.8.0\3rdParty\Qhull\include\
INCLUDEPATH += D:\software\PCL1.8.0\3rdParty\VTK\include\vtk-7.0

CONFIG(debug,debug|release){
LIBS += D:\software\PCL1.8.0\lib\pcl_common_debug.lib\
        D:\software\PCL1.8.0\lib\pcl_features_debug.lib\
        D:\software\PCL1.8.0\lib\pcl_filters_debug.lib\
        D:\software\PCL1.8.0\lib\pcl_io_debug.lib\
        D:\software\PCL1.8.0\lib\pcl_io_ply_debug.lib\
        D:\software\PCL1.8.0\lib\pcl_kdtree_debug.lib\
        D:\software\PCL1.8.0\lib\pcl_keypoints_debug.lib\
        D:\software\PCL1.8.0\lib\pcl_ml_debug.lib\
        D:\software\PCL1.8.0\lib\pcl_octree_debug.lib\
        D:\software\PCL1.8.0\lib\pcl_outofcore_debug.lib\
        D:\software\PCL1.8.0\lib\pcl_people_debug.lib\
        D:\software\PCL1.8.0\lib\pcl_recognition_debug.lib\
        D:\software\PCL1.8.0\lib\pcl_registration_debug.lib\
        D:\software\PCL1.8.0\lib\pcl_sample_consensus_debug.lib\
        D:\software\PCL1.8.0\lib\pcl_search_debug.lib\
        D:\software\PCL1.8.0\lib\pcl_segmentation_debug.lib\
        D:\software\PCL1.8.0\lib\pcl_stereo_debug.lib\
        D:\software\PCL1.8.0\lib\pcl_surface_debug.lib\
        D:\software\PCL1.8.0\lib\pcl_tracking_debug.lib\
        D:\software\PCL1.8.0\lib\pcl_visualization_debug.lib
LIBS+=  D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_atomic-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_chrono-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_container-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_context-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_coroutine-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_date_time-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_exception-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_filesystem-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_graph-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_iostreams-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_locale-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_log_setup-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_log-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_math_c99f-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_math_c99l-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_math_c99-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_math_tr1f-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_math_tr1l-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_math_tr1-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_mpi-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_prg_exec_monitor-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_program_options-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_random-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_regex-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_serialization-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_signals-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_system-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_test_exec_monitor-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_thread-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_timer-vc140-mt-gd-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_type_erasure-vc140-mt-gd-1_61.lib
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_unit_test_framework-vc140-mt-gd-1_61.lib
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_wave-vc140-mt-gd-1_61.lib
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_wserialization-vc140-mt-gd-1_61.lib
LIBS+=  D:\software\PCL1.8.0\3rdParty\FLANN\lib\flann_cpp_s-gd.lib\
        D:\software\PCL1.8.0\3rdParty\FLANN\lib\flann_s-gd.lib\
        D:\software\PCL1.8.0\3rdParty\FLANN\lib\flann-gd.lib
LIBS+=  D:\software\PCL1.8.0\3rdParty\Qhull\lib\qhullstatic_d.lib\
        D:\software\PCL1.8.0\3rdParty\Qhull\lib\qhull_d.lib\
        D:\software\PCL1.8.0\3rdParty\Qhull\lib\qhull_p_d.lib\
        D:\software\PCL1.8.0\3rdParty\Qhull\lib\qhullcpp_d.lib\
        D:\software\PCL1.8.0\3rdParty\Qhull\lib\qhullstatic_r_d.lib
LIBS+=  D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkalglib-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkChartsCore-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkCommonColor-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkCommonComputationalGeometry-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkCommonCore-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkCommonDataModel-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkCommonExecutionModel-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkCommonMath-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkCommonMisc-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkCommonSystem-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkCommonTransforms-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkDICOMParser-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkDomainsChemistry-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkexoIIc-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkexpat-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersAMR-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersCore-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersExtraction-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersFlowPaths-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersGeneral-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersGeneric-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersGeometry-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersHybrid-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersHyperTree-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersImaging-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersModeling-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersParallel-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersParallelImaging-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersProgrammable-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersSelection-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersSMP-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersSources-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersStatistics-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersTexture-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersVerdict-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkfreetype-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkGeovisCore-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkgl2ps-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkhdf5-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkhdf5_hl-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkImagingColor-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkImagingCore-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkImagingFourier-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkImagingGeneral-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkImagingHybrid-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkImagingMath-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkImagingMorphological-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkImagingSources-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkImagingStatistics-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkImagingStencil-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkInfovisCore-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkInfovisLayout-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkInteractionImage-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkInteractionStyle-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkInteractionWidgets-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOAMR-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOCore-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOEnSight-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOExodus-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOExport-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOGeometry-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOImage-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOImport-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOInfovis-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOLegacy-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOLSDyna-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOMINC-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOMovie-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIONetCDF-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOParallel-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOParallelXML-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOPLY-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOSQL-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOVideo-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOXML-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOXMLParser-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkjpeg-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkjsoncpp-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtklibxml2-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkmetaio-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkNetCDF-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkNetCDF_cxx-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkoggtheora-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkParallelCore-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkpng-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkproj4-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingAnnotation-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingContext2D-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingContextOpenGL-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingCore-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingFreeType-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingGL2PS-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingImage-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingLabel-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingLIC-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingLOD-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingOpenGL-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingVolume-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingVolumeOpenGL-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtksqlite-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtksys-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtktiff-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkverdict-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkViewsContext2D-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkViewsCore-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkViewsInfovis-7.0-gd.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkzlib-7.0-gd.lib
LIBS+=  D:\software\PCL1.8.0\3rdParty\OpenNI2\Lib\OpenNI2.lib
}
else {
LIBS += D:\software\PCL1.8.0\lib\pcl_common_release.lib\
        D:\software\PCL1.8.0\lib\pcl_features_release.lib\
        D:\software\PCL1.8.0\lib\pcl_filters_release.lib\
        D:\software\PCL1.8.0\lib\pcl_io_release.lib\
        D:\software\PCL1.8.0\lib\pcl_io_ply_release.lib\
        D:\software\PCL1.8.0\lib\pcl_kdtree_release.lib\
        D:\software\PCL1.8.0\lib\pcl_keypoints_release.lib\
        D:\software\PCL1.8.0\lib\pcl_ml_release.lib\
        D:\software\PCL1.8.0\lib\pcl_octree_release.lib\
        D:\software\PCL1.8.0\lib\pcl_outofcore_release.lib\
        D:\software\PCL1.8.0\lib\pcl_people_release.lib\
        D:\software\PCL1.8.0\lib\pcl_recognition_release.lib\
        D:\software\PCL1.8.0\lib\pcl_registration_release.lib\
        D:\software\PCL1.8.0\lib\pcl_sample_consensus_release.lib\
        D:\software\PCL1.8.0\lib\pcl_search_release.lib\
        D:\software\PCL1.8.0\lib\pcl_segmentation_release.lib\
        D:\software\PCL1.8.0\lib\pcl_stereo_release.lib\
        D:\software\PCL1.8.0\lib\pcl_surface_release.lib\
        D:\software\PCL1.8.0\lib\pcl_tracking_release.lib\
        D:\software\PCL1.8.0\lib\pcl_visualization_release.lib
LIBS+=  D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_atomic-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_chrono-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_container-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_context-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_coroutine-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_date_time-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_exception-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_filesystem-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_graph-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_iostreams-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_locale-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_log_setup-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_log-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_math_c99f-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_math_c99l-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_math_c99-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_math_tr1f-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_math_tr1l-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_math_tr1-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_mpi-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_prg_exec_monitor-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_program_options-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_random-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_regex-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_serialization-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_signals-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_system-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_test_exec_monitor-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_thread-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_timer-vc140-mt-1_61.lib\
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_type_erasure-vc140-mt-1_61.lib
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_unit_test_framework-vc140-mt-1_61.lib
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_wave-vc140-mt-1_61.lib
        D:\software\PCL1.8.0\3rdParty\Boost\lib\libboost_wserialization-vc140-mt-1_61.lib
LIBS+=  D:\software\PCL1.8.0\3rdParty\FLANN\lib\flann_cpp_s.lib\
        D:\software\PCL1.8.0\3rdParty\FLANN\lib\flann_s.lib\
        D:\software\PCL1.8.0\3rdParty\FLANN\lib\flann.lib
LIBS+=  D:\software\PCL1.8.0\3rdParty\Qhull\lib\qhullstatic.lib\
        D:\software\PCL1.8.0\3rdParty\Qhull\lib\qhull.lib\
        D:\software\PCL1.8.0\3rdParty\Qhull\lib\qhull_p.lib\
        D:\software\PCL1.8.0\3rdParty\Qhull\lib\qhullcpp.lib\
        D:\software\PCL1.8.0\3rdParty\Qhull\lib\qhullstatic_r_d.lib
LIBS+=  D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkalglib-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkChartsCore-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkCommonColor-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkCommonComputationalGeometry-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkCommonCore-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkCommonDataModel-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkCommonExecutionModel-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkCommonMath-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkCommonMisc-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkCommonSystem-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkCommonTransforms-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkDICOMParser-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkDomainsChemistry-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkexoIIc-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkexpat-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersAMR-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersCore-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersExtraction-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersFlowPaths-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersGeneral-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersGeneric-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersGeometry-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersHybrid-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersHyperTree-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersImaging-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersModeling-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersParallel-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersParallelImaging-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersProgrammable-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersSelection-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersSMP-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersSources-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersStatistics-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersTexture-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkFiltersVerdict-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkfreetype-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkGeovisCore-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkgl2ps-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkhdf5-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkhdf5_hl-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkImagingColor-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkImagingCore-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkImagingFourier-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkImagingGeneral-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkImagingHybrid-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkImagingMath-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkImagingMorphological-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkImagingSources-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkImagingStatistics-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkImagingStencil-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkInfovisCore-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkInfovisLayout-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkInteractionImage-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkInteractionStyle-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkInteractionWidgets-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOAMR-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOCore-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOEnSight-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOExodus-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOExport-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOGeometry-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOImage-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOImport-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOInfovis-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOLegacy-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOLSDyna-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOMINC-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOMovie-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIONetCDF-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOParallel-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOParallelXML-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOPLY-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOSQL-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOVideo-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOXML-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkIOXMLParser-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkjpeg-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkjsoncpp-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtklibxml2-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkmetaio-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkNetCDF-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkNetCDF_cxx-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkoggtheora-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkParallelCore-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkpng-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkproj4-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingAnnotation-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingContext2D-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingContextOpenGL-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingCore-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingFreeType-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingGL2PS-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingImage-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingLabel-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingLIC-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingLOD-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingOpenGL-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingVolume-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkRenderingVolumeOpenGL-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtksqlite-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtksys-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtktiff-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkverdict-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkViewsContext2D-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkViewsCore-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkViewsInfovis-7.0.lib\
        D:\software\PCL1.8.0\3rdParty\VTK\lib\vtkzlib-7.0.lib
LIBS+=  D:\software\PCL1.8.0\3rdParty\OpenNI2\Lib\OpenNI2.lib
}

RESOURCES += \
    res.qrc
