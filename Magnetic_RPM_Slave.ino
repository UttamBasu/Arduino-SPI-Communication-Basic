/* Measure the RPM of motor using Magnetic RPM Sensor.
   The Sensor D0 pin connected with the Digital pin 12 of Arduino.
   Sensor + pin connected with 5V power supply.
   Sensor - pin connected with GND pin of Arduino.
   Senosr A0 pin is not connected.
   The live RPM, and speed (KM/h) will be send to the computer using Serial Port.
   This code is made by Uttam Basu on 23rd August 2021.
   https://github.com/UttamBasu
*/
int rpmsensor = 12;
unsigned long start_time = 0;
unsigned long end_time = 0;
int steps = 0;
float steps_old = 0;
float temp = 0;
float rps = 0;
float kmph1 = 0.0;

float spd1 = 0;
String str;

void setup()
{
  Serial.begin(9600);
  pinMode(rpmsensor, INPUT_PULLUP);
  //Serial.println("LABEL,Date,Time,RPM,KM/H");  //Define the Heading of the Column of the data file.
}
void loop()
{
  float spd2 = spd1;  //for call the previous data before update new data.
  start_time = millis();
  end_time = start_time + 1000;
  while (millis() < end_time)
  {
    if (digitalRead(rpmsensor))
    {
      steps = steps + 1;
      while (digitalRead(rpmsensor));
    }
  }
  temp = steps - steps_old;
  steps_old = steps;
  rps = (temp);
  float spd = 3.14 * 0.135 * rps; // speed = 3.14159*(D/100)*(rpm/60) // speed in m/s
  spd1 = ((3.14 * 0.000135 * rps * 60 * 1000 * 2.5) * 0.9285); //RPM use 1 number of reflector connected. 0.9885 value is for calibration thr speed with data logger.
  spd1 = spd1 / 2000;

  //convert the RPM to 8 bit. so maximum 255. I devide the data by 2 get 512 maximum.
  //need to multiply the data on the receiver side by 2 for actual data.


  //Put the condition if any error (neagtive) data come then it will transfer the last previous data. because speed can't be negative value.
  if (spd1 < 0)
  {
    spd1 = spd2;
  }

  //Convert the RPM the Speed (Km/h)
  float kmph1 = (spd1 * 0.1885 * 0.45);   //Here 0.45 is the wheel diameter in meter.
  str = String(spd1);
  Serial.println(str);
  delay(10);  //Wait for 10 Mili second for update again, But data will come after 1 Second.
}
