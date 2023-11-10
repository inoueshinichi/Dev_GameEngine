# Dev_GameEngine
OpenGL, DirectX12, Metalによる包括的なレンダリングエンジンの作成

## 参考
+ 

## 背景
+ 3DCVという観点から興味があった
+ 中身の実装部分を理解したい
+ ゲームを作って挙げられる人になりたい

## 目的
+ CGの勉強
+ Unix系GUIフレームワークのGTKの理解
+ Linux(OpenGL), MacOS(Metal), DirectX12(Windows)のクロスプラットフォームゲームエンジンの勉強
+ AR・VRの勉強

## ロードマップ
| マイルストン | 内容 | 達成状況 |
| :-- | :-- | :-- |
| 0合目 | 大まかな要件定義 | - |
| 1合目 | 詳細な要件定義 | - |
| 2合目 | 非機能要件の定義 | - |
| 3合目 | アーキテクチャ設計 | - |
| 3合目 | 各種クラスの洗い出し | - |
| 4合目 | デザインパターンの適用箇所の検討 | - |
| 5合目 | 抽象クラスの実装 | - |
| 6合目 | Windows環境でOS機能を使ってUI機能の実装 | - |
| 7合目 | Windows環境でEvent&Dispatcher機能の実装 | - |
| 8合目 | Windows環境でDirectX12による基本的な描画ループを実装 | - |
| 9合目 | Windows環境でOpenGLによる基本的な描画ループを実装 | - |
| 10合目 | MacOS/Linux環境でGTKによるUI機能の実装 | - |
| 11合目 | MacOS環境でMetalによる基本的な描画ループを実装 | - |
| 12合目 | MacOS/Linux環境でGTKによるEvent&Dispatcher機能の実装 | - |
| 13合目 | Actor,Component,Renderer,Pipelineの実装 | - |
| 14合目 | CoordinateContext,Math,Projectionの実装 | - |
| 15合目 | Windows環境でVertexArray,Shader,Mesh,Textureの実装 | - |
| 16合目 | AudioSystem,InputSystem,Camera,Lightingの実装 | - |
| 17合目 | Collision,PhysWorld,Skeleton,Animationの実装 | - |
| 18合目 | NetworkSytemの実装| - |
| 19合目 | 各種PipeLine用Shaderを実装 | - |
+ ....


## 機能要件
| カテゴリ | 用途 |
| :-- | :-- |
| Widget | 画面機能 |
| Game | ゲームエンジンの中核 |
| Renderer | 描画機能. パイプラインや描画用リソースを管理 |
| Pipeline | レンダリングパイプライン. 各種Shader機能の統括 |
| Math | 基本関数,Dot,Cross,回転行列,クォータニオン,回転ベクトル,オイラー角 |
| Shader | 描画パイプライン用のシェーダの窓口 |
| ProjectionContext | 3Dから2D画面への投影方法, パラメータを担当. カメラ座標系からNDC座標系への変換. |
| VertexArray | 頂点属性 |
| Mesh | 3Dメッシュ |
| Texture | 2Dスプライト |
| Actor | アクター |
| Component | アクターに機能追加 |
| Camera | 視点操作 |
| Lighting | 環境光, 平行光, 点光源, 拡散反射, 鏡面反射 |
| Event | 各種OSイベント |
| EventDispatcher | プロセスキューから取り出したイベント(メッセージ)を所属するイベントループに渡す |
| AudioSystem | 音源 2D, 3D |
| InputSystem | 各種コントローラ等からの入力処理 |
| NetworkSystem | 各種ネットワーク関連を統括 |
| ModelConverter | 3Dモデルファイルのコンバーター |
| Skeleton | スケルトンモデル |
| Animation | アニメーション |
| Collision | 衝突検知 |
| PhysWorld | 物理演算 |


## アーキテクチャ
+ Windows環境のUIはOS機能を使用. Unix環境のUIはGTKを使用.
+ シングルスレッド型イベントループ (できればマルチスレッドでUI描画とゲームエンジンの描画を切り離したいが...)
+ イベントクラスとイベントディスパッチャー
+ 抽象基底クラスと各CGフレームワークを具体クラスで構成(基本機能はBaseクラスで実装)
+ 行列は行優先表現に統一(数学的に B@Aは, コード上でA@Bになる)
+ 継承(エクステンド)と委譲(コンポーネント)の両方を利用する. (基本機能は, コンポーネントで機能追加の方針で)
+ 継承は最小限に済ませる
+ ProjectionContextにより透視投影変換やZバッファの設定によるNDC定義を変更する.
+ Position等もすべてベクトルクラスで管理する.
+ 演算時の浮動小数点数は, floatを使用する.

## ワールド及びモデル座標系定義は, DirecX12, Metalスタイルを選定
+ 座標系: 左手, Forward: z, Right: x, Up: y

## カメラ座標系の座標系定義は, UE系を採用
+ 座標系: 左手, Forward: -z, Right: x, Up: -y

## NDCの座標系定義
+ 座標系: 右手, Forward: -z(Inverse Z), Right: x, Up: -y

## ビューポートの座標定義
+ zバッファはマイナスな程手前にある.
+ 左上原点で, ↓に+y, →に+z


## 非機能要件
+ 変数名, 関数名はCamel記法 : myValue, myMethod()
+ プライベートは名前の先頭に_をつける : _myValue, _myMethod()
+ C++ == 20
+ CMake > *
+ UIエンジン GTK @ Unix > *
+ サウンドエンジン FMOD > *
+ OpenGL @ Linux > *
+ DirectX12 @ Windows > *
+ Metal @ MacOS > *

## 使用ツール
+ Visual Studio 2022
+ Blender (3Dモデル作成)
+ UML
+ WanderMax EdrawMax (クラス図)

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


