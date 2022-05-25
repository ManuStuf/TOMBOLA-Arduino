/**
   Sviluppatore: Stufano Manuele
   Data: 25/05/2022
   Titolo: TOMBOLA
*/

#include <LiquidCrystal.h>
#include <IRremote.h>
#include <time.h>

int num = 0,        //numero da estrarre
    tot[90] {},     //array contente i numeri della tombola
    mem = 0,        //variabile di memorizzazione dell'ultimo numero estratto
    massimo = 89;   //posizione ultima cella dell'array

byte block[8] {     //creazione casella intera per schermo LCD
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

int receiver = 7;   //PIN ricevitore raggi infrarossi
IRrecv irrecv(receiver);
decode_results results;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void special_effect();  //funzione di presentazione iniziale
void start_arr(int);    //funzione di riepimento dell'array
void delete_var(int&, int, int, int&);  //funzione di cancellazione della variabile estratta

void setup() {

  lcd.begin(16, 2);

  lcd.createChar(0, block);

  special_effect();   //presentazione progetto

  lcd.setCursor(0, 0);
  lcd.print("corrente:");

  lcd.setCursor(0, 1);
  lcd.print("ultimo:");

  irrecv.enableIRIn();

  randomSeed (analogRead(9));
}

void loop() {

  start_arr(tot);   //riempimento array

  for (int count = 90; count >= 1; count--) {
    irrecv.resume();
    if (irrecv.decode(&results)) {
      num = random(massimo) + 1;    //estrazione numero casuale

      lcd.setCursor(9, 0);
      lcd.print(tot[num]);    //stampa del numero estratto

      lcd.setCursor(7, 1);    //stampa del numero precedentemente estratto
      lcd.print(mem);

      delete_var(mem, tot, num, massimo);   //cancellazione numero estratto dall'array
    }
  }
}

void special_effect() {

  lcd.clear();    //svuotamento schermo LCD da eventuali scritte

  for (int x = 0; x < 2; x++) {     //inizio riempimento schermo LCD
    for (int y = 0; y < 16; y++) {
      lcd.setCursor(y, x);
      lcd.write(byte(0));
    }
  }   //fine riempimento schermo LCD

  delay(300);

  for (int y1 = 7, y2 = 8; y2 < 16; y1--, y2++) {   //inizio effetto tenda in apertura
    for (int x = 0; x < 2; x++) {
      lcd.setCursor(y1, x);
      lcd.print(' ');

      lcd.setCursor(y2, x);
      lcd.print(' ');
    }
    delay(200);
  }   //fine effetto tenda in apertura

  delay(700);

  lcd.setCursor(0, 0);
  lcd.print("TOMBOLA");   //stampa titolo del progetto

  lcd.setCursor(0, 1);
  lcd.print("Stufano Manuele");   //stampa sviluppatore

  delay(1500);

  for (int y1 = 15, y2 = 0; y2 < 16; y1--, y2++) {    //inizio effetto tenda in chiusura
    for (int x = 0; x < 2; x++) {
      lcd.setCursor(y1, x);
      lcd.write(byte(0));

      lcd.setCursor(y2, x);
      lcd.write(byte(0));
    }
    delay(200);
  }   //fine effetto tenda in chiusura

  lcd.clear();
}

void start_arr(int v[]) {   //caricamento array
  for (int i = 1; i < 90; i++) {
    v[i] = i + 1;
  }
}

void delete_var(int& m, int v[], int n, int& x) {   //cancellazione ultimo numero estratto
  int p = 0;

  m = v[n];
  p = v[x];
  v[x] = v[n]; //eliminazione variabile
  v[n] = p;
  x -= 1;
}
