# xlogic
> aoi: Area of interest. Implements with orthogonal linked list.  
> gs : Game server. A server with general functions.

gs build

ubuntu 18.04
安装 g++
apt install g++

安装 autoconf
apt install autoconf

####### 先编译第三方库
```
cd third_party
./build_third_party.sh
```
####### 再编译代码
```
cd ..
./build.sh
```

