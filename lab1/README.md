# 实验一：PageRank 计算

## 文件

本文件夹包括实验一的所有源代码。

- `CMakeLists.txt`：CMake 源文件。
- `parser/`：页面解析器源文件。包括 Lex 源文件和 C++ 接口。
- `graph/`：图数据结构的源文件。
- `flow/`：主函数依次调用的流程。最核心的 PageRank 算法位于该文件夹下的 `6_pagerank.hpp` 中。
- `script/`：给报告画图用的。
- `global.hpp`：全局变量。
- `main.cpp`：主函数。

本实验的报告不开放获取。

## 部署

使用 CMake 配置并生成即可。需安装 win_flex（Windows 上）或 flex（UNIX 上）。具体流程略，有需要请联系我。

