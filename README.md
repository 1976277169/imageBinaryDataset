# imageBinaryDataset

前一篇博客：[C/C++ 图像二进制存储与读取](http://blog.csdn.net/yhl_leo/article/details/50782792)中，已经讲解了如何利用C/C++的方法存储与读取二进制图像文件，本文继续讲述如何根据[CIFAR-10](http://www.cs.toronto.edu/~kriz/cifar.html)的格式制作自己的数据集。

所述博文与代码均已同步至GitHub：[yhlleo/imageBinaryDataset](https://github.com/yhlleo/imageBinaryDataset)

主要代码文件有三个：

 - `BinaryDataset.h`
 - `BinaryDataset.cpp`
 - `main.cpp`

以`main.cpp`给出的一个小demo为例，首先指定一个原数据图片所在的文件夹：

```c
std::string filefolder = "C:\\Samples\\train";
```

然后，自动获得该文件下的所有图片文件名：

```c
std::vector<std::string> fileLists = binData.getFileLists(filefolder); // load file name
```

这里有一点需要说明一下，`getFileLists()`是按照文件名升序顺序读取（大家都知道，文件名为字符串，comparable），文件命名最好不要以`1, 2, ..., 11, ...`这种方式存储，因为这么存，你就会发现`1`之后的文件可能不是你想的`2, 3, 4, ...`，而是`11, 12, 13, ...`。

如果你想按照顺序的某一堆数据是一种类别（我是这么做的，因为便于产生对应的`labels`），建议使用等宽零位补齐的方式命名，例如：`00001, 0002, ..., 0011, ...`，那么文件读取的顺序就会如我们所设定。

总结一下实现方法（仅供参考）：
 
 - 采集样本的时候可以先类别存于不同的文件夹，命名就随意吧，如果是使用一些抠图软件，也不用纠结一个一个手工修改成自己想要的命名（这么做工作量很大，真的很蛋疼。。。）；
 - 每一类数据整理好后，依次将每一类的数据，用程序读取并另存一份（读取使用`getFileLists()`，反正是一类的，也无所谓先后顺序）：
```c
    for ( int i=0; i<fileLists.size(); i++ )
	{
		char* curfile = new char[128];
		sprintf(curfile, "C:\\Samples\\class-1\\%04d.jpg", i);
		string fileName = filefolder + "\\";
		fileName += fileLists[i];
		cv::Mat image = cv::imread(fileName);
		cv::imwrite(curfile, image);
		delete[] curfile;
	}
```
 - 后面的其他类别也可以这样，为了按照顺序区分，依次进行其他类别的时候，只需要在改动文件夹后，将`sprintf(curfile, "C:\\Samples\\class-1\\%04d.jpg", i);`中的第三个参数`i`改为`i+k`，这里`k`是前面一类或几类的样本总数。
 - 最后，将重新命名的文件，存在一个文件夹里，记清楚类别对应的区间范围，以便生成`labels`。 

读取上述最终文件内的所有文件，接下来，生成`labels`（`labels`一般用`[0, 9]`组成的整数字）：

```c
std::vector<int> image_labels(size_list, 0);  // generate lables, here are all 0
```

当然，你也可以用`image_labels.push_back()`把所有的`labels`设置，但是熟悉`vector`的话，就会明白使用初始化长度，比那种做法更加高效（可以阅读本人的博客： [C++ 容器（一）：顺序容器简介](http://blog.csdn.net/yhl_leo/article/details/47759729)）。然后就相应地修改某些索引区间内的`label`值：

```c
for ( int i=0; i<count_class_k; i++ )
	image_labels[i] = 1;
```

都准备好后，就可以开始生成想要的二进制文件了：
```c
	std::string binfile = "C:\\Samples\\train.bin";
	binData.images2BinaryFile( filefolder, fileLists, image_labels, binfile );
```

到这里，已经制作好了二进制数据集，我很懒，想直接基于`tensorflow/models/image/cifar10`模块的源码跑我定义的数据集，想想只要跟`cifar10`数据集类似，那肯定没什么问题，下面是官网上下载的`cifar-10-binary.tar`解压后内容：

![cifar.rar](http://img.blog.csdn.net/20160304122224628)

这份数据集比较大，训练样本有`50000`，测试样本`10000`（我的数据集并没有这么大，但是又有什么关系呢！）。

看，这是我的数据集：

![cifar2](http://img.blog.csdn.net/20160304122537239)

是不是很迷你~

然后，将`tensorflow/models/image/cifar10`模块的拷贝中的部分参数修改成为适合自己数据集的，就OK了~

献上运行截图（训练测试集有`5196`张样本，所以`5196*0.4 = 2078`）：

![run](http://img.blog.csdn.net/20160304123542258)
