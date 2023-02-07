#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 50

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 9

static const CRGB PROGMEM
  mc[][7] = {
    {CRGB::Black,  CRGB::Black,  CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Black,  CRGB::Black},
    {CRGB::Black,  CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Black,  CRGB::Yellow, CRGB::Black},
    {CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow},
    {CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow},
    {CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow},
    {CRGB::Black,  CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Black},
    {CRGB::Black,  CRGB::Black,  CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Black,  CRGB::Black},
  },
  mo1[][7] = {
    {CRGB::Black,  CRGB::Black,  CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Black,  CRGB::Black},
    {CRGB::Black,  CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Black,  CRGB::Yellow, CRGB::Black},
    {CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Black,  CRGB::Black},
    {CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Black,  CRGB::Black,  CRGB::Black},
    {CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Black,  CRGB::Black},
    {CRGB::Black,  CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Black},
    {CRGB::Black,  CRGB::Black,  CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Black,  CRGB::Black},
  },  
  mo2[][7] = {
    {CRGB::Black,  CRGB::Black,  CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Black,  CRGB::Black},
    {CRGB::Black,  CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Black,  CRGB::Black, CRGB::Black},
    {CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Black, CRGB::Black,  CRGB::Black},
    {CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Black, CRGB::Black,  CRGB::Black,  CRGB::Black},
    {CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Black, CRGB::Black,  CRGB::Black},
    {CRGB::Black,  CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Black, CRGB::Black},
    {CRGB::Black,  CRGB::Black,  CRGB::Yellow, CRGB::Yellow, CRGB::Yellow, CRGB::Black,  CRGB::Black},
  },
  ghostc[][7] = {
    {CRGB::Black,  CRGB::Black,  CRGB::Cyan,  CRGB::Cyan,  CRGB::Cyan,  CRGB::Black,  CRGB::Black},
    {CRGB::Black,  CRGB::Cyan,   CRGB::Cyan,  CRGB::Cyan,  CRGB::Cyan,  CRGB::Cyan,   CRGB::Black},
    {CRGB::Black,  CRGB::Cyan,   CRGB::White, CRGB::Cyan,  CRGB::White, CRGB::Cyan,   CRGB::Black},
    {CRGB::Cyan,   CRGB::Cyan,   CRGB::Blue,  CRGB::Cyan,  CRGB::Blue,  CRGB::Cyan,   CRGB::Cyan},
    {CRGB::Cyan,   CRGB::Cyan,   CRGB::Cyan,  CRGB::Cyan,  CRGB::Cyan,  CRGB::Cyan,   CRGB::Cyan},
    {CRGB::Cyan,   CRGB::Cyan,   CRGB::Cyan,  CRGB::Cyan,  CRGB::Cyan,  CRGB::Cyan,   CRGB::Cyan},
    {CRGB::Cyan,   CRGB::Black,  CRGB::Cyan,  CRGB::Black, CRGB::Cyan,  CRGB::Black,  CRGB::Cyan},
    {CRGB::Black,   CRGB::Cyan,  CRGB::Black,  CRGB::Cyan, CRGB::Black,  CRGB::Cyan,  CRGB::Black},
  },
  ghostp[][7] = {
    {CRGB::Black,  CRGB::Black,  CRGB::Pink,  CRGB::Pink, CRGB::Pink, CRGB::Black,  CRGB::Black},
    {CRGB::Black,  CRGB::Pink, CRGB::Pink, CRGB::Pink, CRGB::Pink,  CRGB::Pink, CRGB::Black},
    {CRGB::Black, CRGB::Pink, CRGB::White, CRGB::Pink, CRGB::White, CRGB::Pink,  CRGB::Black},
    {CRGB::Pink, CRGB::Pink, CRGB::Blue, CRGB::Pink, CRGB::Blue,  CRGB::Pink,  CRGB::Pink},
    {CRGB::Pink, CRGB::Pink, CRGB::Pink, CRGB::Pink, CRGB::Pink, CRGB::Pink,  CRGB::Pink},
    {CRGB::Pink,  CRGB::Pink, CRGB::Pink, CRGB::Pink, CRGB::Pink, CRGB::Pink, CRGB::Pink},
    {CRGB::Pink,  CRGB::Black, CRGB::Pink, CRGB::Black, CRGB::Pink, CRGB::Black, CRGB::Pink},
    {CRGB::Black,  CRGB::Pink, CRGB::Black, CRGB::Pink, CRGB::Black, CRGB::Pink, CRGB::Black},      
  },

  ghosto[][7] = {
    {CRGB::Black,  CRGB::Black,  CRGB::Orange,  CRGB::Orange, CRGB::Orange, CRGB::Black,  CRGB::Black},
    {CRGB::Black,  CRGB::Orange, CRGB::Orange, CRGB::Orange, CRGB::Orange,  CRGB::Orange, CRGB::Black},
    {CRGB::Black, CRGB::Orange, CRGB::White, CRGB::Orange, CRGB::White, CRGB::Orange,  CRGB::Black},
    {CRGB::Orange, CRGB::Orange, CRGB::Blue, CRGB::Orange, CRGB::Blue,  CRGB::Orange,  CRGB::Orange},
    {CRGB::Orange, CRGB::Orange, CRGB::Orange, CRGB::Orange, CRGB::Orange, CRGB::Orange,  CRGB::Orange},
    {CRGB::Orange,  CRGB::Orange, CRGB::Orange, CRGB::Orange, CRGB::Orange, CRGB::Orange, CRGB::Orange},
    {CRGB::Orange,  CRGB::Black,  CRGB::Orange, CRGB::Black, CRGB::Orange, CRGB::Black,  CRGB::Orange},
    {CRGB::Black,  CRGB::Orange,  CRGB::Black, CRGB::Orange, CRGB::Black, CRGB::Orange,  CRGB::Black},
  },
  ghostr[][7] = {
    {CRGB::Black,  CRGB::Black,  CRGB::Red,  CRGB::Red, CRGB::Red, CRGB::Black,  CRGB::Black},
    {CRGB::Black,  CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,  CRGB::Red, CRGB::Black},
    {CRGB::Black, CRGB::Red, CRGB::White, CRGB::Red, CRGB::White, CRGB::Red,  CRGB::Black},
    {CRGB::Red, CRGB::Red, CRGB::Blue, CRGB::Red, CRGB::Blue,  CRGB::Red,  CRGB::Red},
    {CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,  CRGB::Red},
    {CRGB::Red,  CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red},
    {CRGB::Red,  CRGB::Black,  CRGB::Red, CRGB::Black, CRGB::Red, CRGB::Black,  CRGB::Red},
    {CRGB::Black,  CRGB::Red,  CRGB::Black, CRGB::Red, CRGB::Black, CRGB::Red,  CRGB::Black},
    }, 
  eye[][7] = {
    {CRGB::Black,  CRGB::Black,  CRGB::Black,  CRGB::Black, CRGB::Black, CRGB::Black,  CRGB::Black},
    {CRGB::Black,  CRGB::White,  CRGB::White,  CRGB::Black, CRGB::White, CRGB::White,  CRGB::Black},
    {CRGB::Black,  CRGB::White,  CRGB::Blue,  CRGB::Black, CRGB::White, CRGB::Blue,  CRGB::Black},
    {CRGB::Black,  CRGB::Black,  CRGB::Black,  CRGB::Black, CRGB::Black, CRGB::Black,  CRGB::Black},
    {CRGB::Black,  CRGB::Black,  CRGB::Black,  CRGB::Black, CRGB::Black, CRGB::Black,  CRGB::Black},
    {CRGB::Black,  CRGB::Black,  CRGB::Black,  CRGB::Black, CRGB::Black, CRGB::Black,  CRGB::Black},
    {CRGB::Black,  CRGB::Black,  CRGB::Black,  CRGB::Black, CRGB::Black, CRGB::Black,  CRGB::Black}
    };


// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {       
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);   
  randomSeed(analogRead(0));  
}


int lastSeq = -1;

void loop() { 

  FastLED.clear();
 
  
  int seq=lastSeq;
  while(seq==lastSeq){
    seq = random(0,6);
  }
  lastSeq=seq;

  Serial.println(seq,DEC);
  
  switch(seq){
    case 0:
      pacmanSequence();
      break;
    case 1:
      ghostCSequence();
      break;
    case 2:
      ghostPSequence();  
      break;
    case 3:         
      ghostOSequence();
      break;
    case 4:
      ghostRSequence();
      break;
    case 5:
      eatSequence();
      break;
  }

}


void eatSequence(){
  for(int x=-7;x<-2;x++){
    drawBitmap(x, 0, mc, 0, 4, 255, false);      
    drawBitmap(-x, 0, ghostc, 4, 8, 255, false);      
    FastLED.show();
    delay(100);
    drawBitmap(x, 0, mo1, 0, 4, 255, false);      
    drawBitmap(-x, 0, ghostc, 4, 8, 255, true);      
    FastLED.show();
    delay(100);
    drawBitmap(x, 0, mo2, 0, 4, 255, false);      
    drawBitmap(-x, 0, ghostc, 4, 8, 255, false);      
    FastLED.show();
    drawBitmap(x, 0, mo1, 0, 4, 255, false);      
    drawBitmap(-x, 0, ghostc, 4, 8, 255, true);      
    FastLED.show();
    delay(100);      
  }
  
  for(int x=-2;x<7;x++){
    drawBitmap(x, 0, mc, 0, 6+x, 255, false);            
    FastLED.show();
    delay(100);
    drawBitmap(x, 0, mo1, 0, 6+x, 255, false);            
    FastLED.show();
    delay(100);
    drawBitmap(x, 0, mo2, 0, 6+x, 255, false);            
    FastLED.show();
    drawBitmap(x, 0, mo1, 0, 6+x, 255, false);              
    FastLED.show();
    delay(100);      
  }

  for(int y=0;y<7;y++){
    drawBitmap(0, y, eye, 0, 8, 255, false);    
    FastLED.show();
    delay(350);
  }

}

void pacmanSequence(){
  for(int x=-7;x<7;x++){
    drawBitmap(x, 0, mc, 0, 8, 255, false);    
    dots(x);
    FastLED.show();
    delay(100);
    drawBitmap(x, 0, mo1, 0, 8, 255, false);    
    dots(x);
    FastLED.show();
    delay(100);
    drawBitmap(x, 0, mo2, 0, 8, 255, false);    
    dots(x);
    FastLED.show();
    delay(100);
    drawBitmap(x, 0, mo1, 0, 8, 255, false);    
    dots(x);
    FastLED.show();
    delay(100);
  }
}

void ghostCSequence(){
  
    
  for(int x=-7;x<7;x++){
    drawBitmap(x, 0, ghostc, 0, 8, 255, false);    
    FastLED.show();
    delay(150);
    drawBitmap(x, 0, ghostc, 0, 8, 255, true);    
    FastLED.show();
    delay(150);    
  }
}

void ghostPSequence(){

  for(int y=-7;y<7;y++){
    drawBitmap(0, y, ghostp, 0, 8, 255, false);    
    FastLED.show();
    delay(150);
    drawBitmap(0, y, ghostp, 0, 8, 255, true);    
    FastLED.show();
    delay(150);
  }
}

void ghostOSequence(){

  for(int x=7;x>-7;x--){
    drawBitmap(x, 0, ghosto, 0, 8, 255, false);    
    FastLED.show();
    delay(150);
    drawBitmap(x, 0, ghosto, 0, 8, 255, true);    
    FastLED.show();
    delay(150);    
  }
}

void ghostRSequence(){

  for(int y=7;y>-7;y--){
    drawBitmap(0, y, ghostr, 0, 8, 255, false);    
    FastLED.show();
    delay(150); 
    drawBitmap(0, y, ghostr, 0, 8, 255, true);    
    FastLED.show();
    delay(150);   
  }
  
  
}

void dots(int x){
  if(x<1){
    leds[19]=CRGB::White;
    leds[21]=CRGB::White;
    leds[22]=CRGB::White;           
    leds[33]=CRGB::White; 
  }
  if(x<0){
    leds[23]=CRGB::White;
  }
}

void drawBitmap(int x, int y, const CRGB bmp[][7], int windowX, int windowW, int brightness, bool swapBottom){   

  //Shift bitmap first

  int ir=0;
  int ic=0;

  CRGB bmpOut[7][7] = {
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0}
  };

 
 
   
 for(int r=y;r<y+7;r++){        
    ic=0;
    for(int c=x;c<x+7;c++){
      if(r>=0 && c>=0 && r<7 && c<7){
        bmpOut[r][c] = bmp[ir][ic];
      }
      ic++;
    }
    ir++;
    if(ir==6 && swapBottom){
      ir=7;
    }
  }    
 

  int ledNum=0;
  for(int r=0;r<7;r++){
    for(int c=0;c<7;c++){      
      if(r % 2){      
        if((6-c)>=windowX && (6-c)<=windowX+windowW){
          leds[ledNum]=bmpOut[r][6-c];
        }
      } else {
        if(c>=windowX && c<=windowX+windowW){
          leds[ledNum]=bmpOut[r][c];
        }
      }
      ledNum++;
    }    
  }  
  FastLED.setBrightness(brightness);

}
