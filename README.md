# 仿真项目说明

本仓库包含一个基于 Verilog 的仿真项目，原本用于 ModelSim，现在已迁移至 Verilator 仿真环境。以下是运行方式的详细说明。

## 环境要求

1. **操作系统**：已测试Linux，Mac/Win可能需修改部分脚本
2. **工具链**：
   - Verilator（推荐版本 > 5.0以支持timing特性）
   - C++ 编译器（如 `g++` 或 `clang++`）
   - 波形查看工具（如 GTKWave）

## 仿真顶层文件

仓库中包含三套仿真顶层文件，分别位于 `sim/` 目录下：
- `tb_top_0.v`
- `tb_top_1.v`
- `tb_top_2.v`

每个顶层文件对应不同的仿真场景，需在 `main.cpp` 中手动修改实例化的模块名称以匹配当前仿真目标。

## 仿真步骤

### 1. 安装 Verilator

确保安装了 Verilator，推荐版本大于 5.0。可以通过以下命令安装：
```bash
sudo apt install verilator
```

### 2. 修改 `main.cpp`

根据需要选择仿真顶层文件，修改 `main.cpp` 中的 Verilated 模块名称。例如：
```cpp
#define VTOP Vtb_top_0
#include "Vtb_top_0.h" // 如果仿真 tb_top_0.v
```
将 `Vtb_top_0.h` 替换为对应的模块名称（如 `Vtb_top_1.h` 或 `Vtb_top_2.h`）。

### 3. 编译项目

运行以下命令编译项目：
```bash
make tb_top_0
```
编译完成后，生成的可执行文件`tb_top_0`位于 `build/` 目录下。

### 4. 运行仿真

运行以下命令启动仿真：
```bash
./build/tb_top_0
```
根据选择的顶层文件，替换 `tb_top_0` 为对应的仿真目标（如 `tb_top_1` 或 `tb_top_2`）。

### 5. 查看波形

仿真完成后，生成的波形文件为 `xxx.fst`（如cnt_ceil_wf.fst），可以使用 GTKWave 查看：
```bash
gtkwave xxx.fst
```

## 清理构建文件

运行以下命令清理构建文件：
```bash
make clean
```

## 注意事项

1. 仿真时间步长在 `tb_top_$i.v` 中定义，可根据需要调整：
    ```verilog
    initial begin
        #10000;
        $finish;
    end
    ```
2. 如果需要添加新的顶层文件，请确保在 `Makefile` 中更新 `TOPS` 变量：
   ```makefile
   TOPS = tb_top_0 tb_top_1 tb_top_2
   ```
3. 仿真过程中，`tb_top_$i` 无输入信号，依靠verilog的延时指令产生时钟。

## 目录结构

- `src/`：源代码文件
- `sim/`：仿真顶层文件
- `build/`：构建输出目录
- `main.cpp`：仿真入口文件
- `Makefile`：构建脚本

## 参考

- [Verilator 官方文档](https://verilator.org/)
- [GTKWave 官方文档](http://gtkwave.sourceforge.net/)