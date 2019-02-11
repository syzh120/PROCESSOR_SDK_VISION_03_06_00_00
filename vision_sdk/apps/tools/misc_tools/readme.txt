- Use "gmake all" for building image_convert and bin2c tools in resp. directory.
- gmake from TI XDC tools is recommended (d:/ti/xdctools_x_xx_xx_xx/gmake).
- Codeblocks 13.12 was used for build. build issues are seen on 16.01
- Install ImageMagick-6.4.3-1-Q16-windows-static.exe for "convert" utility

1. Usage
----------
Sample example to convert .png file to C array.

convert image.png image.rgb
image_convert -i image.rgb rgb888i 220 75 220 -o image.rgb565 rgb565 220
bin2c image.rgb565 > image_white.h

"220" is the image width in pixels
"75" is the height in pixels
The third parameter is the line offset, which is usually but not always the same like the width.


Parameters "220 75 220" of image_convert have to be adjusted to the geometry of the image.




