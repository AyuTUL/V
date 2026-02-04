clear all;
close all;
clc;
pkg load image;

img = imread("Input/05squidward.jpg");

bit0 = double(bitget(img,1));
bit1 = double(bitget(img,2));
bit2 = double(bitget(img,3));
bit3 = double(bitget(img,4));
bit4 = double(bitget(img,5));
bit5 = double(bitget(img,6));
bit6 = double(bitget(img,7));
bit7 = double(bitget(img,8));

subplot(3,3,1);
imshow(img);
title("Original Image");

subplot(3,3,2);
imshow(bit0);
title('Bit Plane 0');

subplot(3,3,3);
imshow(bit1);
title('Bit Plane 1');

subplot(3,3,4);
imshow(bit2);
title('Bit Plane 2');

subplot(3,3,5);
imshow(bit3);
title('Bit Plane 3');

subplot(3,3,6);
imshow(bit4);
title('Bit Plane 4');

subplot(3,3,7);
imshow(bit5);
title('Bit Plane 5');

subplot(3,3,8);
imshow(bit6);
title('Bit Plane 6');

subplot(3,3,9);
imshow(bit7);
title('Bit Plane 7');

imwrite(bit0,"Output/05bitPlaneSlicing/0PlaneImage.png");
imwrite(bit1,"Output/05bitPlaneSlicing/1PlaneImage.png");
imwrite(bit2,"Output/05bitPlaneSlicing/2PlaneImage.png");
imwrite(bit3,"Output/05bitPlaneSlicing/3PlaneImage.png");
imwrite(bit4,"Output/05bitPlaneSlicing/4PlaneImage.png");
imwrite(bit5,"Output/05bitPlaneSlicing/5PlaneImage.png");
imwrite(bit6,"Output/05bitPlaneSlicing/6PlaneImage.png");
imwrite(bit7,"Output/05bitPlaneSlicing/7PlaneImage.png");