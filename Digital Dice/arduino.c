#define Pin_a 7  //        
#define Pin_b 8  //      
#define Pin_c 2  //     
#define Pin_d 3  //  
#define Pin_e 4  //     
#define Pin_f 6  //   
#define Pin_g 5  //       

// Pin configuration
#define PIN_BUTTON_P1 A0
#define PIN_BUTTON_P2 A1
#define PIN_BUZZER 10
#define PIN_LED 12

const byte PIN_CHAOS = A5; // Unconnected analog pin used to initialize RNG

// Other configuration
const unsigned int BEEP_FREQUENCY = 3000;

int On = 0; //<On=0; for Common anode><On=1; for Common cathode>
int Off = 1;

void setup() {
  randomSeed(analogRead(PIN_CHAOS));
  Serial.begin(9600);  // Initialize serial communication at 9600 baud

  pinMode(Pin_a, OUTPUT);
  pinMode(Pin_b, OUTPUT);
  pinMode(Pin_c, OUTPUT);
  pinMode(Pin_d, OUTPUT);
  pinMode(Pin_e, OUTPUT); 
  pinMode(Pin_f, OUTPUT);
  pinMode(Pin_g, OUTPUT);
  
  pinMode(PIN_BUTTON_P1, INPUT_PULLUP);    // On button pin as input with pullup
  pinMode(PIN_BUTTON_P2, INPUT_PULLUP); 
  pinMode(PIN_BUZZER, OUTPUT);      // On buzzer pin as output

  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW); 
 
  // Indicate that system is ready
  for (int i = 9; i >= 0; i--) {
    showNumber(i);
    tone(PIN_BUZZER, BEEP_FREQUENCY, 100);
    delay(300); 
  }  
  tone(PIN_BUZZER, BEEP_FREQUENCY, 250);  // Beep when done
  delay(1000);              // Wait for 1 second

  Serial.println("System ready");
}

void loop() {
  // Wait for button to be pressed, then run the test routine
  if (digitalRead(PIN_BUTTON_P1) == LOW) {
    Serial.println("Player 1 rolling...");
    rollTheDice(6, 150);
    tone(PIN_BUZZER, BEEP_FREQUENCY, 300);
    delay(300); // debounce
  }

  if (digitalRead(PIN_BUTTON_P2) == LOW) {
    Serial.println("Player 2 rolling...");
    rollTheDice(6, 150);
    tone(PIN_BUZZER, BEEP_FREQUENCY, 300);
    delay(300); // debounce
  }
}

int rollOnce() {
  return random(1, 7);
}

void rollTheDice(int count, int delayLength) {
  for (int i = 0; i < count; i++) {
    int number = random(1,  7);      // Get random number from 1 to 6
    Serial.print("Rolling: ");
    Serial.println(number);
    tone(PIN_BUZZER, BEEP_FREQUENCY, 5);  // Beep very shortly ("click")
    showNumber(number);           // Show the number
    delay(delayLength);           // Wait
  }
}

void showNumber(int x) {
  if (Off == 0) {
    On = 1;
  } else {
    On = 0;
  }

  Serial.print("Showing number: ");
  Serial.println(x);

  switch (x) {
    case 1: one();   break;
    case 2: two();   break;
    case 3: three(); break;
    case 4: four();  break;
    case 5: five();  break;
    case 6: six();   break;
    // 
  }

  if(x == 6) {
    digitalWrite(PIN_LED, HIGH);  // turn LED ON
  } else {
    digitalWrite(PIN_LED, LOW);   // turn LED OFF
  }
}

void one() {
  digitalWrite(Pin_a, Off); //      
  digitalWrite(Pin_b, On);  //      |
  digitalWrite(Pin_c, On);  //      |
  digitalWrite(Pin_d, Off); //      |
  digitalWrite(Pin_e, Off); //      |
  digitalWrite(Pin_f, Off);
  digitalWrite(Pin_g, Off);
}

void two() {
  digitalWrite(Pin_a, On);  //  ____
  digitalWrite(Pin_b, On);  //      | 
  digitalWrite(Pin_c, Off); //  ____|
  digitalWrite(Pin_d, On);  // |     
  digitalWrite(Pin_e, On);  // |____
  digitalWrite(Pin_f, Off);
  digitalWrite(Pin_g, On);
}

void three() {
  digitalWrite(Pin_a, On);  //  ____
  digitalWrite(Pin_b, On);  //      |
  digitalWrite(Pin_c, On);  //  ____|
  digitalWrite(Pin_d, On);  //      |
  digitalWrite(Pin_e, Off); //  ____|
  digitalWrite(Pin_f, Off); 
  digitalWrite(Pin_g, On);
}

void four() {
  digitalWrite(Pin_a, Off); //  
  digitalWrite(Pin_b, On);  // |    |
  digitalWrite(Pin_c, On);  // |____|
  digitalWrite(Pin_d, Off); //      |
  digitalWrite(Pin_e, Off); //      |
  digitalWrite(Pin_f, On);
  digitalWrite(Pin_g, On);
}

void five() {
  digitalWrite(Pin_a, On);  //  ____
  digitalWrite(Pin_b, Off); // |
  digitalWrite(Pin_c, On);  // |____
  digitalWrite(Pin_d, On);  //      |
  digitalWrite(Pin_e, Off); //  ____|
  digitalWrite(Pin_f, On);  
  digitalWrite(Pin_g, On);
}

void six() {
  digitalWrite(Pin_a, On);  //  ____
  digitalWrite(Pin_b, Off); // |
  digitalWrite(Pin_c, On);  // |____
  digitalWrite(Pin_d, On);  // |    |
  digitalWrite(Pin_e, On);  // |____|
  digitalWrite(Pin_f, On);
  digitalWrite(Pin_g, On);
}

// void seven() {
//   digitalWrite(Pin_a, On);  //  ____
//   digitalWrite(Pin_b, On);  //      |
//   digitalWrite(Pin_c, On);  //      |
//   digitalWrite(Pin_d, Off); //      |
//   digitalWrite(Pin_e, Off); //      |
//   digitalWrite(Pin_f, Off);
//   digitalWrite(Pin_g, Off);
// }

// void eight() {
//   digitalWrite(Pin_a, On); //  ____
//   digitalWrite(Pin_b, On); // |    |
//   digitalWrite(Pin_c, On); // |____|
//   digitalWrite(Pin_d, On); // |    |
//   digitalWrite(Pin_e, On); // |____|
//   digitalWrite(Pin_f, On); 
//   digitalWrite(Pin_g, On); 
// }

// void nine() {
//   digitalWrite(Pin_a, On);  //  ____
//   digitalWrite(Pin_b, On);  // |    |
//   digitalWrite(Pin_c, On);  // |____|
//   digitalWrite(Pin_d, On);  //      |
//   digitalWrite(Pin_e, Off); //  ____|
//   digitalWrite(Pin_f, On); 
//   digitalWrite(Pin_g, On);
// }

// void zero() {                 
//   digitalWrite(Pin_a, On); //  ____
//   digitalWrite(Pin_b, On); // |    |
//   digitalWrite(Pin_c, On); // |    |
//   digitalWrite(Pin_d, On); // |    |
//   digitalWrite(Pin_e, On); // |____|
//   digitalWrite(Pin_f, On); 
//   digitalWrite(Pin_g, Off);   
// }
