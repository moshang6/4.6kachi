2024-04-12
耗费整整两天时间，终于把卡池模拟器的优化做的差不多了，此次优化大幅减少程序大小由800多M缩小到80多M，同时加载时间几乎为0，界面切换也更加顺畅--具体操作为调用了libvlc视频库，从而使原来播放视频逐帧播放图片转为直接播放mp4文件，音频同理。频繁切换页面时标题栏会突然出现bug也已修复。不过此次优化出现一个新问题：终端会显示报错，不过实际并没有什么影响。
2024-04-25
此次更新了卡池至当前最新版本，并优化了分辨率会因电脑缩放原因变模糊的问题，同时新增了武器定轨操作界面，更符合游戏实际。
2024-04-26
修复武器池界面在16比10屏幕下的图像拉伸问题，添加游戏内字体
2024-04-27
添加背景音乐，优化噪音问题
如果你对我的研究感兴趣，不妨来我的网站看看：moshang.zicp.fun:8088
欢迎交流！