# Homework: Graph

**課程：** NDHU CSIE2000AA Data Structures  
**日期：** 2025/11/20

---

## 題目說明

有一批物件需要管理。每個物件都有一個整數權限值 `priority`，其範圍為
$0 \leq \text{priority} < \text{MAX}$，其中 $\text{MAX} = n$，而 $n$ 一般可以設定為 $2^k$。
`priority` 值越小，權限越大。

請設計一個類似 adjacency list 的資料結構來管理這批物件：將具有相同權限值的物件串接在同一個 linked list 中，並採用先進先出（FIFO）的方式管理相同權限值的物件。此資料結構需要提供以下函式：

1. `insertQ`：將一個物件插入資料結構中。
2. `deleteQ`：取出目前權限最高（`priority` 值最小）的物件。
3. `initQ`：初始化整個資料結構。

## 要求

1. `insertQ` 必須在常數時間內完成，時間複雜度為 $O(1)$。
2. `deleteQ` 必須在 $O(n)$ 以內完成。
3. 此資料結構必須能讓未來的使用者使用，因此必須提供使用說明文件（Markdown 文字或 PDF）。

## 版本

0. 皆不能使用 GNU C 提供的所有內建函式。
1. 完成上述要求：graphhwn 的檔案
2. `deleteQ` 的時間複雜度為 $O(\log n)$：graphhwlogn 的檔案
3. `deleteQ` 的時間複雜度為 $O(1)$（`deleteQ` 中不能使用迴圈）：graphhw1 的檔案
