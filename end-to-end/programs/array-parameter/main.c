void write_ok(char msg[]) {
  msg[0] = 'O';
  msg[1] = 'K';
  msg[2] = '\n';
}

void main() {
  char msg[3];
  write_ok(msg);
  putchar(msg[0]);
  putchar(msg[1]);
  putchar(msg[2]);
}
