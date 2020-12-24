// 1 Oktober 2019
// Final Code Mini Scale Machine

#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>


LiquidCrystal_I2C lcd(0x27,20,4);

const byte rows = 4; 
const byte columns = 4; 
char gram[3];
int n;
int time;
int pos = 0;
int redLed = 13;
//int buzzer = 12;          //uncomment kalau nak pakai buzzer

char buttons[rows][columns] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowP[rows] = {9, 8, 7, 6}; 
byte columnsP[columns] = {5, 4, 3, 2}; 
Keypad pad = Keypad( makeKeymap(buttons), rowP, columnsP, rows, columns );    //create keypad

int i=0;

Servo myservo;                  //create servo objek

void setup(){
    
    lcd.begin();
    lcd.backlight();
    lcd.print("Insert gram:");
    myservo.attach(11);
    myservo.write(pos);
    pinMode(redLed, OUTPUT);
    //pinMode(buzzer,OUTPUT);     //uncomment kalau nak pakai buzzer
    
}

void loop(){
  char keypressed = pad.getKey();  
  lcd.setCursor(0, 0);
  
  if(keypressed != NO_KEY){       //ambil input dari keypadd
    
    lcd.setCursor(4+i,1);
    lcd.println(keypressed);
  
    gram[i]=keypressed;
    i++ ;
  
      if(keypressed == '#'){      //buat button # dijadikan sebagai button enter
      
        gram[i] = '\0';           
        n = atoi(gram);           //simpan array gram dalam nilai integer
      
      
         if(n >= 31){             //menghadkan gram kepada 30g sahaja
          lcd.clear();
          lcd.print("Error!");
          i = 0;
          delay(1000);
          lcd.clear();
          lcd.print("Insert gram");
          }
         else{                   //motor berputar mengikut masa per gram yang ditetapkan
          Serial.println(n);
          lcd.setCursor(4,1);
          lcd.println(n);
          lcd.clear();
          time = n*1000;
          lcd.print("Time open:");
          lcd.print(time/1000);
          delay(1000);
          LedOpen();
          ServoClose();
          delay(time);
          ServoOpen();
          LedClose();
          lcd.clear();
          lcd.print("Insert gram");
          }
  i = 0; 
  
  }
  if(i >= 4){                     //menghadkan array gram kepada 3 tempat sahaja
    lcd.clear();
    lcd.print("Error!");
    i = 0;
    delay(1000);
    lcd.clear();
    lcd.print("Insert gram");
    delay(1000);
    lcd.clear();
    lcd.print("Insert gram");
  }
  if( keypressed == '*'){         //menetapkan button "*" sebagai button reset
    lcd.clear();
    i = 0;
    lcd.print("Insert gram");
  }
  if( keypressed == 'A'||keypressed == 'B' ||keypressed == 'C'||keypressed == 'D'  ){       //membuang fungsi kepada button A,B,C dan D
    lcd.clear();
    i = 0;
    lcd.print("Error!");
    delay(500);
     lcd.clear();
    lcd.print("Insert gram:");
  }
}

}
  
//OPERASI BUKA SERVO
void ServoOpen(){
  for (pos = 90; pos >= 0; pos -= 5){ 
    myservo.write(pos);              
    delay(15);
}
}
//OPERASI TUTUP SERVO
void ServoClose(){
  for (pos = 0; pos <= 90; pos += 5){ 
    myservo.write(pos);              
    delay(15);
    }
  }
 void LedOpen(){
    digitalWrite (redLed, HIGH);
    //tone(buzzer,1000,500);           //buang //kalau nak pakai buzzer
    //delay(700);
    
}
 void LedClose(){
    digitalWrite (redLed, LOW);
 }
