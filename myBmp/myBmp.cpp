#include <string.h>
#include <fstream>
#include <iostream>
#include <stdexcept>
//creates a data stucture to hold the color value a pixel. The vars hold 8 bytes that hold the rgb values
struct Pixel {
  unsigned char b,g,r; 
};

/*
 * shortened info for bmpImage class and code line.
 * public
 * bmpIMage constructor :27
 * Render :28 
 * private
 * length :37
 * width :38
 * Header :40
 * ImageData :44
 * MakeHeader() :47
 * fillValue :50
 */ 


class bmpImage {
  public: 
  /* constructor for bmpImage */
  bmpImage(int length,int width, Pixel* Image);//:57
  
  /* This function is to print out a .bmp file. 
   * input: name for file
   * output: rn returning the pointer to the char array but could change to void?*/
  void Render(std::string fileName);//:108
    
  
  private:
    unsigned int length;
    unsigned int width;
// holds the header separate from the picture
  unsigned char* Header;
  
  /* should be a char array that holds the info of the picture*/
    Pixel* ImageData;

  /* derives the header for a bmp file using the length and width of the image*/
    unsigned char* MakeHeader();// :73

  /* function that places a integer into a set of four bytes at a place called atIndex in the array header. */
  void fillValue( int value, int atIndex,unsigned char* header);// :65
};


// end of class 



// start of function declarations
bmpImage::bmpImage(int x,int y, Pixel* a) {

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
  try{
  int padding = (4 - ((3 * width) % 4));
  if(padding == 4){
    padding = 0;
  }
  
  std::ofstream image;
  image.open(fileName);

  for(int i = 0; i <54; i++){
    image<<Header[i];
  }
 
    if(ImageData == NULL){
      throw std::runtime_error(
          "ERROR::ImageData return NULL");
    }

 for(int j = 0;j < length*width;j++){
      image<<ImageData->b;
      image<<ImageData->g;
      image<<ImageData->r;
      if(((j + 1) % width == 0) ){
        for( int k = 0;k < padding; k++){
          image<<'0';
        }
      ImageData++;
      }
    }
  }

  catch (std::exception const& e){
    std::cout<<"Exception "<<e.what()<<std::endl;
  }

}



int main(){
  
  const int width = 300;
  const int height = 400;

  Pixel tester[width][height];
  for(int row = 0; row < width; row++){
    for(int col =0; col < height; col++){
      tester[row][col].b = 0;
      tester[row][col].g = 255;
      tester[row][col].r = 0;
    }
  }
  
  bmpImage myimage(width,height,&tester[0][0]);
  myimage.Render("GreenSquare.bmp");
  return 0;
}
