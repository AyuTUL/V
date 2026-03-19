clear all;
close all;
clc;

pkg load image;

% Read the image
img = imread('apo.jpg');

% Convert to grayscale if RGB
if size(img,3) == 3
    gray = rgb2gray(img);
else
    gray = img;
end

% Convert to double
gray = im2double(gray);

% Convert to binary image
level = graythresh(gray);
bw = im2bw(gray, level);

% Create structuring element
se = strel('square',3);

% Apply erosion
eroded_img = imerode(bw, se);

% Display images
figure

subplot(1,2,1)
imshow(bw)
title('Original Binary Image')

subplot(1,2,2)
imshow(eroded_img)
title('Eroded Image')