#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

byte pin[] = {15,2,4,5,18,19,21,7}; 
int count = 8;
// LED pins
const int relaySda = 18;
const int relaySlc = 19;

void loopTwo( void * pvParameters );
void loopOne( void * pvParameters );
void message(String message);


TaskHandle_t Task1;
TaskHandle_t Task2;

void setup() {
  Serial.begin(9600); 
  Serial.println();
  Serial.println("Setup started..............");

  lcd.init(); 
  lcd.backlight(); 
  
  lcd.setCursor(3,0);   //Set cursor to character 2 on line 0
  lcd.print("Madhuri Niwash");
  
  pinMode(relaySda, OUTPUT);
  pinMode(relaySlc, OUTPUT);

  xTaskCreatePinnedToCore(loopOne, "loopOne", 10000, NULL, 1, &Task1, 0);          /* pin task to core 0 */                  
  delay(10);
  xTaskCreatePinnedToCore(loopTwo, "loopTwo", 10000, NULL, 1, &Task2, 1);          /* pin task to core 1 */
  delay(10); 
  Serial.println();
  Serial.println("Port setup done........");
}

void loop() {
  
}

void loop1() {
  
  message("Running loop1 %d", xPortGetCoreID());
  vTaskDelay(7000);

}

void loop2() {
  vTaskDelay(10000);
  message("Running loop2 %d", xPortGetCoreID());
}



void print(char message[]) {
  char clearbuffer[40] = "                    ";
  lcd.setCursor(0,3);
  lcd.print(clearbuffer);
  lcd.setCursor(0,3);
  lcd.print(message);
}

void message(char * format, ...) {
  char buffer[20];
  va_list args;
  va_start (args, format);
  vsnprintf (buffer, 255, format, args);
  va_end (args);
  print(buffer);
}


void loopOne( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());
  for(;;) {
    try {
      loop1();
    }catch(...) {}
  }
}

//Task2code: blinks an LED every 700 ms
void loopTwo( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());
  for(;;) {
    try {
      loop2();
    }catch(...) {}
  }
}
















































// #if CONFIG_FREERTOS_UNICORE
// #define ARDUINO_RUNNING_CORE 0
// #else
// #define ARDUINO_RUNNING_CORE 1
// #endif

// #ifndef LED_BUILTIN
// #define LED_BUILTIN 2
// #endif

// void TaskBlink( void *pvParameters );
// void TaskAnalogReadA3( void *pvParameters );

// void setup() {
  
//   Serial.begin(9600);
  
//   // Now set up two tasks to run independently.
//   xTaskCreatePinnedToCore(
//     TaskBlink
//     ,  "TaskBlink"   // A name just for humans
//     ,  1024  // This stack size can be checked & adjusted by reading the Stack Highwater
//     ,  NULL
//     ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
//     ,  NULL 
//     ,  ARDUINO_RUNNING_CORE);

//   xTaskCreatePinnedToCore(
//     TaskAnalogReadA3
//     ,  "AnalogReadA3"
//     ,  1024  // Stack size
//     ,  NULL
//     ,  1  // Priority
//     ,  NULL 
//     ,  ARDUINO_RUNNING_CORE);

//   // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
// }

// void loop()
// {
//   // Empty. Things are done in Tasks.
// }

// /*--------------------------------------------------*/
// /*---------------------- Tasks ---------------------*/
// /*--------------------------------------------------*/

// void TaskBlink(void *pvParameters)  // This is a task.
// {
//   (void) pvParameters;
//   pinMode(LED_BUILTIN, OUTPUT);

//   for (;;){
//     digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//     vTaskDelay(100);
//     digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//     vTaskDelay(100);
//   }
// }

// void TaskAnalogReadA3(void *pvParameters)  // This is a task.
// {
//   (void) pvParameters;
//   for (;;){
//     int sensorValueA3 = analogRead(A3);
//     Serial.println(sensorValueA3);
//     vTaskDelay(10)
//   }
// }
