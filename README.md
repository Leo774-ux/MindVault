# 心灵穹顶 · MindVault

> 基于 mmap 的嵌入式数据库引擎  
> 属于 StormForge 系列组件之一

---

## 简介

MindVault 是一个轻量级、高性能的嵌入式数据库引擎，采用内存映射文件（mmap）作为底层存储机制。它专为需要快速读写、低延迟、持久化存储的场景设计，特别适用于 AI 推理过程中的向量索引与元数据管理。

本项目是 StormForge 体系中的"数据底座"，与 mindstorm.cpp（推理引擎）配合使用，构成完整的端到端解决方案。

---

## 特性

- **零拷贝访问**：利用 mmap 实现文件直接映射到进程地址空间，避免传统 read/write 的系统开销。
- **事务支持**：简单的 WAL（预写日志）机制，保证崩溃恢复时的数据一致性。
- **B+ 树索引**：高效的键值查找与范围查询，支持整数与字符串键。
- **内存池管理**：减少碎片化，提高写入吞吐量。
- **跨平台**：Linux 原生支持，macOS/FreeBSD 可通过兼容层适配。
- **单文件嵌入**：无需独立服务进程，直接链接进你的应用。

---

## 快速开始

### 依赖

- C11 兼容编译器（GCC ≥ 4.9 或 Clang ≥ 3.6）
- CMake ≥ 3.10
- Linux 内核 ≥ 2.6（mmap 支持）

### 构建

```bash
git clone https://github.com/StormForge/mindvault.git
cd mindvault
mkdir build && cd build
cmake ..
make -j$(nproc)
```

### 测试

```bash
ctest --output-on-failure
```

---

## 使用示例

以下是一个简单的打开数据库、插入数据并查询的 C 语言示例：

```c
#include "mindvault.h"
#include <stdio.h>

int main() {
    mv_db *db = mv_open("test.mv", MV_CREATE);
    if (!db) { perror("mv_open"); return 1; }

    // 插入一条记录
    mv_entry entry = { .key = "user:1001", .value = "Alice", .vlen = 5 };
    mv_put(db, &entry);

    // 查询
    mv_entry result;
    if (mv_get(db, "user:1001", &result) == 0) {
        printf("Found: %.*s\n", (int)result.vlen, (char*)result.value);
        mv_free_entry(&result);
    }

    mv_close(db);
    return 0;
}
```

编译时需要链接 libmindvault.a：

```bash
gcc example.c -Lbuild/lib -lmindvault -lpthread -o example
```

---

## API 文档

完整 API 请参见 docs/api.md（待完善）。

---

## 贡献指南

欢迎提交 Issue 和 Pull Request。所有交流请使用中文。

1. Fork 本仓库
2. 创建你的特性分支 (`git checkout -b feat/awesome-feature`)
3. 提交改动 (`git commit -m "feat: 添加某项功能"`)
4. 推送分支 (`git push origin feat/awesome-feature`)
5. 发起 Pull Request

代码风格遵循项目根目录下的 `.clang-format` 配置。

---

## 致谢

- llama.cpp - GGUF 格式与 Transformer 推理的参考实现
- SQLite - 嵌入式数据库设计的灵感来源
- 元宝 - 一路以来的开发陪伴与技术支持
- 所有为开源社区贡献力量的开发者

---

## 许可证

本项目采用 MIT 许可证。详见 LICENSE。

---

> StormForge · 锻造数据的形状
