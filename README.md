# SVD_Compression
I've been looking into Singular Value Decomposition (SVD), what it is, why it works, how it works, and finally, why it's useful. This tutorial goes over some of the former - I'm not a good mathematics lecturer, so my explanation won't be great but I'll try to give helpful links - and the code gives an example of the latter. Specifically, this is how SVD can be used to compress an image from a raw format, like bitmap, to something using far fewer values, whether lossy or not. I'll also explain why this is not a commonly used image compression algorithm, and why ones like JPG are far superior.


### Theory and walkthrough
For the [theory behind SVD](https://github.com/dmckinnon/SVD_Compression/wiki/SVD-Theory), and a [walkthrough of my code](https://github.com/dmckinnon/SVD_Compression/wiki/Image-compression), see the [wiki](https://github.com/dmckinnon/SVD_Compression/wiki). 

### How to build and run
I've included the Visual Studio project along with my code, and the OpenCV dlls. I use these, and the Eigen library. When you have the appropriate libs linked, and headers in the rights paths, then this should just build in visual studio. Outside of that, linking and including is on you. I advice compiling with -O3, since SVD is an intensive algorithm on something as large as an image.

The instructions for how to run the exe are in main - try running it with -h first. 
