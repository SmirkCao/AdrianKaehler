# Learning OpenCV 3

![img](https://img.shields.io/docker/cloud/build/smirk/opencv.svg)

[TOC]

## 前言

首先鼓励看英文版的，本笔记所有涉及到的页码，都是英文原版对应的页码。然后说下中译本的梗。

中文版的有个《学习OpenCV》，还有个这本对应的中文版《学习OpenCV3》，英文是同样的作者，中文版翻译是两个团队。

不多说了。

《学习OpenCV3》书中包含的代码，是从老版本的书中转移过来的，并且，没做复核应该是，很多代码用不了，很多代码的注释部分还用到了老版本的章节描述。

1999年，OpenCV项目启动，转眼20年。OpenCV的作者Bradski也是本书的作者之一。

### 建议阅读顺序

没什么建议，可以从第十章开始，遇到不懂的往前翻。首先还是要有编程的环境，下面的内容可供参考，环境搭好，能跑helloword，就可以继续了。

另外，这本书内容很多，但是书中给的例子很少，大部分内容在后面的练习中覆盖。看练习任务需求，翻前面的正文找解决方案，然后再读理论这个顺序也不错。

这本书参考文献给了14页

### 环境

关于环境，其实Gray提供了Dockerfile，试了下，貌似是不好用，所以自己整理了一个

```bash
# Dockerfile在项目跟目录，在项目根目录执行以下命令
# 转发X11数据
xhost +
# 创建目录
mkdir docker
cp Dockerfile docker/.
cd docker && sudo docker build -t smirk/opencv .

# 运行镜像
cd .. && sudo docker run -it -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=unix$DISPLAY \
   -v `pwd`:/home/smirk smirk/opencv:latest
```

### 目录结构

```bash
AdrianKaehler
├── CH01
│   └── README.md
├── CPP
│   ├── build
│   ├── clean.sh
│   ├── CMakeLists.txt
│   └── helloword.cpp
├── Dockerfile
├── Python
└── README.md
```

### 语言

原书副标题`Computer Vision in C++ with the OpenCV Library`，这个项目做的时候应该会加上Python的版本。

做CV，SLAM，早晚要用C++，上手的话，Python还是小白一点。各位在积累和时间之间做个权衡，各自坚持吧。

原书配了[Repo](https://github.com/oreillymedia/Learning-OpenCV-3_examples)

## CH01 Overview

## CH02 Introduction to OpenCV

### exa0201

显示一张图

### exa0202

使用namespace形式的代码显示，并且，说明了这个不推荐。

### exa0203

播放视频

### exa0204

trackbar slider

### exa0205

平滑一张图

### exa0206

图像金字塔

### exa0207

Canny边缘检测

### exa0208

## CH10 Filters and Convolution

前面的章节是了解OpenCV的结构等基础的内容，这章节开始有些高级操作。前面把图像当作数组，但是图像的单元之间又是有联系的，每一个小区域的像素之间有着一定的规律，比如不会突变，色彩的变化通常也不会非常明显，如果这个小区域是一个指定的物体，那么他们的数据表现甚至会有一定的规律，所以，现在开始把图像当作图像，这样可以利用更多的图像相关的信息。

## CH16 Keypoints and Descriptor

这一章有一个例子，讲LK光流的。如果想扩展，可以看下十四讲里面视觉里程计，光流的部分。可以使用TUM的数据集进行实践。
链接如下：

https://vision.in.tum.de/data/datasets/rgbd-dataset/download

## CH17 Tracking

这两章在《Learning OpenCV》的时候是一章的内容，篇幅不小，实际上也有很重要的应用。算是距离场景比较近的两大块。