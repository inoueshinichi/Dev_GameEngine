# Dev_WinNativeGuiWithXaml
C++NativeDesktopApp with `Xaml Island` by `WinUI2`

特長
+ `WinUI2`を用いたNativeDesktopApp + XAML UI. 
+ WinUIに関して`WinUI3`が現行バージョンだが, `WinUI3`には後述する`Xaml Island`によるNativeDesktopAppへのホスティングが未実装.
+ オブジェクト指向に基づくWinNativeAPIをラッピングしたクラスの提供
+ WinRTが提供する`XAML Island`に基づくXAML UIへのアクセス
+ リソース管理をResource.hからXAMLに変更(Fluent Design Systemを利用可能)
+ SingleThreadアーキテクチャ(GUIはメインスレッドで稼働. イベントループもメインスレッドで稼働.)
+ XAMLはVisualStudio C#等で使用するUI XAMLエディタ(仮称)を使用? (未調査)
+ WinAPIとCOM(by C++/WinRT)をベースとしたプログラム

要件
+ \>= Windows 10 1903
+ Visual Studio 2019 (Toolset v142)
+ C++17
+ />= Windows SDK (Windows API, Windows Runtime API(`WinRT`)) 10.0.17134.0 (`XAML Island` with `WinUI2`)

特記
+ \>= Windows App SDK 1.2 (`WinUI3`)
+ `WinUI3`は以前, `Project Reunion`と呼称されていた

参考
| 項目 | URL |
| (C++/)WinRT(公式) | https://learn.microsoft.com/ja-jp/windows/uwp/cpp-and-winrt-apis/intro-to-using-cpp-with-winrt |
| Xaml Island(公式) | https://learn.microsoft.com/ja-jp/windows/apps/desktop/modernize/xaml-islands |
| WinUI(公式) | https://learn.microsoft.com/ja-jp/windows/apps/winui/ |
| WinUI3プロジェクトの作成(公式) | https://learn.microsoft.com/ja-jp/windows/apps/winui/winui3/create-your-first-winui3-app?source=recommendations |
| WinUI3の使い方(UWP) | https://zenn.dev/tan_y/articles/39e71426973512d3a97a |


