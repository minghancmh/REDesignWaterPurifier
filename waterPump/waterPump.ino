// GPIO Interfacing
#define BACKWASH_BUTTON 25 
#define solenoid_1_NO 16
#define solenoid_2_NO 17
#define solenoid_3_NC 18
#define pump_main_NC 21
#define pump_backwash_NO 22

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
  pinMode(BACKWASH_BUTTON, INPUT_PULLUP);
  pinMode(solenoid_1_NO, OUTPUT);
  pinMode(solenoid_2_NO, OUTPUT);
  pinMode(solenoid_3_NC, OUTPUT);
  pinMode(pump_main_NC, OUTPUT);
  pinMode(pump_backwash_NO, OUTPUT);

  // set all pumps to off state (NC/NO logic handled by relay)
  offMainpump();
  offBackwashpump();

  // open all solenoid valves (NC/NO logic handled by relay)
  openSolenoidValve1();
  openSolenoidValve2();
  openSolenoidValve3();

  Serial.println("Purification Starting in 5 seconds");
  delay(5000);
  
}

// *********************  LOOP ***************************//

void loop() {
  // put your main code here, to run repeatedly:
  normalPurification(); // initialise normal purification


  // press button to initiate backwash
  currentState = digitalRead(BACKWASH_BUTTON);
  if (currentState!= lastFlickerableState){
    lastDebounceTime=millis();
    lastFlickerableState=currentState;
  }

  if ((millis()-lastDebounceTime) > DEBOUNCE_TIME) {
    if (lastSteadyState==HIGH && currentState == LOW){
      Serial.println("Backwash button press");
      backwash();

    }
    else if (lastSteadyState==LOW && currentState==HIGH){
      Serial.println("Backwash button release");
    }
    lastSteadyState = currentState;
  }

}


// *********************  HELPER FUNCTIONS  *********************//


void backwash(){
  // insert code to do backwash here
  Serial.println("Backwashing...")
  Serial.println("120 seconds")
  offMainPump();
  closeSolenoidValve1();
  closeSolenoidValve2();
  openSolenoidValve3();
  onBackwashPump();
  delay(120000);
}

void normalPurification(){
  Serial.println("Normal Purification");
  openSolenoidValve1();
  openSolenoidValve2();
  closeSolenoidValve3();
  onMainPump();
  offBackwashPump();
}

void openSolenoidValve1(){
  digitalWrite(solenoid_1_NO, LOW);
}


void closeSolenoidValve1(){
  digitalWrite(solenoid_1_NO, HIGH);
}

void openSolenoidValve2(){
  digitalWrite(solenoid_2_NO, LOW);
}


void closeSolenoidValve2(){
  digitalWrite(solenoid_2_NO, HIGH);
}

void openSolenoidValve3(){
  digitalWrite(solenoid_3_NC, HIGH);
}


void closeSolenoidValve3(){
  digitalWrite(solenoid_3_NC, LOW);
}

void onMainPump(){
  digitalWrite(pump_main_NC, LOW);
}

void offMainPump(){
  digitalWrite(pump_main_NC, HIGH);
}

void onBackwashPump(){
  digitalWrite(pump_backwash_NO, HIGH);
}

void offBackwashPump(){
  digitalWrite(pump_backwash_NO, LOW);
}
