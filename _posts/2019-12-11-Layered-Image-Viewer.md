---
layout: post
title: Layered Image Viewer
use_math: false
draft: true
---

Additional Authors: Jessica Bernard, Gerardo Rodriguez, Suneth Tissera, Melissa Yataco, Matt Niepielko

**Dave:** So what happens when one colleague asks another colleague, "Can you get my data into VR?"

I was talking with Matt Niepielko (Biology, New Jersey Center for Science, Technology, and Mathematics, Kean University) about some of the work we do with our students, and he started showing me data he had from a confocal microscope of stained fruit fly stem cells. In short, he wanted to see if we could bring the data up in VR using the hardware we had without needing the expensive proprietary software he was using.

The data looked like this.

![Raw Fruit Fly Data](/images/blog_2019_12_11/RawFruitFlyData.png)

My plan had been (and still is) to pull in the image data, read off the data values, and build some visualizations using the UVT. But I figured before I did that, how good of an image could we get if we just stripped away the low valued pixels and made them transparent, added some translucency to what was left over, and throw the images stacked on top of each other into a Unity scene.

![Layered Fruit Fly Data](/images/blog_2019_12_11/LayeredFruitFlyData.png)


**Gerardo Rodriguez:** This entire project was a great learning opportunity and it provided me with some level of experience i would of never have received elsewhere. My view of VR gear before this project was that it was mainly used for entertainment purposes such as a personal theater or games. This project however proved otherwise as it showed that Virtual Reality gear can be pretty versatile in terms of what it can do. While you still need a beefed up machine to run VR software, the opportunities it has brought to the scientific field are astonishing. The gear itself is also relatively cheap, obviously not everyone can afford a \$600 headset, but it beats the \$25,000 or so piece of machine or software that a university might opt for. The VR market is also growing, as new iterations of the gear are being released and updated constantly. So much so that we know have much cheaper models that go for less than \$500. 

**Melissa Yataco:** At the start of the project, it was very intimidating to think it was possible for us to actually write a program that would integrate oculus with unity and be able to mark and erase the cells. I struggled along the way due to the fact that I've never worked with oculus before and that I'm not familiar with C sharp too much. Since I wasn’t that familiar with coding I focused more on the appearance of the cells because unity was easier for me to navigate through. Despite my struggles, I was still able to accomplish the goal of the project with the assistance of my classmates, who really helped me along the way and made the class fun. 

**Suneth Tissera:** Before the start of this project, I had very little experience with virtual reality and I was unsure of what I’d be able to help with. But after a few days, we as a team managed to grasp the foundations on how the Oculus Integration toolkit worked with Unity and we were able to use it to help improve the Layered Image Viewer Project that Dr. Joiner was working on.

**Gerardo Rodriguez:** With the use of just the VR headset and unity, we were able to visualize scientific data count stem cells. At the moment it can only visualize a set of images provided to us but hopefully with future updates, it’ll be able to handle any set of given images that can be looked at in a 3D space with the help of UVT. For me the most amazing thing out of all this is the visualization of scientific data in a 3D space. VR takes this to a whole new level because we can implement ways for the end user to interact with this data, such as our project with the ability to erase and set markers for each cell. I can see it now, a future where doctors can slip on a VR headset and view a patient's arteries or something or the visualization of weather in a 3D space. 
This project was my first time using Unity to this extent and it was also my first time with a VR headset and overall it was a wild experience having to use these tools to come up with such a project. It was intimidating at first because I was not well knowledge with unity and only knew a fair bit of the C# language, but as work with the project continued I quickly picked up the essentials needed to feel comfortable working with my team on this project. 

**Melissa Yataco:** Another great result from the semester’s project was Dr. Niepielko’s reaction after it was completed and he was able to test it out. The cell data we used was for our project was from his research that he gave us, as previously he used a different program to be able to count the cells that he no longer had access too. During the process of his testing it, he kept repeating ``it’s so amazing,'' and it was just such a good feeling that the amount of effort we all put into the project paid off. As well as having fun with my classmates, using oculus is so enjoyable as well. Putting on the oculus goggles was definitely a different experience, and if you’ve never had the chance before, you’re missing out. In being able to have this opportunity to work with this equipment, I've realized that I would like to continue working on this project and coming up with more ways to improve it further.  

**Suneth Tissera:** Once Dr. Joiner had build the scene with the cell images stacked together, one of our first goals were to get the hands working in Virtual Reality. We quickly managed to get this working by editing and using prefabs already created by Oculus. 

Once this was done, the idea was to add a laser pointer attached to the hand which would’ve then enabled us to interact with the stacked images. For this purpose, we tried using a toolkit from the asset store called the ``VRTK Toolkit''. But we soon found out that it was causing issues with our project and so we decided to take a different approach since the time spent trying to trace the issue could be used more productively. 

So instead we opted to use a wand (a free asset from the Unity asset store) that can be picked up from the scene by grabbing from the handle (Collider attached to the handle of the wand). With the use of another collider attached to the tip, and a script written by Dr. Joiner, the wand was now also able to interact with the stacked images. We were now able to leave a marker and erase any part of the stacked images with ease. 

Some tips I have regarding Unity is to not be as intimidated as I was. I only had minor experience with unity but with the help of external resources, such as the unity documents, I had enough of an understanding of the software to be of some use in this project. Using Google also helped out a lot as it often solved many of the minor questions and problems we encountered. Don’t be afraid to look things up as well, even if it something small as searching for a specific setting location in unity or searching on how to add a script to a game object. 

After a semester filled with a lot of time spent on figuring out how to do things and how to proceed with certain things, we realized that we had accomplished what we wanted to get done this semester, which was, a working program with a set of layered images where you could navigate through in virtual reality and interact with.

For future modifications, some improvements that I feel would be interesting for anyone to add in would be:
	
1. The ability to call the wand to you by raising a hand, instead of having to grab it.
2. Basic improvements to the background scene to make it look nicer. 
    * Placing the stack of cell images inside a room like space.
    * Adding some lighting in this room.
    * Restricting the movement of the user to only the area of the room.
3. The ability for the user to grab, move and rotate the stack of images as a whole in the X, Y and Z direction so that they could visualize things better.
4. Some performance optimization could also be done so that the program could run smoother on less powerful machines as well.

**Jessica Bernard:** As a whole, this was a great and valuable learning experience. Although I was a bit familiar with how to do this sort of project from my RFI last year, I was still a bit uncertain about taking on a project like this, due to feeling that I did not have enough experience in order to really help. However as we actually started the project it seemed to get easier, and I was able to understand what was needed.

Due to scheduling issues I ended up being separated from the others involved in the project. However even though this was the case Dr. Joiner did help a lot when it came to understanding what the others were up to and the issues that needed help fixing. 

The main aspect that I worked on for the project was working to get the hands to generate the marker that was later used with the wand. The markers, aptly named Trackers in the project, were made in order to mark down any instances of an individual cell that the user saw. They are small spheres that are generated from code placed into each hand. However there were a few issues that arose, which is why I later changed it to just the right hand due to issues mostly having to do with the direction it was being generated in the left hand. Later it was adjusted to work with the wand that was later implemented. 

Some ideas for future features could be:
 * A way to count how many trackers are generated in the scene
 * A way to have the wand just come to your hand and center itself perfectly
 * The ability to scale and rotate the stacked images to make sure to get as many cells as possible(the ones that may overlap or even some that hide underneath)
 * A way to run the program smoother so that it won’t stutter when too many trackers are in the scene at once
 * Possibly make the scene look a bit more pleasing to the user instead of a generic open space
 * Adjust the Tracker for the wand to make it generate from the tip at different angles better
 * Having the wand not fly off into the ether when you let go of it


**Dave:** This is still ongoing, with questions about how to share the data, how we will make the code available, and what will get published where, but we will definitely keep updating this blog on the progress of this project.

Our process essentially consisted of: Use Resources.Load to grab the images as a Texture2D. The images had to be in a resources folder in assets, and had to be marked as editable, in an RGB format, with alpha transparency, all within the editor. The individual pixels were pulled in a C# script with Texture2D.GetPixels, and RGB values below a set threshhold were set to zero, along with the alpha level of the pixel. The texture was attached to a new material on a plane, built from a call to Shader.Find on a transparent two sided diffuse shader. The y position of each plane for each image was set slightly higher to provide depth.

Performance with 47 layered transparent images in close proximity has been better than 60 frames per second on the embedded video on my laptop, and significantly better on our Alienware laptop development rig with an Nvidia Geforce 1070.

![Viewer Poster](/images/blog_2019_12_11/ConfocalData.png)



