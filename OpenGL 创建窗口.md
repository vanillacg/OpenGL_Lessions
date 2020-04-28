# OpenGL 创建窗口

https://www.jianshu.com/p/c2ce5e22e01b

#### step1.首先安装homebrew

在终端输入



```ruby
$ ruby --version
$ ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

#### step2.安装GLEW和GLFW库

在终端输入



```ruby
$ brew install glew
$ brew install glfw3
```

安装位置在 **/usr/local/Cellar**

#### step3.下载GLAD库

打开GLAD的[在线服务](http://glad.dav1d.de/)，将语言(Language)设置为**C/C++**，在API选项中，选择**3.3** **以上的OpenGL(gl)版本**。之后将模式(Profile)设置为**Core**，并且保证生成加载器**(Generate a loader)**的选项是选中的。都选择完之后，点击生成(Generate)按钮来生成库文件。
 GLAD现在应该提供给你了一个zip压缩文件，包含两个头文件目录，和一个glad.c文件。将两个头文件目录（glad和KHR）复制到Include文件夹中（路径"/usr/local/include"），并添加glad.c文件到工程中。

#### step4.配置xcode

在Xcode中找到Peference菜单项，然后在里面找到Locations项，再点击Custom Paths，添加四项
 配置依次为：

![image-20200427191812004](/Users/chenguang/Library/Application Support/typora-user-images/image-20200427191812004.png)

具体位置如图所示

![image-20200427191824519](/Users/chenguang/Library/Application Support/typora-user-images/image-20200427191824519.png)
 在这里需要修改的只有一项，就是要根据你自己安装的glew的版本和glfw3的版本修改2.1.0和3.2.1这两个版本号，其他的都是一样的。

#### step5.更改头文件和库搜索路径

创建一个新的Xcode项目（command line tool），语言选择C++。接着，在项目的Bulid Settings里面找到Header Search Paths和Library Search Paths两项，在Header Search Paths中加入



```ruby
/usr/local/include
$(glew_header) 
$(glfw_header)
```

同理也在Library Search Paths中加入



```jsx
$(glew_lib) 
$(glfw_lib)
```

#### step6.导入framework

在项目的General中找到Linked Frameworks and Libraries，点击‘+’号，添加如下三个文件



```css
OpenGL.framework    
libGLEW.2.1.0.dylib    
libglfw3.2.dylib
```

添加两个dylib文件的方法是，在你没有在framework中搜索到这两个文件时，点击add other，然后点击shift+command+G进入/usr/local文件夹，然后根据我们之前说的安装glew和glfw3的路径找到这两个文件夹，在这两个文件夹中找到这两个文件，当然这两个文件可能和我图中给出的文件名不同还是因为安装的版本号不同，这个需要注意一下。

#### step7.添加头文件



```cpp
#include <GL/glew.h>
#include <GLFW/glfw3.h>
```

或



```cpp
#include <glad/glad.h>  //glad 必须在GLFW之前添加
#include <GLFW/glfw3.h>
```



作者：叫我小黑
链接：https://www.jianshu.com/p/c2ce5e22e01b
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。