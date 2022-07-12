//alcohol simple checker
//Arduino 1.8.15 , Board manager M5Stack Arduino M5stick-C 1.0.9
//Waveshare MQ-3 gus Sensor , https://www.waveshare.com/mq-3-gas-sensor.htm

#include <M5StickC.h>
const float Vref = 1.75 ; //ATT -6dB時の最大電圧
int gas_din=26; // M5stick-C IO26 Degital Input ,connect to the Dout terminal
int gas_ain=36; // M5stick-C IO36 Analog Input ,connect to the Aout terminal
int ad_value;
float gas_value;
float gas_value_ave;
float gas_value_sum;
int avenum=10; //平均値取得用の測定回数
float ATT=5.1/1.8;//抵抗分圧
float VTH=2.0;// アルコール検知のスレッシュ電圧 2.0 - 2.5V 位で設定

void setup()
{
  M5.begin();
  pinMode(gas_din,INPUT);
  pinMode(gas_ain,ANALOG);
  analogSetPinAttenuation(gas_ain, ADC_6db);//set GPIO36 ATT -6dB
  Serial.begin(115200);
  M5.Lcd.setRotation(3);
  M5.Lcd.setTextSize(1);
  M5.Lcd.fillScreen(BLACK); 
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(10, 0);
  M5.Lcd.print("Alcohol simple checker");
}
void loop()
{
  gas_value_ave = 0;
  gas_value_sum = 0;
  for (int i=0 ; i<avenum ;i++)
  {
    int ad_value=analogRead(gas_ain);
    gas_value = float(ad_value) * Vref  / 4095.0; // 12bit
    gas_value_sum = gas_value_sum + gas_value;
  }
    gas_value_ave = gas_value_sum / avenum;
    Serial.println("Gas leakage");
    Serial.print("gas_value:");
//    Serial.print(gas_value);
    Serial.print(gas_value_ave);
    Serial.println("V");
    if (gas_value_ave * ATT > VTH) {
    M5.Lcd.setTextColor(RED, BLACK);
    }
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 30);
    M5.Lcd.printf("%.3fV", gas_value_ave * ATT);
    M5.Lcd.setTextColor(WHITE, BLACK);
    delay(500);
}
