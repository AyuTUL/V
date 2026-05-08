clear all;
close all;
clc;
pkg load image;

img = imread("Input/14-hammond.jpg");

if size(img,3) == 3
    grayscaleImage = rgb2gray(img);
else
    grayscaleImage = img;
end

grayscaleImage = im2double(grayscaleImage);

sobel_x = [-1 0 1; -2 0 2; -1 0 1];
sobel_y = [-1 -2 -1; 0 0 0; 1 2 1];

gx = imfilter(grayscaleImage, sobel_x, 'replicate');
gy = imfilter(grayscaleImage, sobel_y, 'replicate');

edge_img = sqrt(gx.^2 + gy.^2);

subplot(1,2,1);
imshow(img);
title("Original Image");

subplot(1,2,2);
imshow(edge_img, []);
title("Edge Detection using Sobel Operator");

imwrite(edge_img, "Output/14-edge-detected-image.jpg");
