cmake_minimum_required(VERSION 3.18)
project(kadio)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to create code from Qt designer ui files
set(CMAKE_AUTOUIC ON)

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)


# Find the QtWidgets library
find_package(Qt5 CONFIG REQUIRED COMPONENTS
    Core    # QCommandLineParser, QStringLiteral
    Widgets # QApplication, QAction
    Multimedia
)

find_package(KF5 REQUIRED COMPONENTS
    CoreAddons      # KAboutData
    I18n            # KLocalizedString
    XmlGui          # KXmlGuiWindow, KActionCollection
    TextWidgets     # KTextEdit
    ConfigWidgets   # KStandardActions
    WidgetsAddons   # KMessageBox
    KIO             # KIO
)

set(CMAKE_INSTALL_RPATH "/home/cruz/kde/usr/lib64")


set(kadio_SRC
  src/main.cpp
  src/kadio.cpp
  src/station_list_item.cpp
)

# Tell CMake to create the helloworld executable
add_executable(kadio ${kadio_SRC})

set_target_properties(kadio
    PROPERTIES BUILD_WITH_INSTALL_RPATH ON
)


# Use the Widgets module from Qt 5.
target_link_libraries(kadio
    Qt5::Widgets
    Qt5::Multimedia
    KF5::CoreAddons
    KF5::I18n
    KF5::XmlGui
    KF5::TextWidgets
    KF5::ConfigWidgets
    KF5::WidgetsAddons
    KF5::KIOCore
)

# Install the executable
install(TARGETS kadio DESTINATION ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES src/kadioui.rc DESTINATION ${KDE_INSTALL_KXMLGUI5DIR}/kadio)
