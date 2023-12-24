#include <vector>
class RangeSumSegmentTree {
private:
    std::vector<int> tree;
    std::vector<int> lazy;
    int n;

    void buildTree(const std::vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            buildTree(arr, 2 * node, start, mid);
            buildTree(arr, 2 * node + 1, mid + 1, end);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    void updateRange(int node, int start, int end, int l, int r, int val) {
        if (lazy[node] != 0) { 
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
        if (start > end or start > r or end < l)
            return;
        if (start >= l and end <= r) {
            tree[node] += (end - start + 1) * val;
            if (start != end) {
                lazy[node * 2] += val;
                lazy[node * 2 + 1] += val;
            }
            return;
        }
        int mid = (start + end) / 2;
        updateRange(node * 2, start, mid, l, r, val);
        updateRange(node * 2 + 1, mid + 1, end, l, r, val);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    int queryRange(int node, int start, int end, int l, int r) {
        if (start > end or start > r or end < l)
            return 0; 
        if (lazy[node] != 0) {
            tree[node] += (end - start + 1) * lazy[node]; 
            if (start != end) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0; 
        }
        if (start >= l and end <= r) 
            return tree[node];
        int mid = (start + end) / 2;
        int p1 = queryRange(node * 2, start, mid, l, r);
        int p2 = queryRange(node * 2 + 1, mid + 1, end, l, r);
        return (p1 + p2);
    }

public:
    RangeSumSegmentTree(const std::vector<int>& arr) {
        n = arr.size();
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        buildTree(arr, 1, 0, n - 1);
    }

    void update(int l, int r, int val) {
        updateRange(1, 0, n - 1, l, r, val);
    }

    int query(int l, int r) {
        return queryRange(1, 0, n - 1, l, r);
    }
};
using SegmentTree = RangeSumSegmentTree;
