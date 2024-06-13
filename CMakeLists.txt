set(target_name junuoui)

set(misc_sources
    stdafx.h
    stdafx.cpp
)

set(button_sources
    button/buttons.h
    button/buttons.cpp
    progressbar/junuowaterprogressbar.h
    progressbar/junuowaterprogressbar.cpp
)

junuo_add_library(${target_name} SHARED ${misc_sources} ${button_sources})
junuo_use_Qt(${target_name} Core Widgets Gui)
junuo_auto_moc(${target_name} ${button_sources})
junuo_include_directories(${target_name} .)
junuo_compile_definitions(${target_name} _JUNUOUI_MODULE_)
