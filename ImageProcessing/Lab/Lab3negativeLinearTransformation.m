clear all;
close all;
clc;
pkg load image;

img = imread("Input/3gaurav.png");

subplot(2,2,1);
imshow(img);
title("Original Image");

doubleImg = im2double(img);

log1Img   = uint8(1   * log(1 + doubleImg) * 255);
subplot(2,2,2);
imshow(log1Img);
title("Log = 1 Image");

log10Img  = uint8(10  * log(1 + doubleImg) * 255);
subplot(2,2,3);
imshow(log10Img);
title("Log = 10 Image");

log200Img = uint8(200 * log(1 + doubleImg) * 255);
subplot(2,2,4);
imshow(log200Img);
title("Log = 200 Image");

imwrite(log1Img,  "Output/3Logarithmic1Image.png");
imwrite(log10Img, "Output/3Logarithmic10Image.png");
imwrite(log200Img,"Output/3Logarithmic200Image.png");
