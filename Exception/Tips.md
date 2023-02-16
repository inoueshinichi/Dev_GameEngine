
### Windows ATL(COM) Error (HRESULT)
https://learn.microsoft.com/ja-jp/cpp/windows/attributes/attribute-programming-faq?view=msvc-170  
#include <atlbase.h>  
| 名前 | 値 | 説明 |
| :-- | :-- | :-- |
| S_OK | 0x00000000 | 成功 |
| E_UNEXPECTED | 0x8000FFFF | 予期しないエラー |
| E_NOTIMPL | 0x80004001 | 未実装 |
| E_OUTOFMEMORY | 0x8007000E | メモリ割り当ての失敗 |
| E_INVALIDARG | 0x80070057 | 1 つ以上の引数が無効 |
| E_NOINTERFACE | 0x80004002 | インターフェースの未実装 |
| E_POINTER | 0x80004003 | 無効なポインタ |
| E_HANDLE | 0x80070006 | 無効なハンドル |
| E_ABORT | 0x80004004 | 中止 |
| E_FAIL | 0x80004005 | 不特定のエラー |
| E_ACCESSDENIED | 0x80070005 | アクセス拒否エラー |


### Windows API Error (システムエラー)
https://learn.microsoft.com/ja-jp/windows/win32/debug/error-handling  
https://learn.microsoft.com/ja-jp/windows/win32/debug/about-error-handling  
https://learn.microsoft.com/ja-jp/windows/win32/debug/error-handling-reference   
#include <winerror.h>
| 範囲 | URL |
| :-- | :-- |
| 0-499 | https://learn.microsoft.com/ja-jp/windows/win32/debug/system-error-codes--0-499- |
| 500-999 | https://learn.microsoft.com/ja-jp/windows/win32/debug/system-error-codes--500-999- |
| 1000-1299 | https://learn.microsoft.com/ja-jp/windows/win32/debug/system-error-codes--1000-1299- |
| 1300-1699 | https://learn.microsoft.com/ja-jp/windows/win32/debug/system-error-codes--1300-1699- |
| 1700-3999 | https://learn.microsoft.com/ja-jp/windows/win32/debug/system-error-codes--1700-3999- |
| 4000-5999 | https://learn.microsoft.com/ja-jp/windows/win32/debug/system-error-codes--4000-5999- |
| 6000-8199 | https://learn.microsoft.com/ja-jp/windows/win32/debug/system-error-codes--6000-8199- |
| 8200-8999 | https://learn.microsoft.com/ja-jp/windows/win32/debug/system-error-codes--8200-8999- |
| 9000-11999 | https://learn.microsoft.com/ja-jp/windows/win32/debug/system-error-codes--9000-11999- |
| 12000-15999 | https://learn.microsoft.com/ja-jp/windows/win32/debug/system-error-codes--12000-15999- |





