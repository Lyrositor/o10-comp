int64_t main() {
  char a = 45;  // 0b00101101
  return ~a & 255; // 210 == 0b11010010
}
