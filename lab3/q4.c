#include <stdio.h>
#include <stdlib.h>

// 定义最小堆结构
typedef struct {
    long long *data;
    int size;
    int capacity;
} MinHeap;

// 初始化堆
MinHeap* createHeap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (long long*)malloc(sizeof(long long) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// 交换元素
void swap(long long *a, long long *b) {
    long long temp = *a;
    *a = *b;
    *b = temp;
}

// 向上调整
void heapifyUp(MinHeap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->data[parent] > heap->data[index]) {
            swap(&heap->data[parent], &heap->data[index]);
            index = parent;
        } else {
            break;
        }
    }
}

// 向下调整
void heapifyDown(MinHeap *heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;
    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;

    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        heapifyDown(heap, smallest);
    }
}

// 插入元素
void insert(MinHeap *heap, long long value) {
    if (heap->size == heap->capacity) return;
    heap->data[heap->size] = value;
    heapifyUp(heap, heap->size);
    heap->size++;
}

// 提取最小值
long long extractMin(MinHeap *heap) {
    if (heap->size == 0) return -1;
    long long minVal = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return minVal;
}

int main() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) return 0;

    // 最大可能节点数：n + 补齐的0节点
    // 补齐数量最多 k-2 个
    MinHeap *heap = createHeap(n + k);

    for (int i = 0; i < n; i++) {
        long long w;
        scanf("%lld", &w);
        insert(heap, w);
    }

    // 补齐虚拟节点
    // 每次合并减少 k-1 个节点
    // 最后剩 1 个节点
    // (n + added - 1) % (k - 1) == 0
    int remainder = (n - 1) % (k - 1);
    if (remainder != 0) {
        int added = (k - 1) - remainder;
        for (int i = 0; i < added; i++) {
            insert(heap, 0);
        }
    }

    long long totalLength = 0;

    // 构建哈夫曼树
    while (heap->size > 1) {
        long long sum = 0;
        // 取出 k 个最小节点
        for (int i = 0; i < k; i++) {
            sum += extractMin(heap);
        }
        totalLength += sum;
        insert(heap, sum);
    }

    printf("%lld\n", totalLength);

    free(heap->data);
    free(heap);
    return 0;
}
