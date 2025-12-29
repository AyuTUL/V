clear all;
close all;
clc;
#import image package
pkg load image;
#read image
img=imread("F:/AyushTuladharCSITV/IP/Photos/2mrIncredible.png");
subplot(1,3,1);
imshow(img);
title("Original Image");
#convert image into gray
grayscaleImg=rgb2gray(img);
#show grayscale image
subplot(1,3,2);
imshow(grayscaleImg);
title("Grayscale Image");
imwrite(grayscaleImg,"Grayscale.png");
#calculate negative of image
output=255-grayscaleImg;
#show output image
subplot(1,3,3);
imshow(uint8(output));
title("Negative Image");
imwrite(unit*(output),"Negative Image");