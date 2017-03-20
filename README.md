# C++ 调用 *Matlab Engine* 步骤

**matlab文档说明**http://cn.mathworks.com/help/matlab/calling-matlab-engine-from-c-c-and-fortran-programs.html?s_tid=srchtitle
## **step 1**<br>
 ![step 1](https://github.com/Rogerbin/Cpp-calling-Matlab-Engine/blob/master/img/m1.png)
 ![step 1](https://github.com/Rogerbin/Cpp-calling-Matlab-Engine/blob/master/img/m2.png)<br>
**_1_** 中添加 **D:\MATLAB7\bin\win32<br>**
**_2_** 中添加 **D:\MATLAB7\extern\include<br>**
**_3_** 中添加 **D:\MATLAB7\extern\lib\win32\microsoft\msvc71<br>**

 
#linker 添加:
>**libmx.lib<br>**
**libmex.lib<br>**
**libeng.lib<br>**
**libmat.lib<br>**

 ![step 2](https://github.com/Rogerbin/Cpp-calling-Matlab-Engine/blob/master/img/m3.png)<br>

_示例程序_：***main.cpp***
```cpp
#include <engine.h>
#include <iostream>
#include <string>
#include <cmath>

#pragma comment( lib, "libmx.lib" ) 
#pragma comment( lib, "libmex.lib" )
#pragma comment( lib, "libeng.lib" )
#pragma comment (lib, "libmat.lib")

using namespace std;

int main()
{
	Engine *m_pEngine;
	m_pEngine = engOpen(NULL);
	engSetVisible(m_pEngine,0);//设置Matlab command 不显示

	if (m_pEngine == NULL)
	{
		cout << "Error: Not Found"
	        << endl;
	            exit(1);
	}

	const int arraysize=1000;
	const double deg=.0174;
	double SinArray[arraysize];

	for(int i=0;i<arraysize;i++)
	{
		SinArray[i]=sin(i*deg);
	}
	cout<<"example";
	mxArray* SIN =mxCreateDoubleMatrix(arraysize,1,mxREAL);
	memcpy((void*)mxGetPr(SIN),(void*)SinArray,sizeof(double)*arraysize);
	engPutVariable(m_pEngine,"sinegraph",SIN);
	engEvalString(m_pEngine,"figure('units','normalized','outerposition',[0 0 1 1])");
	engEvalString(m_pEngine,"plot(sinegraph),");
	mxDestroyArray(SIN);//释放空间
	system("pause");
	engClose(m_pEngine);
}
```

------
# LNK1123: 转换到 COFF 期间失败: 文件无效或损坏

用VS2010编译C++项目时出现这样的错误：

LNK1123: 转换到 COFF 期间失败: 文件无效或损坏

**方案一：（这个方法比较好，在用qt运行时出现问题也能解决）

复制 C:\Windows\winsxs\x86_netfx-cvtres_for_vc_and_vb_b03f5f7f11d50a3a_6.1.7601.17514_none_ba1c770af0b2031b 目录下的 cvtres.exe 到C:\Program Files\Microsoft Visual Studio 10.0\VC\bin 目录下，直接覆盖替换。

**方案二：

是嵌入清单的问题，于是对该工程以及所有依赖工程进行如下操作
右键->工程属性->配置属性-> 清单工具->输入和输出->嵌入清单，选择[否]

1>LINK : fatal error LNK1123: 转换到 COFF 期间失败: 文件无效或损坏
1>CVTRES : fatal error CVT1100: 资源重复。类型: MANIFEST，名称: 1，语言: 0x0409

这个是由于日志文件引起的，可以将

项目\属性\配置属性\清单工具\输入和输出\嵌入清单：原来是“是”，改成“否”。
或者将
项目\属性\配置属性\链接器\清单文件\生成清单：原来是“是”，改成“否”。
