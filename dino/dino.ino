#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd( 0x27 , 16 , 2 );

unsigned long timer = 0;

byte dinoCordX = 1;
byte dinoCordY = 1;

byte barCordX = 0;
byte barCordY = 0;

byte score = 0;
byte dino_char_1[8] = {
  B00011,
  B00011,
  B00010,
  B10010,
  B11110,
  B01110,
  B01010,
  B10001
};
byte dino_char_2[8] = {
  B00011,
  B00011,
  B00010,
  B10010,
  B11110,
  B01110,
  B01010,
  B01010
};

byte dino_char_3[8] = {
  B00011,
  B00011,
  B00010,
  B10010,
  B11110,
  B01110,
  B11011,
  B00000
};

byte bar_char_1[8] = {
  B01110,
  B11111,
  B11111,
  B11111,
  B10101,
  B00100,
  B00100,
  B00100
};

byte bar_char_2[8] = {
  B00000,
  B00000,
  B00100,
  B01101,
  B11111,
  B01100,
  B00100,
  B00000
};

byte null_char[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};



void clearChar(byte cord1, byte cord2) {
  lcd.setCursor(cord1, cord2);
  lcd.write(0);
}

void drawDino(byte dinoX, byte dinoY) {
  lcd.setCursor(dinoX, dinoY);
  if (timer % 2 == 0 && dinoY == 1) {
    lcd.write(1);
  } else if (dinoY == 1){
    lcd.write(2);
  } else if (dinoY == 0){
    lcd.write(5);
    }

}

void drawBar(byte cord1, byte cord2) {
  lcd.setCursor(cord1, cord2);
  if (cord2 == 0) {
    lcd.write(4);
  } else {
    lcd.write(3);
    }

}
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, null_char);
  lcd.createChar(1, dino_char_1);
  lcd.createChar(2, dino_char_2);
  lcd.createChar(3, bar_char_1);
  lcd.createChar(4, bar_char_2);
  lcd.createChar(5, dino_char_3);
  lcd.setCursor(0, 1);

  pinMode(12, INPUT);
  Serial.begin(9600);

  //clearChar(barCordX, barCordY);
  barCordX = random(5, 16);
  barCordY = random(0, 2);
  //drawBar(barCordX, barCordY);
}
boolean jumped = 0;
boolean flag = 0;
void readBut() {
  boolean jump = digitalRead(12);
  if (jump == true && flag == false)
    flag = true;
}

void loop() {
  //lcd.clear();
  lcd.setCursor(14, 0);
  lcd.print(score);
  readBut();
  if (flag == true) {
    clearChar(1, 1);
    dinoCordY = 0;
    drawDino(dinoCordX, dinoCordY);
    flag = false;
  } else {
    dinoCordY = 1;
    clearChar(1, 0);
    drawDino(dinoCordX, dinoCordY);
  }

  if (barCordX > 0) {
    clearChar(barCordX, barCordY);
    barCordX--;
    drawBar(barCordX, barCordY);

  } else {
    clearChar(0, 0);
    clearChar(0, 1);
    barCordX = random(5, 14);
    barCordY = random(0, 2);
  }

  if (dinoCordX == barCordX && dinoCordY == barCordY) {
    boolean i = 1;
    while (i) {
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("GAME OVER");
      lcd.setCursor(2, 1);
      lcd.print("YOUR SCORE");
      lcd.setCursor(13, 1);
      lcd.print(score);
      delay(1000);
      if (digitalRead(12)) {
        lcd.clear();
        score = -1;
        i = 0;
      };
    }
  }
  if (dinoCordX == barCordX) {
    score++;
  }
  delay(100);
  timer++;
}
