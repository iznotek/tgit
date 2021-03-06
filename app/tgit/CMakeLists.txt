cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(tgit WIN32
  src/main.cpp
  src/GraphRow.hpp
  src/Reference.hpp
  resources/images.qrc
)
add_classes(tgit PRIVATE
  History
  HistoryModelAdaptor
  ReferenceDatabase
  ReferencesModel
  ReferenceItemDelegate
  GraphItemDelegate
  CommitView
  CommitDiffModel
  CodeViewer
  GraphBuilder
  TGitApplication
)
add_widgets(tgit PRIVATE
  TGitMainWindow
  FileDiffWidget
  CommitDetailsWidget
)
add_resource(tgit)
target_link_libraries(tgit
  PRIVATE Qt5::Widgets
          Qt5::Svg
          stx
          gitpp
)
target_include_directories(tgit
  PRIVATE src
)
set_target_properties(tgit PROPERTIES
  VS_DEBUGGER_ENVIRONMENT "PATH=${DEBUGGER_PATHS};$(PATH)"
)

install(
  TARGETS tgit
  RUNTIME DESTINATION bin
)
install(
  FILES $<TARGET_PDB_FILE:tgit>
  DESTINATION bin
)
