---
layout: post
title: Layered Image Viewer
use_math: true
draft: true
---

Additional Authors: Jessica Bernard, Gerardo Rodriguez, Suneth Tissera, Melissa Yataco, Matt Niepielko

Example text follows below.

So what happens when one colleague asks another colleague, "Can you get my data into VR?"

I was talking with Matt Niepielko (Biology, New Jersey Center for Science, Technology, and Mathematics, Kean University) about some of the work we do with our students, and he started showing me data he had from a confocal microscope of stained fruit fly stem cells. In short, he wanted to see if we could bring the data up in VR using the hardware we had without needing the expensive proprietary software he was using.

The data looked like this.

![Raw Fruit Fly Data](/images/blog_2019_12_11/RawFruitFlyData.png)

My plan had been (and still is) to pull in the image data, read off the data values, and build some visualziations using the UVT. But I figured before I did that, how good of an image could we get if we just stripped away the low valued pixels and made them transparent,  added some translucency to what was left over, and throw the images stacked on top of each other into a Unity scene.

![Layered Fruit Fly Data](/images/blog_2019_12_11/LayeredFruitFlyData.png)

This is still ongoing, with questions about how to share the data, how we will make the code available, and what will get published where, but we will definitely keep updating this blog on the progress of this project.

Our process essentially consisted of: Use Resources.Load to grab the images as a Texture2D. The images had to be in a resources folder in assets, and had to be marked as editable, in an RGB format, with alpha transparency, all within the editor. The individual pixels were pulled in a C# script with Texture2D.GetPixels, and RGB values below a set threshhold were set to zero, along with the alpha level of the pixel. The texture was attached to a new material on a plane, built from a call to Shader.Find on a transparent two sided diffuse shader. The y position of each plane for each image was set slightly higer to provide depth.

Performance with 47 layered transparent images in close proximity has been better than 60 frames per second on the embedded video on my laptop, and significantly better on our Alienware laptop development rig with an Nvidia Geforce 1070.


