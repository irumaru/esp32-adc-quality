//High quality ADC

#include "Arduino.h"

//ADCサンプリング数
#define ADC_HQ_SAMPLE1 100
//平均との許容誤差
#define ADC_HQ_SWING 20
//ADC2を採用する最低サンプリング数
#define ADC_HQ_SAMPLE2_MIN 50

uint16_t analogReadHighQuality(uint8_t gpio)
{
  //宣言
  int unsigned volatile total1, total2, sample2Count, i;
  uint16_t volatile values[ADC_HQ_SAMPLE1], avg1, avg2;

  //初期化
  total1 = total2 = sample2Count = 0;

  //サンプリング1
  for(i = 0; i < ADC_HQ_SAMPLE1; i ++)
  {
    values[i] = analogRead(gpio);
    total1 += values[i];
  }
  //サンプリング1の平均
  avg1 = total1 / ADC_HQ_SAMPLE1;

  //サンプリング2
  for(i = 0; i < ADC_HQ_SAMPLE1; i ++)
  {
    if((avg1 - (ADC_HQ_SWING / 2) < values[i])&&(values[i] < avg1 + (ADC_HQ_SWING / 2)))
    {
      total2 += values[i];
      sample2Count ++;
    }
  }

  if((total2 != 0)&&(ADC_HQ_SAMPLE2_MIN < sample2Count)){
    //サンプリング2の平均
    avg2 = total2 / sample2Count;
  }else{
    //avg2が使えないとき
    avg2 = avg1;
  }

  return avg2;
}
