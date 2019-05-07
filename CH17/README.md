# CH17 Tracking

## 导读

这章内容以前是和前一章在一起的，这个版本被拆开。

- 这章讲了Kalman Filter：考虑到我们系统的状态，系统的动态以及观测，来估计真实的运动状态。
- 关于star和hat也做了注释说明
- 在介绍Kalman Filter的时候说明了Kalman Filter适用的情况。
- 两个高斯分布合并之后依然是高斯分布。
- Kalman Filter就是线性加权，考虑增益和变化量。
- 均值和方差是概率分布的一阶和二阶矩。

## 内容

### 基本概念

### 稠密光流in n o vain n o vain n o va

#### Farneback Polynomial Expansion algorithm

#### Dual TV-L1 Algorithm

#### Simple Flow Algorithm

### Mean-Shift and Camshift Tracking

#### Mean-Shift

#### Camshift

### Motion Templates

### Estimators

#### Kalman Filter

这部分比较重要。
初始的状态$(\vec{x}^*_0, \Sigma^*_0)$称为先验分布。

Kalman Filter三个假设：

- 线性模型：$S_{k+1}=F*S_k$
- 白噪声
- 高斯噪声 : 这两条说明噪声可以用高斯分布表示，均值和方差可以表示这个噪声。

书中有提到这个假设是“Strong but reasonable”的假设，也解释说这些假设看起来很严格，但是和实际场景意外的匹配。

看， 有时候，我们可能会很直觉的把事情想得复杂，做一些看起来很粗糙的假设，却能解决问题。

给定观测的条件下的最大后验概率的意思是考虑到了之前模型的不确定性以及新的观测的不确定性之后得到正确结果的最大可能性。

Kalman Filter是在给定三个假设的条件下，合并不同数据源的数据或者同一数据源不同时间的数据。从我们已知出发，获取新信息，然后基于我们对已知信息的确定性以及新的信息决定如何加权合并新旧信息。

所以Kalman Filter的主旨就是信息融合。

标准差是表示我们测量有多好的不确定性。

迭代形式：

$$
\begin{aligned}
x_k^*&=x_{k-1}^*+K(x_k-x_{k-1}^*)\\
\sigma_k^{*2}&=(1-K)\sigma_{k-1}^{*2}\\
K&=\frac{\sigma_{k-1}^{*2}}{\sigma_{k-1}^{*2}+\sigma_k^2}
\end{aligned}
$$

可以看出这个就是线性加权，考虑到综合利用前后两个结果的线性加权。看到这里，知道大部分融合问题，就是加权求和，只是这个权重怎么定。

配图17-11就是两个高斯的合并情况，这个图是概率密度图，不是简单的相加，是卷积。

另外，提到高斯模型合并，就会想到GMM。GMM和KF是两个维度对同一个问题的考虑，想一想时间步这个概念，以及时域和频域的关系。

Kalman Filter考虑三种运动：

1. dynamical motion
1. control motion
1. random motion

在Kalman Filter框架下，随机噪声假设为高斯噪声，或者噪声可以用高斯模型建模的。

先考虑动态系统的各种运动，update到旧的测量之后，再和新的测量进行融合。

### 例子

#### 1701

其实这个例子可以再扩展，虽然图片本来就可视化了结果，但是并没有说明各种颜色的作用，这图不完备。
附件的代码改了下，说明了不同颜色的含义。

// 另外，这个例子可以数字化显示噪声和估计值的差异，做对比。有空完善下。

这个例子里面也说了，没有用到Control inputs。