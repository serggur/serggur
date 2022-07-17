// Receiver code
HardwareSerial SerialAT(1);

const int RUN_LED =  2; 
int run_led_state = LOW;             // ledState used to set the LED


void setup() {  
    // Initialize the digital pin as an output:
  pinMode(RUN_LED, OUTPUT);
  
  
  Serial.begin(115200);
  SerialAT.begin(9600,SERIAL_8N1,16,17);

  Serial.println("lora E220 receiver start.");
}

void loop() {  
int receivedNumber;

if (SerialAT.available()) {
   // Serial.println(SerialAT.read());

    static char input[8];
    static uint8_t i;
    char c = SerialAT.read ();
    
    if ( c != '\r' && i < 7 ) // assuming "Carriage Return" is chosen as the line ending character
      input[i++] = c;
    else
    {
      input[i] = '\0';
      i = 0; 
      receivedNumber = atoi( input ); // Now the receivedNumber is an integer we can store or 
                                          // use this value to control devices

      Serial.println( receivedNumber );
   
      run_led_state = run_led_state == LOW ? HIGH : LOW;
      digitalWrite(RUN_LED, run_led_state);
    }
}
}
