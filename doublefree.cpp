void fn(void) {
  int *arr = new int[10];
  delete arr;
  delete arr;
}

int main(void) {
  fn();
  return (0);
}
