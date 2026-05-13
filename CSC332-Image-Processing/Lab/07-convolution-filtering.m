clear all;
close all;
clc;
pkg load image;

img = imread("Input/07-goku.jpg");

img=img(:,:,1);
subplot(1,3,1);
imshow(img);
title("Original Image");

highPassMask=[0 -1  0;
             -1  5 -1;
              0 -1  0];
  
sharpenedImg=uint8(conv2(highPassMask,img));
subplot(1,3,2);
imshow(sharpenedImg);
title("High Pass Filtered Image");

lowPassMask=[1 1 1; 
             1 1 1;
             1 1 1]/9;
  
smoothedImg=uint8(conv2(lowPassMask,img));
subplot(1,3,3);
imshow(smoothedImg);
title("Low Pass Filtered Image");

imwrite(sharpenedImg,"Output/07-convolution-filtering/1-high-pass-filtered-image.jpg");
imwrite(smoothedImg,"Output/07-convolution-filtering/2-low-pass-filtered-image.jpg");
