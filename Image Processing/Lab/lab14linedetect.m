clear all;
close all;
clc;

pkg load image;

% Read image
img = imread('apo.jpg');

% Convert to grayscale if RGB
if size(img,3) == 3
    gray = rgb2gray(img);
else
    gray = img;
end

gray = im2double(gray);

% Horizontal line mask
h_mask = [-1 -1 -1;
           2  2  2;
          -1 -1 -1];

% Vertical line mask
v_mask = [-1 2 -1;
          -1 2 -1;
          -1 2 -1];

% Diagonal line mask
d_mask = [2 -1 -1;
         -1 2 -1;
         -1 -1 2];

% Apply filters
h_lines = imfilter(gray, h_mask);
v_lines = imfilter(gray, v_mask);
d_lines = imfilter(gray, d_mask);

% Display results
figure

subplot(2,2,1)
imshow(gray)
title('Original Image')

subplot(2,2,2)
imshow(h_lines)
title('Horizontal Lines')

subplot(2,2,3)
imshow(v_lines)
title('Vertical Lines')

subplot(2,2,4)
imshow(d_lines)
title('Diagonal Lines')