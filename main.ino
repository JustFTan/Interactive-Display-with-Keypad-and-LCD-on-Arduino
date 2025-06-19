//Library untuk 7 segment, keypad, dan LCD I2C
#include <TM1637Display.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

//Menginisialisasi ukuran LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Menginisialisasi pin pada arduino
const int CLK = 12;
const int DIO = 13;
const byte button = 2;

//Mendeklarasikan variabel interrupt, ADC, dan keypad
volatile byte state = LOW;
unsigned int adcval;
char key;

//4 baris
const byte ROWS = 4;

//4 kolom
const byte COLS = 4;

//pin untuk kontrol baris
byte colPins[COLS] = { 10, 9, 8, 7 };  

//pin untuk kontrol kolom
byte rowPins[ROWS] = { 6, 5, 4, 3 };   

//Penggambaran keypad ke program
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },  //
  { '4', '5', '6', 'B' },  //
  { '7', '8', '9', 'C' },  //
  { '*', '0', '#', 'D' }   //
};

//Mendeklarasi keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//Mendeklarasi display untuk 7 segment
TM1637Display display(CLK, DIO);

//Inisialisasi Segment a mati
const uint8_t a[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G
};

//Inisialisasi Segment b mati
const uint8_t b[] = {
  SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G
};

//Inisialisasi Segment c mati
const uint8_t c[] = {
  SEG_A | SEG_B | SEG_D | SEG_E | SEG_F | SEG_G
};

//Inisialisasi Segment d mati
const uint8_t d[] = {
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G
};

//Inisialisasi Segment e mati
const uint8_t e[] = {
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G
};

//Inisialisasi Segment f mati
const uint8_t f[] = {
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_G
};

//Inisialisasi Segment g mati
const uint8_t g[] = {
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F
};


void setup() {
  Serial.begin(9600);
  lcd.begin();

  //Menginisialisasi pin button
  pinMode(button, INPUT_PULLUP);
  //Menambahkan tombol interrupt 
  attachInterrupt(digitalPinToInterrupt(button), interupsi, FALLING);

  uint8_t allon[] = { 0xff, 0xff, 0xff, 0xff };



    //Menyalakan semua segment
    display.setBrightness(0x0f);
    display.setSegments(allon);

    lcd.setCursor(0, 0);
    lcd.setCursor(0, 1);

    lcd.print("<<<  LCD ON  >>>");
    lcd.print("<<<  SUCCESS >>>");


  //Jeda 500ms
  delay(500);
}

void loop() {

  //Masuk mode no 1
  modeawal();

}


//Fungsi untuk mode counter down 9-0 ketika menekan push button
void interrupt() {
  lcd.setCursor(0, 0);
  lcd.print("<<<  SUCCESS >>>");
  lcd.setCursor(0, 1);
  lcd.print("<Mode Interrupt>");
  for (int i = 9; i >= 0; i--) {
    display.showNumberDec(i, false);
  }
}


//Fungsi untuk mode menampilkan nilai ADC ketika menekan '1'
void adc() {
  int i = 1;
  while (i > 0) {
  lcd.setCursor(0, 0);
  lcd.print("<<<  SUCCESS >>>");
  lcd.setCursor(0, 1);
  lcd.print("< Mode key = 1 >");
    key = keypad.getKey();
    adcval = analogRead(A0);
    display.showNumberDec(ADC, false);
    Serial.println(ADC);
    delay(100);

    if (state) {
      state = false;
      interrupt();
    } else if (key == 'C' || key == 'c') {
      modeawal();
    }
    i++;
  }
}

//Fungsi untuk mode berkedip ketika menekan '5'
void blink() { 
  int i = 1;
  uint8_t allon[] = { 0xff, 0xff, 0xff, 0xff };
  //Menyalakan semua lampu 7 segment
  display.setBrightness(0x0f);

  while (i > 0) {
    lcd.setCursor(0, 0);
    lcd.print("<<<  SUCCESS >>>");
    lcd.setCursor(0, 1);
    lcd.print("< Mode key = 5 >");
    key = keypad.getKey();
    if (state) {
      state = false;
      interrupt();
    } else if (key == '1') {
      adc();
    } else if (key == 'C' || key == 'c') {
      modeawal();
    }

    //Untuk nyala dan mati 7 Segment
    display.setBrightness(7, false);  
    display.setSegments(allon);
    delay(500);
    display.setBrightness(7, true);  
    display.setSegments(allon);

    key = keypad.getKey();

    //Jeda 500ms
    delay(500);
    if (state) {
      state = false;
      interrupt();
    } else if (key == '1') {
      adc();
    } else if (key == 'C' || key == 'c') {
      modeawal();
    }
    i++;
  }
}


//Fungsi untuk mode no 1
void modeawal() {
  int i, x = 1;
  while (x > 0) {
    lcd.setCursor(0, 0);
    lcd.print("<<<  SUCCESS >>>");
    lcd.setCursor(0, 1);
    lcd.print("<<<  Mode 1  >>>");

    //Segment a mati 1x
    for (i = 0; i < 2; i++) {
      key = keypad.getKey();
      display.setSegments(a, 1, 0);
      display.setSegments(a, 1, 1);
      display.setSegments(a, 1, 2);
      display.setSegments(a, 1, 3);
      //Jeda 500ms = 250 * 2
      delay(250);
      if (state) {
        state = false;
        interrupt();
      } else if (key == '1') {
        adc();
      } else if (key == '5') {
        blink();
      }
    }

    //Segment b mati 1x
    for (i = 0; i < 2; i++) {
      key = keypad.getKey();
      display.setSegments(b, 1, 0);
      display.setSegments(b, 1, 1);
      display.setSegments(b, 1, 2);
      display.setSegments(b, 1, 3);
      //Jeda 500ms = 250 * 2
      delay(250);
      if (state) {
        state = false;
        interrupt();
      } else if (key == '1') {
        adc();
      } else if (key == '5') {
        blink();
      }
    }

    //Segment c mati 1x
    for (i = 0; i < 2; i++) {
      key = keypad.getKey();
      display.setSegments(c, 1, 0);
      display.setSegments(c, 1, 1);
      display.setSegments(c, 1, 2);
      display.setSegments(c, 1, 3);
      //Jeda 500ms = 250 * 2
      delay(250);
      if (state) {
        state = false;
        interrupt();
      } else if (key == '1') {
        adc();
      } else if (key == '5') {
        blink();
      }
    }

    //Segment d mati 1x
    for (i = 0; i < 2; i++) {
      key = keypad.getKey();
      display.setSegments(d, 1, 0);
      display.setSegments(d, 1, 1);
      display.setSegments(d, 1, 2);
      display.setSegments(d, 1, 3);
      //Jeda 500ms = 250 * 2
      delay(250);
      if (state) {
        state = false;
        interrupt();
      } else if (key == '1') {
        adc();
      } else if (key == '5') {
        blink();
      }
    }

    //Segment e mati 1x
    for (i = 0; i < 2; i++) {
      key = keypad.getKey();
      display.setSegments(e, 1, 0);
      display.setSegments(e, 1, 1);
      display.setSegments(e, 1, 2);
      display.setSegments(e, 1, 3);
      //Jeda 500ms = 250 * 2
      delay(250);
      if (state) {
        state = false;
        interrupt();
      } else if (key == '1') {
        adc();
      } else if (key == '5') {
        blink();
      }
    }

    //Segment f mati 1x
    for (i = 0; i < 2; i++) {
      key = keypad.getKey();
      display.setSegments(f, 1, 0);
      display.setSegments(f, 1, 1);
      display.setSegments(f, 1, 2);
      display.setSegments(f, 1, 3);
      //Jeda 500ms = 250 * 2
      delay(250);
      if (state) {
        state = false;
        interrupt();
      } else if (key == '1') {
        adc();
      } else if (key == '5') {
        blink();
      }
    }

    //Segment g mati 1x
    for (i = 0; i < 2; i++) {
      key = keypad.getKey();
      display.setSegments(g, 1, 0);
      display.setSegments(g, 1, 1);
      display.setSegments(g, 1, 2);
      display.setSegments(g, 1, 3);
      //Jeda 500ms = 250 * 2
      delay(250);
      if (state) {
        state = false;
        interrupt();
      } else if (key == '1') {
        adc();
      } else if (key == '5') {
        blink();
      }
    }

    //Segment a mati 2x
    for (i = 0; i < 2; i++) {
      key = keypad.getKey();
      display.setSegments(a, 1, 0);
      display.setSegments(a, 1, 1);
      display.setSegments(a, 1, 2);
      display.setSegments(a, 1, 3);
      //Jeda 500ms = 250 * 2
      delay(250);
      if (state) {
        state = false;
        interrupt();
      } else if (key == '1') {
        adc();
      } else if (key == '5') {
        blink();
      }
    }

    //Segment b mati 2x
    for (i = 0; i < 2; i++) {
      key = keypad.getKey();
      display.setSegments(b, 1, 0);
      display.setSegments(b, 1, 1);
      display.setSegments(b, 1, 2);
      display.setSegments(b, 1, 3);
      //Jeda 500ms = 250 * 2
      delay(250);
      if (state) {
        state = false;
        interrupt();
      } else if (key == '1') {
        adc();
      } else if (key == '5') {
        blink();
      }
    }

    //Segment c mati 2x
    for (i = 0; i < 2; i++) {
      key = keypad.getKey();
      display.setSegments(c, 1, 0);
      display.setSegments(c, 1, 1);
      display.setSegments(c, 1, 2);
      display.setSegments(c, 1, 3);
      //Jeda 500ms = 250 * 2
      delay(250);
      if (state) {
        state = false;
        interrupt();
      } else if (key == '1') {
        adc();
      } else if (key == '5') {
        blink();
      }
    }

    //Segment d mati 2x
    for (i = 0; i < 2; i++) {
      key = keypad.getKey();
      display.setSegments(d, 1, 0);
      display.setSegments(d, 1, 1);
      display.setSegments(d, 1, 2);
      display.setSegments(d, 1, 3);
      //Jeda 500ms = 250 * 2
      delay(250);
      if (state) {
        state = false;
        interrupt();
      } else if (key == '1') {
        adc();
      } else if (key == '5') {
        blink();
      }
    }

    //Segment e mati 2x
    for (i = 0; i < 2; i++) {
      key = keypad.getKey();
      display.setSegments(e, 1, 0);
      display.setSegments(e, 1, 1);
      display.setSegments(e, 1, 2);
      display.setSegments(e, 1, 3);
      //Jeda 500ms = 250 * 2
      delay(250);
      if (state) {
        state = false;
        interrupt();
      } else if (key == '1') {
        adc();
      } else if (key == '5') {
        blink();
      }
    }

    //Segment f mati 2x
    for (i = 0; i < 2; i++) {
      key = keypad.getKey();
      display.setSegments(f, 1, 0);
      display.setSegments(f, 1, 1);
      display.setSegments(f, 1, 2);
      display.setSegments(f, 1, 3);
      //Jeda 500ms = 250 * 2
      delay(250);
      if (state) {
        state = false;
        interrupt();
      } else if (key == '1') {
        adc();
      } else if (key == '5') {
        blink();
      }
    }

    //Segment g mati 2x
    for (i = 0; i < 2; i++) {
      key = keypad.getKey();
      display.setSegments(g, 1, 0);
      display.setSegments(g, 1, 1);
      display.setSegments(g, 1, 2);
      display.setSegments(g, 1, 3);
      //Jeda 500ms = 250 * 2
      delay(250);
      if (state) {
        state = false;
        interrupt();
      } else if (key == '1') {
        adc();
      } else if (key == '5') {
        blink();
      }
    }

    //Menampilkan angka 4 pada digit terakhir dan 3 digitnya sisanya mati
    for (i = 0; i < 2; i++) {
      key = keypad.getKey();
      display.showNumberDec(4, false); 
      //Jeda 500ms = 250 * 2 
      delay(250);
      if (state) {
        state = false;
        interrupt();
      } else if (key == '1') {
        adc();
      } else if (key == '5') {
        blink();
      }
    }
  }
  x++;
}

//Membalikan kondisi interrupt ke awal
void interupsi() {
  state = !state;
}
