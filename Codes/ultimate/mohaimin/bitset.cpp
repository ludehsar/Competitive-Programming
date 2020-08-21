int main() {
  bitset<5005> bss[l2] , now ;

  bss[i].set(j); // sets jth bit of i'th bitset
  now = bss[i]&bss[j]; // can do logical operation betwn two bitset
  int here = now.count(); // counts number of 1s in the bitset
  now[i] = 1; // sets i-th bit from right ( 0 based) to 1
  now.all() ; // check if all the bits are set
  now.any() ; // checks if any bits are set
  now.none() ; //checks if none of the bits are set

  bitset<5005> bs1, bs2, bs3;	//Complexity of declaring bitsets is O(N/32)

  bs3 = bs1 ^ bs2  (Complexity is O(N/32))
  bs3 = bs1 & bs2  (Complexity is O(N/32))
  bs3 = bs1 | bs2  (Complexity is O(N/32))
  bs3 = bs2 (Complexity is O(N/32))
  bs3 = ~bs3 // inverse all bits.
  bs3.Find_next(idx); (Complexity is O(N/32)) //Finds the position of set bit after idx;
  bs3.Find_First(); (Complexity is O(N/32)) //Finds the first set bit; return bs3.size() if there is no set bit;
  bs3.reset(); //rests all bits
  bs3.set(); //set all bits
  bs3.flip(); //flip all bits
  bs3 = ~bs3; //flip all bits
  cout<<bb.to_ullong()<<"\n"; // to unsigned long long int
  return 0;
}
