// GPIO Interfacing
#define BUTTON_PIN 25 
#define solenoid_1_NO = 16
#define solenoid_2_NO = 17
#define solenoid_3_NC = 18
#define pump_main_NC = 21
#define pump_backwash_NO = 22

// CONST VARS
#define DEBOUNCE_TIME 50


// button configuration, debounce enable
int lastSteadyState = LOW;
int lastFlickerableState=LOW;
int currentState;
unsigned long lastDebounceTime=0;




// *********************  SET UP  ***************************//

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);


  

}

// *********************  LOOP ***************************//

void loop() {
  // put your main code here, to run repeatedly:
  currentState = digitalRead(BUTTON_PIN);
  if (currentState!= lastFlickerableState){
    lastDebounceTime=millis();
    lastFlickerableState=currentState;
  }

  if ((millis()-lastDebounceTime) > DEBOUNCE_TIME) {
    if (lastSteadyState==HIGH && currentState == LOW){
      Serial.println("Button Press");
      backwash();

    }
    else if (lastSteadyState==LOW && currentState==HIGH){
      Serial.println("Button release");
    }
    lastSteadyState = currentState;
  }

}


// *********************  HELPER FUNCTIONS  *********************//


void backwash(){
  // insert code to do backwash here
}
