cmake_minimum_required(VERSION 3.19)

project(RollScript
    VERSION 0.1.0
    LANGUAGES CXX
)

add_subdirectory(Application)

# -----------------------------------------------------------------------------
# Plugins
# -----------------------------------------------------------------------------
add_subdirectory(Plugins/Printers/DymoLabelPoint350)
#add_subdirectory(Plugins/Features/LabelBlockText)
