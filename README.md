# Qt_virtualKeyboard
用QWidget写的一个windows10触屏键盘

编译器版本：
vs2015
Qt5.7.1
本项目是考虑在window10触屏模式下模仿window10自带虚拟键盘制作的一款虚拟键盘
(window10自带的osk键盘不好看，taptip键盘调不出来)

键盘支持中英文切换，中文是调用的Qt自带的Goolge的中文库
路径：xxx\Qt5.7.1\5.7\Src\qtvirtualkeyboard\src\virtualkeyboard\3rdparty\pinyin

此虚拟键盘代码固定为触屏自动弹出，对于鼠标点击等操作不会响应，要改为由鼠标进行操作可以在键盘类里面定制修改
