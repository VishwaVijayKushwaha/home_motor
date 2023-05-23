#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

const int relaySda = 18;
const int relaySlc = 19;

void message(String message);
void inputLoop();
void switchLoop();
void displayLoop();

void setup() {
  Serial.begin(9600); 
  Serial.println();
  Serial.println("Setup started..............");

  lcd.init(); 
  lcd.backlight(); 

  pinMode(relaySda, OUTPUT);
  pinMode(relaySlc, OUTPUT);

  Serial.println();
  Serial.println("Setup done...........");
}

int i = 0;
void loop() {
  try{
    inputLoop();
  }catch(...){}
  if(++i) {
    try{
      switchLoop();
    }catch(...){}
  }
  if(i%100) {
    try {
      displayLoop();
    } catch(...){}
  }
}

//message("Running loop1 %d", xPortGetCoreID());
//vTaskDelay(7000);
String clearbuffer = "                    ";

void print(char message[], int line) {
  lcd.setCursor(0, line);
  lcd.print(clearbuffer);
  lcd.setCursor(0, line);
  lcd.print(message);
  lcd.setCursor(0, 0);
  lcd.print("   Madhuri Niwash   ");
}

void message(int position, char * format, ...) {
  char buffer[20];
  va_list args;
  va_start (args, format);
  vsnprintf (buffer, 255, format, args);
  va_end (args);
  print(buffer, position);
}

byte motor = 0;
char 9'[name[8][2] = {"G1", "G2", "G3", "G4", "11", "12", "13", "14"};

void inputLoop(){

}
void switchLoop(){

}

void displayLoop(){

}
