set(target_name junuoui)

set(misc_sources
    stdafx.h
    stdafx.cpp
)

set(sources
    button/buttons.h
    button/buttons.cpp
    progressbar/junuowaterprogressbar.h
    progressbar/junuowaterprogressbar.cpp
    customwidget/framelesswidget.h
    customwidget/framelesswidget.cpp
    customwidget/junuobasetitlebar.h
    customwidget/junuobasetitlebar.cpp
)

set(qrc_files
    resources/resources.qrc
)

set(resources
    resources/icon_svg/app_logo_default.svg
    resources/icon_svg/close.svg
    resources/icon_svg/maximum.svg
    resources/icon_svg/maximum_reset.svg
    resources/icon_svg/minimum.svg
)

junuo_add_library(${target_name} SHARED ${misc_sources} ${sources} ${qrc_files} ${resources})
junuo_use_Qt(${target_name} Core Widgets Gui)
junuo_auto_moc(${target_name} ${sources})
junuo_auto_rcc(${target_name} ${qrc_files} ${resources})
junuo_include_directories(${target_name} .)
junuo_compile_definitions(${target_name} _JUNUOUI_MODULE_)
