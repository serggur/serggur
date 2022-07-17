// Transmitter code
HardwareSerial SerialAT(1);

int readVal;

const int RUN_LED =  2; 
int run_led_state = LOW;             // ledState used to set the LED

const int M1 = 13;                   //GPIO13
//const int M0 = 12;                 //GPIO12

void setup() {  
    // Initialize the digital pin as an output:
  pinMode(RUN_LED, OUTPUT);
  pinMode(M1, OUTPUT);

  SerialAT.begin(9600,SERIAL_8N1,16,17);

  digitalWrite(M1, LOW);
}

void loop() {  
  
  readVal = 54;              //value to send
  SerialAT.println(readVal);
  delay(10000);   

    run_led_state = run_led_state == LOW ? HIGH : LOW;
    digitalWrite(RUN_LED, run_led_state);
}
