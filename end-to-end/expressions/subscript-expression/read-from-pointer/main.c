void foo(int64_t c[]) {
  int64_t b = c[0];
}

int64_t main(){
  int64_t a[3];
  foo(a);
}
