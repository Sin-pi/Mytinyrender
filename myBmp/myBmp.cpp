#include <string.h>
#include <fstream>
#include <iostream>
//creates a data stucture to hold the color value a pixel. The vars hold 8 bytes that hold the rgb values
struct Pixel {
  unsigned char b,g,r; 
};


class bmpImage {
  public: 
  /* constructor for bmpImage */
  bmpImage(unsigned int length, unsigned int width,Pixel* imageData);//:35
  
  /* This function is to print out a .bmp file. 
   * input: name for file
   * output: rn returning the pointer to the char array but could change to void?*/
  void Render(std::string fileName);//:86
    
  
  private:
    unsigned int length;
    unsigned int width;
// holds the header separate from the picture
  unsigned char* Header;
  
  /* should be a char array that holds the info of the picture*/
    Pixel* ImageData;

  /* derives the header for a bmp file using the length and width of the image*/
    unsigned char* MakeHeader();// :51

  /* function that places a integer into a set of four bytes at a place called atIndex in the array header. */
  void fillValue( int value, int atIndex,unsigned char* header);// :43
};

bmpImage::bmpImage(unsigned int x, unsigned int y, Pixel* a) {
  
  length = x;
  width = y;
  ImageData = a;
  Header = MakeHeader();
  
}
void bmpImage::fillValue( int value, int atIndex,unsigned char* header){
  int shifter = 0xFF000000;
  for(int i = 0;i < 4;i++){
  header[atIndex-i] = (value & shifter) >> ((6-(2*i))*4);
  shifter >> 2;
  }
}

unsigned char* bmpImage::MakeHeader(){
   int bitmapSize = 3 * width * length;
  int fileSize = bitmapSize + 54;
  
  unsigned char temp[54] = {
    0x42, 0x4D, // "BM"
    0, 0, 0, 0, // image size with header
    0x00, 0x00,
    0x00, 0x00,
    0x36, 0x00, 0x00, 0x00,
    0x28, 0x00, 0x00, 0x00,
    0, 0, 0, 0, // width
    0, 0, 0, 0, // height
    0x01, 0x00,
    0x18, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0, 0, 0, 0, // image size excluding header

    0xC4, 0x0E, 0x00, 0x00,
    0xC4, 0x0E, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
  };
  
  fillValue(fileSize,5,temp);
  fillValue(width,21,temp);
  fillValue(length,25,temp);
  fillValue(bitmapSize, 37,temp);

  unsigned char* header = new unsigned char[54];
  memcpy(header,temp,sizeof(temp));

  return header;
}

void bmpImage::Render(std::string fileName){
  
  std::ofstream image;
  image.open(fileName);

  for(int i = 0; i <54; i++){
    image<<Header[i];
  }
  
 for(int j = 0;j < length*width;j++){

  } 

}



int main(){
  Pixel tester[10];
  for(int i = 0;i<10;i++){
    tester[i].b = 0;
    tester[i].g = 0;
    tester[i].r = 0;
  }
  bmpImage myimage(10,10,&tester[0]);
  myimage.Render("Pumplestim.bmp");
  return 0;
}
