unsigned long ontime, offtime, duty;
float freq, period;
#define tach_in 7
#define tach_out 3
int tach_out_min;

//pin 3 outputs voltage to the tachometer.  
//pin 7 input measure the ECU tachometer signal

void setup() {
  pinMode(tach_in, INPUT_PULLUP);
  pinMode(tach_out, OUTPUT);
  Serial.begin(9600);
  tach_out_min = 20;

  analogWrite(tach_out, 255);
  delay(1000);
  analogWrite(tach_out, tach_out_min);
  
}

void loop() {
  ontime = pulseIn(tach_in, HIGH);
  offtime = pulseIn(tach_in, LOW);
  period = ontime + offtime;
  freq = 1000000.0 / period;
  //duty = (ontime / period) * 100;

  Serial.println("");
  Serial.print("Freq = ");
  Serial.println(freq);

  //freq/1.17 was found to be the right callibration between input from the ECU and display
  //on the tachometer.  100Hz = 3000RPM
  analogWrite(tach_out, constrain(freq/1.17,0,255));
  if(freq > 250){
    analogWrite(tach_out, tach_out_min);
  }

}
