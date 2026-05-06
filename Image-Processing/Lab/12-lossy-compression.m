clear all;
close all;
clc;
pkg load image;

img = imread("Input/12amorim.jpg");

imwrite(img, "Output/12compressedImage.jpg", "Quality", 25);

original = dir("Input/12amorim.jpg");
compressed = dir("Output/12compressedImage.jpg");

disp('Original Image Size:');
disp(original.bytes);

disp('Compressed Image Size:');
disp(compressed.bytes);

subplot(1,2,1);
imshow(img);
title("Original Image");

subplot(1,2,2);
imshow(imread("Output/12compressedImage.jpg"));
title("Compressed Image");
