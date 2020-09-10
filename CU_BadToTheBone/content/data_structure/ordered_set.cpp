/**
 * Policy Based Data Structure (PBDS)
 * 
 * The following code works like a set and a multiset respectively.
 * ordered_set is used to find the number of elements less or greater than a certain element, and the relative position of the element.
 * In order to declare a multiset, you should declare a variable of type ordered_set< array<int, 2> >.
 */

#include "../utility/template.hpp"

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
  ordered_set<int> ost; // ordered set
  ost.insert(2);
  ost.insert(3);
  ost.insert(3);
  ost.insert(5);

  // find_by_order(x) returns the element in position x
  cout << *ost.find_by_order(1) << endl; // 3
  cout << *ost.find_by_order(2) << endl; // 5

  // order_of_key(x) returns the relative position of x in the set/multiset.
  cout << ost.order_of_key(4) << endl; // 2
  cout << ost.order_of_key(3) << endl; // 1

  ordered_set<array<int, 2>> omst; // ordered multiset
  omst.insert({2, 1});
  omst.insert({4, 2});
  omst.insert({3, 3});
  omst.insert({4, 4});
  omst.insert({3, 5});

  cout << omst.order_of_key({5, 0}) << endl; // 5
  cout << omst.order_of_key({3, 0}) << endl; // 1

  omst.clear();

  omst.insert({1, 1});
  omst.insert({1, 2});
  omst.insert({2, 3});
  omst.insert({2, 4});
  cout << omst.order_of_key({1, 200}) << endl; // 2
  cout << sz(omst) - omst.order_of_key({1, 200}) << endl; // 2
}
