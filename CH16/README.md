# CH16 Keypoints and Descriptors

## 导读

这一章和接下来的一章，非常重要。理解Keypoints和Descriptors，先介绍了整体的框架以及OpenCV中的接口，
然后介绍了OpenCV中具体的特征检测器，关键点过滤方法以及匹配方法。

最常见的角点就是Harris Corners。

- 这章的内容很重要，在SLAM里面应该有很多应用。
- 亚像素角点
- LK算法最开始是为了做稠密光流，但是后来成了稀疏光流的重要方法
- 凡是涉及导数的地方基本都用到了rule chain，应该算是数学基础了。不懂没关系，记住场景，要做到没吃过猪肉，但是见过猪跑。
- 亮度恒定和灰度不变，差不多。
- 理解Keypoints和Descriptors的作用，这部分在前面一个版本没有说。
- 书中列举了这章主要的三个任务：追踪，检测和三维重建。
- 这章介绍到特征匹配这里，对于特征测试没有介绍，后面可能会补一个图像检索的例子。

## 内容

LK光流基于三个假设：

1. 亮度恒定；
2. 时间连续或者小运动；
3. 空间一致。

通常Brightness Constancy这种假设都是通过打光技巧实现的。
这部分内容，在第二版和第三版内容之间，作者是有改变描述方式的，但是，也不一定就能看懂。
可以结合SLAM十四讲里面的一些解释来理解。

另外，光流部分有数据集可以用。

### 关键点检测方法

#### GFTT Detector

Good Feature To Track，定义依赖于像素小局域内的自回归，想法是在图像做一个小量的移动之后和原图有多像。
图16-12没著名来源，但是这个画上的签名是中文。

#### Simple Blob Detector

#### Fast Feature Detector

#### SIFT Feature Detector

依赖图像金字塔

#### SURF Feature Detector

#### Star/CenSurE Feature Detector

最开始是VO用的，Center Surround Extremum。

#### BRIEF Descriptor extractor

#### BRISK

#### ORB Feature Detector

#### FREAK

这个描述符里面有提到感受野， Receptive Field

### Keypoints Filter

### Matching Methods

#### BFMatcher

#### FlannBasedMatcher

### Displaying Results

Drawkeypoints， DrawMatches

## 例子

### exa1601

比如，这个例子图片可以用TUM数据集的。

通过GoodFeature来捕捉相邻的图像OK，也就是满足小运动的相关图像，比较相似甚至不相似的物体之间分类，区分度是不一定够的。

## 习题

这章的习题给了一些OpenCV的Sample