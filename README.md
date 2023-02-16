# Dev_WinNativeGuiWithXamlIsland
Win32APIのオブジェクト指向プログラムとXAML_UI(UWP)の融合  

特長
+ Win32APIを内包したクラスの提供(オブジェクト指向)
+ WinRTが提供するXAML Islandインターフェースを利用したUWPなUIへのアクセス
+ リソース管理をResource.hからXAMLに変更
+ SingleThreadアーキテクチャ(GUIはメインスレッドで稼働. イベントループもメインスレッドで稼働.)
+ XAMLはVisualStudio C#等で使用するUI XAMLエディタ(仮称)を使用
+ WinAPIとCOM(by WinRT)をベースとしたプログラム

要件
+ Visual Studio 2019
+ C++17
+ Windows API
+ WinRT (`XAML Island` Component)


