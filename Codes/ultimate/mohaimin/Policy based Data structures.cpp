#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; ///set in ascending order (the typical one)
template <typename T>
using ordered_set_of_pairs = tree<pair<T, size_t>, null_type, less<pair<T, size_t>>, rb_tree_tag, tree_order_statistics_node_update>; ///set of pairs in ascending order (the typical one)
template <typename T>
using ordered_set_desc = tree<T, null_type, greater<T>, rb_tree_tag, tree_order_statistics_node_update>;  ///set in descending order
template <typename T>
using ordered_set_of_pairs_desc = tree<pair<T, size_t>, null_type, greater<pair<T, size_t>>, rb_tree_tag, tree_order_statistics_node_update>; ///set of pairs in descending order

#define optimize() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define endl '\n'

#define MP make_pair
#define F first
#define S second
#define PB push_back

ordered_set<int> st1;
ordered_set_of_pairs<int> st2;
ordered_set_desc<int> st3;
ordered_set_of_pairs_desc<int> st4;

int main() {
  optimize();
  for( int i = 0; i < 10; ++i ) st1.insert(i);
  cout << st1.order_of_key(2) << endl;   ///how many elements in st1 less than 2? (output: 2)
  cout << *st1.find_by_order(5) << endl << endl;   ///what is the 5th minimum element in st1?(0th based indexing) (output: 5)
  for( int i = 0; i < 10; ++i ) st2.insert(MP(i, i));
  cout << st2.order_of_key(MP(2, 3)) << endl; ///output: 3
  cout << st2.order_of_key(MP(2, 2)) << endl; ///output: 2
  cout << st2.order_of_key(MP(3, 2)) << endl; ///output: 3
  cout << st2.order_of_key(MP(3, -1)) << endl; ///output: 4 (i know, you were expecting 3. but giving negative numbers as second element gives unexpected results.)
  cout << (*st2.find_by_order(5)).F << " " << (*st2.find_by_order(5)).S << endl << endl; ///output: 5 5
}
