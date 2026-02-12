# MindVault

> **安全、高效的数据存储与传输工具包**  
> 由 **Leo774-ux** 个人开发，基于 Python 3.10+ 构建，旨在提供轻量级、无 SQL 依赖的现代化数据管理解决方案。

---

## 🚀 项目简介

**MindVault** 是一个专为现代数据管理需求设计的 Python 工具包。它摒弃了传统的关系型数据库（SQL）依赖，采用文件系统、键值存储和内存数据库等轻量级技术，提供了从数据存储、网络传输到多端同步的全套工具链。

## ✨ 核心特性

*   **无 SQL 依赖**：完全基于文件系统、键值存储和内存数据库，部署简单，资源占用低。
*   **多协议支持**：支持 HTTP/HTTPS、WebSocket 等现代网络协议，实现高效的数据传输。
*   **数据同步**：内置智能同步算法，支持多设备、多端数据实时或定时同步。
*   **安全存储**：提供数据加密、访问控制等安全机制，保护数据隐私。
*   **模块化设计**：各个功能模块独立，支持按需组合使用，避免功能臃肿。

## 🛠️ 技术栈

*   **语言**：Python 3.10+
*   **核心库**：Pydantic (数据验证)、Rich (CLI 美化)、Aiofiles (异步文件操作)
*   **网络**：HTTPX (HTTP 客户端)、WebSockets (WebSocket 支持)
*   **存储**：File-based Storage (文件存储)、Key-Value Store (键值存储)
*   **安全**：Cryptography (数据加密)

## 📦 快速开始

### 1. 环境要求

确保你的系统已安装 **Python 3.10** 或更高版本。

### 2. 安装

通过 pip 直接安装（推荐）：

```bash
pip install mindvault
```

或从源码安装：

```bash
git clone https://github.com/leo774-ux/mindvault.git
cd mindvault
pip install -e .
```

### 3. 基本使用

**存储数据**（使用键值存储示例）：

```python
from mindvault import KVStore

# 初始化存储
store = KVStore("./data")

# 存储数据
store.set("user:1", {"name": "Alice", "age": 30})

# 读取数据
data = store.get("user:1")
print(data)  # {'name': 'Alice', 'age': 30}
```

**启动传输服务**（使用 HTTP 服务示例）：

```python
from mindvault import HTTPServer

# 启动服务
server = HTTPServer(port=8080)
server.start()
```

## 📁 项目结构

```plaintext
mindvault/
├── src/                    # 源码目录
│   └── mindvault/
│       ├── core/           # 核心配置与工具
│       ├── storage/        # 存储模块 (键值、文档、文件)
│       ├── net/            # 网络模块 (协议、传输、安全)
│       ├── sync/           # 同步模块 (差异计算、冲突解决)
│       └── cli/            # 命令行接口
├── tests/                  # 测试文件
├── docs/                   # 项目文档
├── examples/               # 使用示例
└── pyproject.toml          # 项目配置
```

## 🧪 开发与测试

1.  **克隆项目**：
    ```bash
    git clone https://github.com/leo774-ux/mindvault.git
    cd mindvault
    ```

2.  **安装开发依赖**：
    ```bash
    pip install -e ".[dev]"
    ```

3.  **运行测试**：
    ```bash
    pytest
    ```

## 🤝 贡献

欢迎提交 Issue 和 Pull Request！  
请确保你的代码符合项目规范，并包含相应的测试用例。

## 📄 许可证

本项目采用 **MIT** 许可证。详情请参阅 LICENSE 文件。

## 🙏 特别鸣谢

*   **腾讯元宝**：在项目开发过程中提供了宝贵的技术支持与建议。

---

**作者**：Leo774-ux  
**仓库**：https://github.com/leo774-ux/mindvault
