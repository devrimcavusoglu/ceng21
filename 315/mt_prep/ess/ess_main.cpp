using namespace std;

#include <iostream>
#include <vector>

class PartitionSet {
public:
  bool canPartition(const vector<int> &num) {
    return this->canPartitionRecursive(num, 0, 0);
  }

  bool canPartitionRecursive(const vector<int> &num, int currentSum, int currentIndex) {
    /*
    * Assume there exists `s` sum, where sum(S_1) = sum(S_2) = s
    * We will try to populate S_1 until sum(S_1) > sum(S_2)
    * For each item
    * include item i in S_1 and get sum(S_1), call it s_1,
    * skip item i in S_2 and get sum(S_2), call it s_2,
    * return max(s_1, s_2) ??
    */
    int s_2 = 0;
    int size = num.size();
    if (currentIndex >= size)
      return false;

    for (int i = currentIndex; i < size; i++)
      s_2 += num[i];

    if (currentSum == s_2)
      return true;
    else if (currentSum > s_2)
      return false;
    else {
      bool c_1;
      // include current item
      c_1 = canPartitionRecursive(num, currentSum + num[currentIndex], currentIndex+1);
      if (c_1)
        return true;
      else
        return false;
    }
  }
};

int main(int argc, char *argv[]) {
  PartitionSet ps;
  vector<int> num = {1, 2, 3, 4};
  cout << ps.canPartition(num) << endl;
  num = vector<int>{1, 1, 3, 4, 7};
  cout << ps.canPartition(num) << endl;
  num = vector<int>{2, 3, 4, 6};
  cout << ps.canPartition(num) << endl;
}