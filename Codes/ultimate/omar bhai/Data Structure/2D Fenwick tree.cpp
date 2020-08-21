int sum[10][10], row,col;
void update(int x,int y,int val){
  while(x<=row){
    while(y<=col){
      sum[x][y]+=val;
      y+=y&(-y);
    }
    x+=x&(-x);
  }
}
int getSum(int x,int y){
  int res=0;
  while(x){
    while(y){
      res+=sum[x][y];
      y-=y&(-y);
    }
    x-=x&(-x);
  }
  return res;
}
