const int SIZE = 1000000;

//criba[i] = false si i es primo
bool criba[SIZE+1];

void buildCriba(){
  memset(criba, false, sizeof(criba));

  criba[0] = criba[1] = true;
  for (int i=4; i<=SIZE; i += 2){
    criba[i] = true;
  }
  for (int i=3; i*i<=SIZE; i += 2){
    if (!criba[i]){
      for (int j=i*i; j<=SIZE; j += i){
        criba[j] = true;
      }
    }
  }
}
