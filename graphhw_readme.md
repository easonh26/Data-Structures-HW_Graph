# 簡介

提供三種不同實作方式，提供不同時間複雜度。使用者可以依據自身需求，選擇最適合的版本。所有的實作皆支援基本的 初始化 (Init)、插入 (Insert) 與 刪除 (Delete) 操作，且內部皆維持先進先出 (FIFO) 的順序來處理相同優先權的資料

## 檔案與編譯

使用者將會取得 `.h` (標頭檔) 與 `.o` (編譯後的物件檔)

在編譯專案時，請連結相應的 `.o` 檔案

| 版本名稱 | 對應標頭檔 | 對應物件檔 | 時間複雜度 | 描述 |
| --- | --- | --- | --- | --- |
| Simple (Linear) | `graphhwn.h` | `graphhwn.o` | O(N) | 簡易實作，適合少量資料 |
| Min-Heap (Log) | `graphhwlogn.h` | `graphhwlogn.o` | O(log N) | 使用 Min-Heap 管理優先權 |
| Bitset (Const) | `graphhw1.h` | `graphhw1.o` | O(1) | 使用位元操作查找，極快 |


**備註：**

所有程式皆需與 `mloccpy.h` / `.o` 一起使用

Min-Heap 版本需與 `minheap.h` / `.o` 一起使用

Bitset 版本需與 `bitset.h` / `.o` 一起使用


---

## 1. 宣告

所有版本皆使用 obj 結構陣列作為主要容器。在使用任何函式前，請務必先宣告並配置

```c
#define L_SIZE 1024 // 最大支援的優先權層級數量
obj list[L_SIZE]; // 宣告方式範例
```

## 2. 版本詳細使用說明

### A. Simple

最基礎的版本，刪除時會線性掃描所有優先權

- 引入檔案: `#include "graphhwn.h"`
- 初始化:
  ```c
  int initQ(obj* list);
  ```
  - 初始化
- 插入資料:
  ```c
  int insertQ(obj* list, void* data, int priority, int data_size);
  ```
  - data: 指向要儲存資料的指標
  - priority: 資料的優先權 (0 ~ L_SIZE-1)
  - data_size: 資料的大小 (以 bytes 為單位)，函式內部會 mloc 並複製資料
- 刪除資料:
  ```c
  void* deleteQ(obj* list);
  ```
  - 回傳優先權最高（數值最小）且最早進入的資料指標。若佇列為空則回傳 NULL

### B. Min-Heap

使用 Min-Heap 來維護「目前存在的優先權」，適合優先權分佈稀疏的情況。由於內部使用 Min-Heap 儲存優先權 (int*)，必須提供一個比較函式。以下是範例：

```c
int compareInts(void* a, void* b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}
```

- 引入檔案: `#include "graphhwlogn.h"`

初始化:

```c
int initQ(obj* list);
```

- 初始化陣列，還會在 list[0] 處配置 Min-Heap
- 插入資料:
  ```c
  int insertQ(obj* list, void* data, int priority, int data_size,
              int compare(void*, void*));
  ```
  - 需加入 compare 函式
  - 當新的優先權出現時，會使用此函式將其推入 Heap 中
- 刪除資料:
  ```c
  void* deleteQ(obj* list, int compare(void*, void*));
  ```
  - 需加入 compare 函式 (用於 Heap 的維護)

### C. Bitset

使用位元運算來達到 O(1) 的查找速度。

- 引入檔案: `#include "graphhw1.h"`
- 介面與 Simple 版完全相同，可參考 A.
  - `initQ(obj* list)`
  - `insertQ(obj* list, void* data, int priority, int data_size)`
  - `deleteQ(obj* list)`
