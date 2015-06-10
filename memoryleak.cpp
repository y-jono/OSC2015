class Hoge{ private: int a; };

void func() {
    Hoge* hoge = new Hoge();
    int* array = new int[1000];
}

int main() {
  for(;;){
    func();
  }
}
