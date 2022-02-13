#include <SPI.h>
#include "epd2in13_V2.h"
#include "imagedata.h"
#include "epdpaint.h"
Epd epd;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("epd FULL");
  int sum = 104 * 212 / 8;
  unsigned char image[sum];
  int i = 0;
  for (i = 0; i < 104 * 212 / 8; i++) {
    image[i] = 0XFF;
  }
  Paint paint(image, 104, 212);    //width should be the multiple of 8
 // paint.DrawRectangle(50, 50, 20, 20, 0);
  paint.SetRotate(3);
  epd.Init(FULL);
  epd.Clear();
  epd.Init(FULL);
    for (i = 0; i < 104 * 212 / 8; i++) {
    image[i] = 0Xff;
  }
 //   paint.DrawFilledRectangle(0, 0, 212, 120, 0);//这里1     黑方块
    paint.DrawStringAt(0, 0, "123456789asdfghjkl", &Font16, 0);//这里2
    paint.DrawStringAt(0, 16, "Hello MK043aaa", &Font8, 0);
    paint.DrawHorizontalLine(0,24,100,0);
    char s,e;         //图像镜像
    for (int x = 0; x < paint.GetWidth() / 8; x++) {
      for (int y = 0; y < paint.GetHeight()/2; y++) {
        s=image[x+y* paint.GetWidth() / 8];
        e=image[x+(paint.GetHeight()-1-y)* paint.GetWidth() / 8];
        image[x+y* paint.GetWidth() / 8]=e;
        image[x+(paint.GetHeight()-1-y)* paint.GetWidth() / 8]=s;
      }
    }



  epd.Display(paint.GetImage());
  
  for (i = 0; i < 104 * 212 / 8; i++) {
    image[i] = 0X00;
  }
    paint.DrawFilledRectangle(120, 50, 140, 20, 1);//这里1       。。。画红色这里需要留白，给黑色显示，上面保持一致，不然会不显示
    paint.DrawStringAt(0, 0, "123456789asdfghjkl", &Font16, 1);//这里2    。。。画红色这里需要留白，给黑色显示，需要和上面保持一致，不然会不显示
    paint.DrawStringAt(0, 16, "Hello MK043aaa", &Font8, 1);
    paint.DrawHorizontalLine(0,24,100,1);
    paint.DrawVerticalLine(100,24,30,1);
    for (int x = 0; x < paint.GetWidth() / 8; x++) {
      for (int y = 0; y < paint.GetHeight()/2; y++) {
        s=image[x+y* paint.GetWidth() / 8];
        e=image[x+(paint.GetHeight()-1-y)* paint.GetWidth() / 8];
        image[x+y* paint.GetWidth() / 8]=e;
        image[x+(paint.GetHeight()-1-y)* paint.GetWidth() / 8]=s;
      }
    }
  paint.DrawFilledRectangle(50, 60, 20, 30, 1);     ///红方块
 
  epd.Display_red(paint.GetImage());
  
  epd.Display(IMAGE_DATA);

  epd.show();
  
  epd.Sleep();

}

void loop()
{

}
