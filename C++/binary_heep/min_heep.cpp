#include <optional>
#include <vector>
using namespace std;
class Heap {
public:
  Heap() = default;

  void push(int val) {
    data.push_back(val);
    heapify_up(data.size() - 1);
  }

  std::optional<int> peek() const {
    if (data.empty())
      return std::nullopt;
    return data[0];
  }

  std::optional<int> pop() {
    if (data.empty())
      return std::nullopt;

    size_t last = data.size() - 1;
    std::swap(data[0], data[last]);
    int min = data.back();
    data.pop_back();

    if (!data.empty()) {
      heapify_down(0);
    }

    return min;
  }

private:
  std::vector<int> data;

  void heapify_up(size_t mut_index) {
    while (auto parent = parent_index(mut_index)) {
      if (data[mut_index] < data[*parent]) {
        std::swap(data[mut_index], data[*parent]);
        mut_index = *parent;
      } else {
        break;
      }
    }
  }

  void heapify_down(size_t mut_index) {
    size_t len = data.size();

    while (true) {
      size_t left = 2 * mut_index + 1;
      size_t right = 2 * mut_index + 2;
      size_t smallest = mut_index;

      if (left < len && data[left] < data[smallest]) {
        smallest = left;
      }
      if (right < len && data[right] < data[smallest]) {
        smallest = right;
      }

      if (smallest == mut_index)
        break;

      std::swap(data[mut_index], data[smallest]);
      mut_index = smallest;
    }
  }

  std::optional<size_t> parent_index(size_t index) const {
    if (index == 0)
      return std::nullopt;
    return (index - 1) / 2;
  }
};
