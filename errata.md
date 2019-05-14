# Errata

这本书关于代码的errata就不要写了，书上的代码都是片段，基本都不能用，参考官方repo。

1. $P_{258}$ `cv::threshold(s, s, 100, 100, cv::THRESH_TRUNC);`->`cv::threshold(s, dst, 100, 100, cv::THRESH_TRUNC);`
2. $P_{260}$`cv::LOAD_IMAGE_GRAYSCALE` ->`cv::IMREAD_GRAYSCALE`
3. $P_{409}$ Figure 14-1 have no dush lines(dotted lines) mentioned in P_{408}
