void foo(int64_t c[]) {
  c[0] = 345;
}

int64_t main(){
  int64_t a[3];
  foo(a);
}
