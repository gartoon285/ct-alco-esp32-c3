#include <Alcohol.h>
MQUnifiedsensor MQ303(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);
void Alcohol::sgp30Init(){
  if (! sgp.begin()){
    Serial.println("Sensor not found :(");
    while (1);
      uint16_t TVOC_base, eCO2_base;
    if (! sgp.getIAQBaseline(&eCO2_base, &TVOC_base)) {
      Serial.println("Failed to get baseline readings");
      return;
    }
  sgp.setIAQBaseline(eCO2_base, TVOC_base);
  }
}
bool Alcohol::sgp30Update(){
  return sgp.IAQmeasure();
}
float Alcohol::sgp30getEthanol(){
        sgp.IAQmeasureRaw();
        int16_t e=sgp.rawEthanol;
        float cref = 0.4;
     float Ethanol= cref * exp((_srefEth - e) * 1.953125e-3);
  return Ethanol;
}
float Alcohol::sgp30getCo2(){
  return sgp.eCO2;
}
void Alcohol::mq303Init()
{
  // Set math model to calculate the PPM concentration and the value of constants
  MQ303.setRegressionMethod(1); //_PPM =  a*ratio^b
  // MQ3.setA(4.8387); MQ3.setB(-2.68); // Configure the equation to to calculate Benzene concentration
  MQ303.setA(0.3934);
  MQ303.setB(-1.504); // Configure the equation to calculate Alcohol concentration value
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
  MQ303.init();
  MQ303.serialDebug(true);
  /*
    //If the RL value is different from 10K please assign your RL value with the following method:
    MQ3.setRL(10);
  */
  MQ303.setRL(10);
}
void Alcohol ::mq303Cal()
{
  /*****************************  MQ CAlibration ********************************************/
  // Explanation:
  // In this routine the sensor will measure the resistance of the sensor supposedly before being pre-heated
  // and on clean air (Calibration conditions), setting up R0 value.
  // We recomend executing this routine only on setup in laboratory conditions.
  // This routine does not need to be executed on each restart, you can load your R0 value from eeprom.
  // Acknowledgements: https://jayconsystems.com/blog/understanding-a-gas-sensor
  Serial.print("MQ303 Calibrating please wait.");

  float calcR0 = 0;
  for (int i = 1; i <= 10; i++)
  {
    MQ303.update(); // Update data, the arduino will read the voltage from the analog pin
    calcR0 += MQ303.calibrate(RatioMQ3CleanAir);
    Serial.print(".");
  }
  MQ303.setR0(calcR0 / 10);
  Serial.println(calcR0 / 10);
  Serial.println(" MQ303 done!.");
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
double Alcohol ::readMQ303(bool debug)
{
  MQ303.update();                         // Update data, the arduino will read the voltage from the analog pin
  double alcoholPPM = MQ303.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  if (debug == true)
  {
    MQ303.serialDebug(); // Will print the table on the serial port
  }
  return alcoholPPM;
}

