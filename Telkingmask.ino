#include <SoftwareSerial.h>

#include <Arduino.h>
#include <U8g2lib.h>



#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
 String c[3];

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

SoftwareSerial BT(2,3);


void setup(void) {
  u8g2.begin();
  u8g2.enableUTF8Print();    // enable UTF8 support for the Arduino print() function
  BT.begin(9600);
  Serial.begin(9600);
  c[0] = "";
  c[1] = "";
  c[2] = "";

}
int qwe = 0;
int asdfghjkl = 50;
int asdf = 1;
int hjkl = 15;
int num = 0;
int a1;
int a2;
int a3;
int a;
int iline = 0;
//char lines[3][18];

void loop(void) {
  u8g2.setFont(u8g2_font_unifont_t_korean1);  
  u8g2.setFontDirection(0);
  u8g2.firstPage();
  
  if(BT.available())
  {
    a = BT.read();
    if(a < 128)
      goto print_screen;
    
    if(num == 0)
    {
      a1 = a;
      Serial.println(a1);
      num++;
    } 
    else if(num == 1)
    {
      a2 = a;  
      Serial.println(a2);
      num++;
    } 
    else if(num == 2)
    {
      num = 0;
      a3 = a;  
      Serial.println(a3);
      c[iline] += utf8tokor(six(a1, a2, a3));
      qwe++;
      if(qwe == 6)
      {
        qwe = 0;
        iline++;
        if(iline == 3)
        {
          iline = 0;
        }
        c[iline] = "";
      }
      Serial.print(iline);
      Serial.println(c[0]);
      Serial.println(c[1]);
      Serial.println(c[2]);
    }
    
  }
  print_screen:
  do
  {
      u8g2.setCursor(0, 15);
      u8g2.print(c[0]);
      u8g2.setCursor(0, 31);
      u8g2.print(c[1]);
      u8g2.setCursor(0, 47);
      u8g2.print(c[2]);
      //delay(200);
  } while (u8g2.nextPage());
  
}


String utf8tokor(String utf8){
  String outputdata = "";
  int tmp = 0;
  int ttmp = 0;
  char utf8data;
  
  tmp = utf8.indexOf('%',tmp);//처음 %찾기
 
  while(tmp > -1){//%가 없으면
    String temp = utf8;
    utf8data = utf8c(temp.substring(tmp+1,tmp+3));
    temp = utf8;
      if(ttmp != tmp){//다음 단어의 시작 %가 이번 단어의 끝과 같지 않을땐 사이에 일반 값이 있으므로
         outputdata += temp.substring(ttmp,tmp);//%--%--%--와%--%--%-- 사이의 값을 잘라내어 저장
      }
    ttmp = tmp+3;
    tmp = utf8.indexOf('%',tmp+3);
    outputdata += utf8data;
    }
    
    outputdata += utf8.substring(ttmp,utf8.length());//맨뒤 남은것 저장
    
    return outputdata;
  }
  
  int utf8c(String utf8data){
  int returndata = 0;
  int i=0;
  for(i=0;i<=1;i++){
    if((utf8data[i] > 47) && (utf8data[i] < 58)){ //0~9
      returndata += (((int)utf8data[i]-48) * (int)(pow(16,(1-i))+0.1));
      }
    if((utf8data[i] > 64) && (utf8data[i] < 71)){ //A~F
      returndata += (((int)utf8data[i]-55) * (int)(pow(16,(1-i))+0.1));
      }
    }
    return returndata;
  }

String six(int dec, int dec2, int dec3){

    int i, k=0, m, n;
    char c_hex[] = "0123456789ABCDEF";
    char hex[6] = { 0 };
    char six[10]= "%";
    while(1){
        m = dec / 16;            // 16으로 나눈 몫
        n = dec - (m * 16);   // 나머지
        hex[k++] = c_hex[n];
        if(m<=0) break;
        dec = m;

   }
   while(1){
        m = dec2 / 16;            // 16으로 나눈 몫
        n = dec2 - (m * 16);   // 나머지
        hex[k++] = c_hex[n];
        if(m<=0) break;
        dec2 = m;

   }
   while(1){
        m = dec3 / 16;            // 16으로 나눈 몫
        n = dec3 - (m * 16);   // 나머지
        hex[k++] = c_hex[n];
        if(m<=0) break;
        dec3 = m;

   }
    int j = 1;
    for(i=1; i>=0; i--){
        if(j == 3 || j == 6){
            six[j] = '%';
            j++;
        }
        six[j] = hex[i];
        j++;
    }
    for(i=3; i>=2; i--){
        if(j == 3 || j == 6){
            six[j] = '%';
            j++;
        }
        six[j] = hex[i];
        j++;
    }
    for(i=5; i>=4; i--){
        if(j == 3 || j == 6){
            six[j] = '%';
            j++;
        }
        six[j] = hex[i];
        j++;
    }
    
 //   Serial.println(six);
    return six;

} 
