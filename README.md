# Dev_WinNativeGuiWithXaml
Win32APIのオブジェクト指向プログラムとXAML_UI(UWP)の融合  

特長
+ WinUI3を用いたNativeDesktopApp + XAML UI. 
+ WinUI3はNative, UWP, WPF, Windows Formなどすべての開発環境からアクセスできるUIコンポーネント.
+ オブジェクト指向に基づくWin32NativeAPIをラッピングしたクラスの提供
+ WinRTが提供するXAML Islandに基づくXAML UIへのアクセス
+ リソース管理をResource.hからXAMLに変更(Fluent Design Systemを利用可能)
+ SingleThreadアーキテクチャ(GUIはメインスレッドで稼働. イベントループもメインスレッドで稼働.)
+ XAMLはVisualStudio C#等で使用するUI XAMLエディタ(仮称)を使用? (未調査)
+ WinAPIとCOM(by C++/WinRT)をベースとしたプログラム

要件
+ \>= Windows 10 1903
+ Visual Studio 2019 (Toolset v142)
+ C++17
+ />= Windows SDK (Windows API, Windows Runtime API(`WinRT`)) 10.0.17134.0 (`XAML Island` with `WinUI2`)
+ >= Windows App SDK 1.2 (`WinUI3`)


