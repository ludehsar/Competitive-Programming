#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    ordered_set<int> ost; // ordered set

    ost.insert(2);
    ost.insert(3);
    ost.insert(3);
    ost.insert(4);
    ost.insert(4);

    cout << *ost.find_by_order(1) << endl; // 3
    cout << *ost.find_by_order(2) << endl; // 4
    cout << ost.order_of_key(5) << endl; // 3
    cout << ost.order_of_key(3) << endl; // 1

    ordered_set<array<int, 2>> omst; // ordered multiset

    /*omst.insert({2, 1});
    omst.insert({4, 2});
    omst.insert({3, 3});
    omst.insert({4, 4});
    omst.insert({3, 5});

    cout << omst.order_of_key({5, 0}) << endl; // 5
    cout << omst.order_of_key({3, 0}) << endl; // 1
    */

    omst.insert({1, 1});
    omst.insert({1, 2});
    omst.insert({2, 3});
    omst.insert({2, 4});
    cout << omst.size() - omst.order_of_key({1, 200}) << endl;
}
