const byte LED_PIN = 13;
const byte METER_PIN = A4;

double clockFrequency = 16000000.0; // Clock frequency in Hz

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(METER_PIN, INPUT);
  Serial.begin(9600);
  setBlinkFrequency(0.5);
}

void loop() {
  
  double potValue = map(analogRead(METER_PIN), 0, 1023, 0.0, 1.0);
  double desiredFrequency = map(potValue, 0.0, 1.0, 0.1, 2.0);
  setBlinkFrequency(desiredFrequency);
}

void setBlinkFrequency(double frequency) {
  
  unsigned int compareValue = (unsigned int)(clockFrequency / (2 * frequency));
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1 << WGM12); 
  OCR1A = compareValue;
  TIMSK1 |= (1 << OCIE1A); 
  interrupts();
}

ISR(TIMER1_COMPA_vect) {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN)); 
}
