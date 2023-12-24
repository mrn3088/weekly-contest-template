#include <vector>

class FenwickTree {
private:
    std::vector<int> tree;
    int n;
    int lowbit(int x) const {
        return x & (-x);
    }

public:
    explicit FenwickTree(int size) : n(size), tree(size + 1, 0) {}

    explicit FenwickTree(const std::vector<int>& nums) : FenwickTree(nums.size()) {
        for (int i = 0; i < nums.size(); ++i) {
            add(i, nums[i]);
        }
    }

    void add(int index, int value) {
        for (index++; index <= n; index += lowbit(index)) {
            tree[index] += value;
        }
    }

    void update(int index, int value) {
        int current_value = sum(index) - sum(index - 1);
        int delta = value - current_value;
        add(index, delta);
    }

    int sum(int index) const {
        int res = 0;
        for (index++; index > 0; index -= lowbit(index)) {
            res += tree[index];
        }
        return res;
    }

    int range_sum(int l, int r) const {
        return sum(r) - sum(l - 1);
    }
};
