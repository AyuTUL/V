clear all;
close all;
clc;
pkg load image;

img = imread("Input/4spongebob.png");

subplot(2,2,1);
imshow(img);
title("Original Image");

doubleImg = im2double(img);

a1 = input("Enter value of a : ");
gamma1 = input("Enter gamma value : ");
gamma1Img = uint8(a1*(doubleImg.^gamma1)*256);
subplot(2,2,2);
imshow(gamma1Img);
title(["Gamma = ", num2str(gamma1)]);

a2 = input("Enter value of a : ");
gamma2 = input("Enter gamma value : ");
gamma2Img = uint8(a2*(doubleImg.^gamma2)*256);
subplot(2,2,3);
imshow(gamma2Img);
title(["Gamma = ", num2str(gamma2)]);

a3 = input("Enter value of a : ");
gamma3 = input("Enter gamma value : ");
gamma3Img = uint8(a3*(doubleImg.^gamma3)*256);
subplot(2,2,4);
imshow(gamma3Img);
title(["Gamma = ", num2str(gamma3)]);

imwrite(gamma1Img,"Output/4gammaTransformation/1gammaImage.png");
imwrite(gamma2Img,"Output/4gammaTransformation/2gammaImage.png");
imwrite(gamma3Img,"Output/4gammaTransformation/3gammaImage.png");
