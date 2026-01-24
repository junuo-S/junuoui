junuo_package(junuoui SHARED)

junuo_sources(
    junuo_moc
    stdafx.h
    stdafx.cpp

    button/buttons.h
    button/buttons.cpp
    progressbar/junuowaterprogressbar.h
    progressbar/junuowaterprogressbar.cpp
    customwidget/junuoframelesswidget.h
    customwidget/junuoframelesswidget.cpp
    customwidget/junuobasetitlebar.h
    customwidget/junuobasetitlebar.cpp

    resources/resources.qrc
)

junuo_use_packages(Qt6Core Qt6Widgets Qt6Gui)
junuo_include_directories(.)
junuo_compile_definitions(_JUNUOUI_MODULE_)
