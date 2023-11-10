# Dev_GameEngine
OpenGL, DirectX12, Metalによる包括的なレンダリングエンジンの作成

## アーキテクチャ
+ マルチスレッド & イベントループ
+ イベントクラスとイベントディスパッチャー
+ 抽象基底クラスと各CGフレームワークを具体クラスで構成(基本機能はBaseクラスで実装)
+ 行列は行優先表現に統一(数学的に B@Aは, コード上でA@Bになる)
+ 継承(エクステンド)と委譲(コンポーネント)の両方を利用する. (基本機能は, コンポーネントで機能追加の方針で)
+ 継承は最小限で構成
+ CoordinateContextによる座標系定義の切り替え(Left or Light, Forward-Right-Up)

## 機能カテゴリー
| カテゴリ | 用途 |
| Widget | 画面機能 |
| Game | ゲームエンジンの中核 |
| Renderer | 描画機能 |
| RenderingPipeline | Renderer参加, 各種Shader機能の統括 |
| Shader | 描画パイプライン用のシェーダの窓口 |
| CoordinateContext | 座標系定義の切り替え |
| VertexArray | 頂点属性 |
| Mesh | 3Dメッシュ |
| Texture | 2Dスプライト |
| Actor | アクター |
| Component | アクターに機能追加 |
| Camera | 視点操作, 透視投影 |
| Lighting | 環境光, 平行光, 点光源, 拡散反射, 鏡面反射 |
| Event | 各種OSイベント |
| EventDispatcher | プロセスキューから取り出したイベント(メッセージ)を所属するイベントループに渡す |
| AudioSystem | 音源 2D, 3D |
| InputSystem | 各種コントローラ等からの入力処理 |
| NetworkSystem | 各種ネットワーク関連を統括 |






## 下記のXaml Islandは, 終了. '23/11以降, このレポジトリは無関係とする

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
| :-- | :-- |
| (C++/)WinRT(公式) | https://learn.microsoft.com/ja-jp/windows/uwp/cpp-and-winrt-apis/intro-to-using-cpp-with-winrt |
| Xaml Island(公式) | https://learn.microsoft.com/ja-jp/windows/apps/desktop/modernize/xaml-islands |
| Xaml Islandの使い方 | https://qiita.com/cubeundcube/items/93c210f8516c9468f5e5 |
| MSIXパッケージ(公式) | https://learn.microsoft.com/ja-jp/windows/msix/overview |
| WinUI(公式) | https://learn.microsoft.com/ja-jp/windows/apps/winui/ |
| WinUI3プロジェクトの作成(公式) | https://learn.microsoft.com/ja-jp/windows/apps/winui/winui3/create-your-first-winui3-app?source=recommendations |
| WinUI3の使い方(UWP) | https://zenn.dev/tan_y/articles/39e71426973512d3a97a |


