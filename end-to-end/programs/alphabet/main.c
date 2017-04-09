void main() {
  for (int64_t cur = 'A'; cur <= 'Z'; cur++) {
    putchar(cur & 1 ? cur : cur | 32);
  }
  putchar('\n');
}
