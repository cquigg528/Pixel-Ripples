


#include "rr.h"

int main()
{


  PNG im1;
  im1.readFromFile("images/falcon.png");
  
  // pair<int,int> start1(1071,1239);
  // rainbowRipple(im1,start1, "1v1b");//"1r2o3y4g3b2i1v");
  // im1.writeToFile("images/falconrr.png");

  PNG im2;
  im2.readFromFile("images/kev.png");
  pair<int,int> start2(970,1963);
  rainbowRipple(im2,start2,"1r0r1b0b");
  im2.writeToFile("images/kevrr.png");

  // PNG im3;
  // im3.readFromFile("images/blank.png");
  // //cout << im3.width() << " " << im3.height() << endl;
  // pair<int,int> start3(320,200);
  // rainbowRipple(im3,start3,"5r5o5y5g5b5i5v");
  // im3.writeToFile("images/blankrr.png");

  return 0;
}
