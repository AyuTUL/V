clear all;
close all;
clc;
pkg load image;

img = imread("Input/3peterParker.jpg");

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

imwrite(log1Img,  "Output/3logarithmicTransformation/Log1Image.jpg");
imwrite(log10Img, "Output/3logarithmicTransformation/Log10Image.jpg");
imwrite(log200Img,"Output/3logarithmicTransformation/Log200Image.jpg");
