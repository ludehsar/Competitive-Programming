//Calculating common path between node (a,b) and (c,d)
int main() {
  scanf("%d %d %d %d",&a,&b,&c,&d);
  int t1=lca(a,b),t2=lca(c,d);
  if (dep[t1]>dep[t2]) {
    swap(a,c); swap(b,d); swap(t1,t2);
  }
  int p1=lca(a,c),p2=lca(b,d);
  int p3=lca(a,d),p4=lca(b,c);
  int k1,k2;
  if (p1==t1) k1=p4; else k1=p1;
  if (p2==t1) k2=p3; else k2=p2;
  if (dis(k1,k2)==1&&t2!=k1) // no intersection
  else // the path is (k1,k2)
}
