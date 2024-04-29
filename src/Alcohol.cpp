#include <Alcohol.h>
MQUnifiedsensor MQ3(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);
void Alcohol::mq3Init()
{
  // Set math model to calculate the PPM concentration and the value of constants
  MQ3.setRegressionMethod(0); //_PPM =  a*ratio^b
  // MQ3.setA(4.8387); MQ3.setB(-2.68); // Configure the equation to to calculate Benzene concentration
  MQ3.setA(0.3934);
  MQ3.setB(-1.504); // Configure the equation to calculate Alcohol concentration value
  /*
    Exponential regression:
  Gas    | a      | b
  LPG    | 44771  | -3.245
  CH4    | 2*10^31| 19.01
  CO     | 521853 | -3.821
  Alcohol| 0.3934 | -1.504
  Benzene| 4.8387 | -2.68
  Hexane | 7585.3 | -2.849
  */

  /*****************************  MQ Init ********************************************/
  // Remarks: Configure the pin of arduino as input.
  /************************************************************************************/
  MQ3.init();
  MQ3.serialDebug(true);
  /*
    //If the RL value is different from 10K please assign your RL value with the following method:
    MQ3.setRL(10);
  */
  MQ3.setRL(10);
}
void Alcohol ::mq3Cal()
{
  /*****************************  MQ CAlibration ********************************************/
  // Explanation:
  // In this routine the sensor will measure the resistance of the sensor supposedly before being pre-heated
  // and on clean air (Calibration conditions), setting up R0 value.
  // We recomend executing this routine only on setup in laboratory conditions.
  // This routine does not need to be executed on each restart, you can load your R0 value from eeprom.
  // Acknowledgements: https://jayconsystems.com/blog/understanding-a-gas-sensor
  Serial.print("MQ3 Calibrating please wait.");

  float calcR0 = 0;
  for (int i = 1; i <= 10; i++)
  {
    MQ3.update(); // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ3.calibrate(RatioMQ3CleanAir);
    Serial.print(".");
  }
  MQ3.setR0(calcR0 / 10);
  Serial.println(calcR0 / 10);
  Serial.println(" MQ3 done!.");
  if (isinf(calcR0))
  {
    Serial.println("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply");
    while (1)
      ;
  }
  if (calcR0 == 0)
  {
    Serial.println("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply");
    while (1)
      ;
  }
  /*****************************  MQ CAlibration ********************************************/
}
void Alcohol::print_battery()
{
  int ADC_bat = analogRead(ADC_BATT);
  Serial.print("ADC Battery Voltage : ");
  Serial.println(mapd(ADC_bat, 2029, 2606, 3.27, 4.2));
}
double Alcohol ::mapd(double x, double in_min, double in_max, double out_min, double out_max)
{
  const double run = in_max - in_min;
  if (run == 0)
  {
    log_e("map(): Invalid input range, min == max");
    return -1; // AVR returns -1, SAM returns 0
  }
  const double rise = out_max - out_min;
  const double delta = x - in_min;
  return (delta * rise) / run + out_min;
}
double Alcohol ::readMQ3(bool debug)
{
  MQ3.update();                         // Update data, the arduino will read the voltage from the analog pin
  double alcoholPPM = MQ3.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  if (debug == true)
  {
    MQ3.serialDebug(); // Will print the table on the serial port
  }
  return alcoholPPM;
}

/******************** TickTask *******************/
bool TickTask::Update()
{
  unsigned long currentMillis = millis();
  MillisCount = currentMillis - Millis_t;
  if (MillisCount >= MillisDelay)
  {
    Millis_t = currentMillis;
    return true;
  }
  else
    return false;
}

unsigned long TickTask::getTick()
{
  return MillisCount;
}

TickTask::TickTask(unsigned long milDelay)
{
  MillisDelay = milDelay;
}
