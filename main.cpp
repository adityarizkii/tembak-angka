#include <iostream>
#include <conio.h>
#include <string>
#include <cstdlib>
using namespace std;

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define RED     "\033[31m"
#define GRAY    "\033[30m"

struct Ball{
  int value;
  Ball *prev;
  Ball *next;
};
Ball *head, *tail, *newBall, *next, *prev, *cur, *del;

struct Player{
  string name;
  int score;
};

char petak[100] = {'_','_','_','_','_','_','_','_','_','_'};
Player players[100];
int numOfBalls = 0, playersLength = 0, posisi = 0, peluru, score = 0, level = 1;

int getRandomNum(){
  int randomNumber = rand() % 4 + 1;
  return randomNumber;
}

char intToStr(int num){
  char result = '0' + num;
  return result;
}

void printBalls(){
  cur = head;
  while(cur != nullptr){
    if(cur->value == 1){
      cout<<MAGENTA<<cur->value<<" "<<RESET;
    } else if(cur->value == 2){
      cout<<YELLOW<<cur->value<<" "<<RESET;
    } else if(cur->value == 3){
      cout<<GREEN<<cur->value<<" "<<RESET;
    } else {
      cout<<CYAN<<cur->value<<" "<<RESET;
    }
    cur = cur->next;
  }
}

void printPetak(int petakLength){
  for(int i = 0; i < petakLength; i++){
    if(petak[i] == '1'){
      cout<<MAGENTA<<" "<<petak[i]<<RESET;
    } else if(petak[i] == '2'){
      cout<<YELLOW<<" "<<petak[i]<<RESET;
    } else if(petak[i] == '3') {
      cout<<GREEN<<" "<<petak[i]<<RESET;
    } else if(petak[i] == '4') {
      cout<<CYAN<<" "<<petak[i]<<RESET;
    } else {
      cout<<" "<<petak[i];
    }
  }
}

void createBall(int num){
  if(numOfBalls == 0){
    head = new Ball();
    head->value = num;
    head->prev = nullptr;
    head->next = nullptr;
    tail = head;
    numOfBalls++;
  } else {
    newBall = new Ball();
    newBall->value = num;
    newBall->prev = nullptr;
    newBall->next = nullptr;
    numOfBalls++;
  }
}

void insertBallAtFirst(){
  newBall->next = head;
  head->prev = newBall;
  head = newBall;
}

void insertBall(){
  cur = head;
  int counter = 0;
  while(cur != nullptr){
    if(posisi == counter){
      if(posisi == numOfBalls-1){ //apakah bola yang dimasukkan berada paling akhir
        createBall(peluru);
        newBall->prev = tail;
        tail->next = newBall;
        tail = newBall;
      } else {
        createBall(peluru);
        newBall->next = cur->next;
        newBall->prev = cur;

        cur->next->prev = newBall;

        cur->next = newBall;
      }
    }
    counter++;
    cur = cur->next;
  }
}

void removeBall(){ //remove ball yang ditunjuk *del (*cur)
  del = cur;
  if(del == head){
    head = head->next;
    delete head->prev;
    head->prev = nullptr;
    del = head;
    numOfBalls--;
  } else if(del == tail){
    tail = tail->prev;
    delete tail->next;
    tail->next = nullptr;
    del = tail;
    numOfBalls--;
  } else {
    del = del->next;
    del->prev = del->prev->prev;
    delete del->prev->next;
    del->prev->next = del;
    numOfBalls--;
  }
  cur = del;
}

void countScore(int jumlahKembar){
  score += jumlahKembar;
}

void kembarCheck(){
  int kembarKanan = 1;
  int kembarKiri = 1;
  cur = newBall;
  if(cur == tail){
    while(cur->value == cur->prev->value){
      kembarKiri++;
      cur = cur->prev;
      if(cur->prev == nullptr){
        break;
      }
    }
  } else {
    while(cur->value == cur->next->value){
      kembarKanan++;
      cur = cur->next;
      if(cur->next == nullptr){
        break;
      }
    }
    cur = newBall;
    while(cur->value == cur->prev->value){
      kembarKiri++;
      cur = cur->prev;
      if(cur->prev == nullptr){
        break;
      }
    }
  }
  
  int jumlahKembar = kembarKanan + (kembarKiri - 1);
  if(jumlahKembar >= 3){
    for(int i = 0; i < jumlahKembar; i++){
      removeBall();
    }
    countScore(jumlahKembar);
    if(posisi > numOfBalls){
      posisi = numOfBalls;
    }
  }
}

void sortLeaderboard(){
  for(int i = 0; i < playersLength; i++){
    for(int j = 0; j < playersLength-i; j++){
      if(players[j].score < players[j+1].score){
        Player temp = players[j];
        players[j] = players[j+1];
        players[j+1] = temp;
      }
    }
  }
}

void showLeaderboard(){
  system("cls");
  cout<<"         ====> Leaderboard <====\n\n";
  if(playersLength == 0){
    cout<<"Belum ada yang mencatatkan skor, ayo bermain !";
  }
  sortLeaderboard();
  for(int i = 0; i < playersLength; i++){
    cout<<i+1<<". "<<players[i].name<<" dengan skor "<<players[i].score<<endl<<endl;
  }
}

void game(){
  numOfBalls = 0, posisi = 0, peluru, score = 0;
  srand(time(0)); 
  for(int i = 0; i < 10; i++){ //buat 10 bola diawal
    createBall(getRandomNum());
    if(numOfBalls > 1){
      insertBallAtFirst();
    }
  }

  bool firstWhile = true;
  while(true){
    system("cls");
    cout<<"SCORE = "<<score<<"\n\n";
    printBalls(); //cetak bola bola
    for(int i = 0; i < 25 - numOfBalls; i++){
      cout<<" _";
    }
    cout<<"|"; //cetak pembatas gameover
    cout<<"\n\n\n";

    if(firstWhile){
      peluru = getRandomNum();
      firstWhile = false;
    }
    petak[posisi] = intToStr(peluru); // menaruh peluru sesuai pada posisi

    printPetak(numOfBalls); // cetak petak sepanjang bola

    cout<<GRAY<<"\n\nTekan a / d untuk bergerak !\nTekan j untuk menembak !\nTekan q jika ingin keluar !\n"<<RESET; 
    char key = getch();
    petak[posisi] = '_'; //mengisi petak bola saat digeser kiri kanan
    if(key == 'j'){
      insertBall(); //masuukan bola kearah yang dituju
      kembarCheck(); //cek apakah ada yang kembar lalu hapus
      if(numOfBalls < 7){ //buat bola bertambah ekstra ketika kurang dari 7
        createBall(getRandomNum()); 
        insertBallAtFirst();
      }
      createBall(getRandomNum()); //buat bola bertambah setiap nembak
      insertBallAtFirst();

      for(int i = 0; i < numOfBalls; i++){ //mengisi semua petak dengan karakter '_'
        petak[i] = '_';
      }

      peluru = getRandomNum(); //mengisi peluru dengan angka acak
    } else if(key == 'a'){
      posisi--;
      if(posisi < 0){
        posisi = numOfBalls-1;
      }
    } else if(key == 'd'){
      posisi++;
      if(posisi > numOfBalls-1){
        posisi = 0;
      }
    } else if(key == 'q'){
      break;
    }

    if(numOfBalls > 25){ //gameover
      string name;
      cout<<"\n   == GAMEOVER ==   \n\n"; 
      getch();
      cout<<"Masukkan namamu : "; cin>>name;
      players[playersLength].name = name; //memasukkan nama player ke leaderboard
      players[playersLength].score = score; //memasukkan score player ke leaderboard
      playersLength++;
      showLeaderboard();
      getch();
      break;
    }
  }
}

int main(){
  int pilihan = 0;
  mainMenu:
  while(true){
    system("cls");
    if(pilihan == 0){
      cout<<"========================\n"; 
      cout<<"====  Tembak Angka  ====\n"; 
      cout<<"========================\n"; 
      cout<<"|                      |\n"; 
      cout<<"|  "<<CYAN<<"==> Mulai Main <=="<<RESET<<"  |\n"; 
      cout<<"|                      |\n"; 
      cout<<"| Cara Main            |\n"; 
      cout<<"|                      |\n"; 
      cout<<"| Leaderboard          |\n"; 
      cout<<"|                      |\n"; 
      cout<<"| Keluar               |\n"; 
      cout<<"|                      |\n"; 
      cout<<"========================\n"; 
      cout<<GRAY<<"Tekan w / s untuk naik / turun !\nTekan j untuk memilih !\n"<<RESET;
    } else if(pilihan == 1){
      cout<<"========================\n"; 
      cout<<"====  Tembak Angka  ====\n"; 
      cout<<"========================\n"; 
      cout<<"|                      |\n"; 
      cout<<"| Mulai Main           |\n"; 
      cout<<"|                      |\n"; 
      cout<<"|  "<<CYAN<<"==> Cara Main <=="<<RESET<<"   |\n"; 
      cout<<"|                      |\n"; 
      cout<<"| Leaderboard          |\n"; 
      cout<<"|                      |\n"; 
      cout<<"| Keluar               |\n"; 
      cout<<"|                      |\n"; 
      cout<<"========================\n"; 
      cout<<GRAY<<"Tekan w / s untuk naik / turun !\nTekan j untuk memilih !\n"<<RESET;
    } else if(pilihan == 2){
      cout<<"========================\n"; 
      cout<<"====  Tembak Angka  ====\n"; 
      cout<<"========================\n"; 
      cout<<"|                      |\n"; 
      cout<<"| Mulai Main           |\n"; 
      cout<<"|                      |\n"; 
      cout<<"| Cara Main            |\n"; 
      cout<<"|                      |\n"; 
      cout<<"|  "<<CYAN<<"==> Leaderboard <=="<<RESET<<" |\n"; 
      cout<<"|                      |\n"; 
      cout<<"| Keluar               |\n";  
      cout<<"|                      |\n"; 
      cout<<"========================\n"; 
      cout<<GRAY<<"Tekan w / s untuk naik / turun !\nTekan j untuk memilih !\n"<<RESET;
    } else if(pilihan == 3){
      cout<<"========================\n"; 
      cout<<"====  Tembak Angka  ====\n"; 
      cout<<"========================\n"; 
      cout<<"|                      |\n"; 
      cout<<"| Mulai Main           |\n"; 
      cout<<"|                      |\n"; 
      cout<<"| Cara Main            |\n";  
      cout<<"|                      |\n"; 
      cout<<"| Leaderboard          |\n"; 
      cout<<"|                      |\n"; 
      cout<<"|    "<<RED<<"==> Keluar <=="<<RESET<<"    |\n";  
      cout<<"|                      |\n"; 
      cout<<"========================\n"; 
      cout<<GRAY<<"Tekan w / s untuk naik / turun !\nTekan j untuk memilih !\n"<<RESET;
    }
    char key = getch();
    if(key == 'w'){
      pilihan--;
      if(pilihan < 0){
        pilihan = 3;
      }
    } else if(key == 's'){
      pilihan++;
      if(pilihan > 3){
        pilihan = 0;
      }
    } else if(key == 'j'){
      break;
    }
  }
  if(pilihan == 0){
    system("cls");
    game();
    goto mainMenu;
  } else if(pilihan == 1){
    system("cls");
    cout<<"         ====> Cara Main <====\n\n";
    cout<<"1. Tekan a / d untuk bergerak kiri / kanan.\n\n";
    cout<<"2. Tekan j untuk menembak.\n\n";
    cout<<"3. Tembak angka yang memiliki minimal 3 kembaran.\n\n";
    cout<<"4. Setiap tembakan angka random akan muncul satu.\n\n";
    cout<<"5. Jangan sampai angka menyentuh garis.\n\n";
    getch();
    goto mainMenu;
  } else if(pilihan == 2){
    system("cls");
    showLeaderboard();
    getch();
    goto mainMenu;
  } else if(pilihan == 3){
    system("cls");
    cout<<"===========================\n";
    cout<<"==                       ==\n";
    cout<<"==  Ingin Keluar ? (Y/N) ==\n";
    cout<<"==                       ==\n";
    cout<<"===========================\n\n";
    confirm:
    char exit = getch();
    if(exit == 'y' || exit == 'Y'){
      return 0;
    } else if(exit == 'n' || exit == 'N'){
      goto mainMenu;
    } else {
      goto confirm;
    }
  }
}