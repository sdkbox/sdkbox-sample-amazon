
# How to run sdkbox samples

Steps:

~~~bash
mkdir samples
cd samples

# must clone this repo
git clone --depth 1 https://github.com/sdkbox/sdkbox-cocos2d-x-binary.git

# clone sample repo
git clone --depth 1 https://github.com/sdkbox/sdkbox-sample-amazon.git

# run sample with specified language and platform
# eg: cpp and ios
./sdkbox-cocos2d-x-binary/run_sample.sh amazon cpp ios
# javascript and android
./sdkbox-cocos2d-x-binary/run_sample.sh amazon js android

# <optional> if exists "download-depends.sh" in sample repo, execute it
# ./sdkbox-sample-amazon/download-depends.sh

~~~

Memo:

1.  Sample repo and cocos2dx repo must be in same level directory

~~~
+-- sdkbox-cocos2d-x-binary
+-- sdkbox-sample-amazon
| +-- cpp
| +-- lua
| \-- js
~~~


# Requirements

1. Amazon Kindle Fire device
2. Install [Amazon App Tester](http://www.amazon.com/Amazon-App-Tester/dp/B00BN3YZM2/) app
3. Upload a JSON Data File to device

    ```
    $ adb push [Your_JSON_File_Folder]/amazon.sdktester.json /mnt/sdcard/
    ```

Here is more information:

- [https://developer.amazon.com/public/apis/earn/in-app-purchasing](https://developer.amazon.com/public/apis/earn/in-app-purchasing)
- [https://developer.amazon.com/public/apis/earn/in-app-purchasing/docs-v2/installing-and-configuring-app-tester](https://developer.amazon.com/public/apis/earn/in-app-purchasing/docs-v2/installing-and-configuring-app-tester)


----

# 中文

此用例演示亚马逊的 Android 内购功能。

## 前提
1. Amazon Kindle Fire 设备
2. 安装 [Amazon App Tester](http://www.amazon.com/Amazon-App-Tester/dp/B00BN3YZM2/) 应用
3. 把 json 文件上传到设备上

    ```
    $ adb push [Your_JSON_File_Folder]/amazon.sdktester.json /mnt/sdcard/
    ```

## 编译运行
cpp 为例:

```
cd cpp
cocos run -p android
```
