# MindVault

https://img.shields.io/badge/python-3.10+-blue.svg](https://www.python.org/downloads/)
https://img.shields.io/badge/License-MIT-yellow.svg](https://opensource.org/licenses/MIT)
https://img.shields.io/badge/code%20style-black-000000.svg](https://github.com/psf/black)
https://img.shields.io/pypi/v/mindvault.svg](https://pypi.org/project/mindvault/)

**MindVault** 是一个安全、高效的数据存储与传输工具包，专为现代应用设计，提供统一的数据管理解决方案。

## ✨ 特性

### 🚀 高性能传输
- **多协议支持**：TCP、UDP、WebSocket等多种传输协议
- **断点续传**：大文件传输支持断点续传
- **压缩加密**：内置数据压缩和端到端加密
- **并行传输**：支持多线程/多进程并发传输
- **进度监控**：实时传输进度和状态监控

### 💾 智能存储
- **多种存储格式**：JSON、YAML、CSV、TXT、JSON Lines
- **嵌入式存储**：内置SQLite、Shelve、Pickle存储后端
- **查询引擎**：灵活的数据查询和过滤
- **索引优化**：自动索引和查询优化
- **数据迁移**：无缝数据迁移和版本管理

### 🔄 可靠同步
- **双向同步**：实时双向数据同步
- **冲突解决**：智能冲突检测和解决方案
- **版本控制**：完整的数据变更历史记录
- **增量同步**：仅同步变更部分，节省带宽

### 🎯 多种接口
- **命令行界面(CLI)**：功能完整的命令行工具
- **图形界面(GUI)**：基于PyQt5的桌面应用
- **Web界面**：基于FastAPI的Web控制台
- **Python API**：完整的Python编程接口

## 📦 安装

### 基础安装
```bash
pip install mindvault
```

### 可选功能安装
```bash
# 安装GUI功能
pip install mindvault[gui]

# 安装Web功能
pip install mindvault[web]

# 安装完整功能
pip install mindvault[full]

# 开发模式安装
git clone https://github.com/leo774-ux/mindvault.git
cd mindvault
pip install -e ".[dev]"
```

## 🚀 快速开始

### 1. 文件传输
```python
from mindvault.net import FileTransfer
from mindvault.net.protocols import TCPProtocol

# 创建传输实例
transfer = FileTransfer(TCPProtocol())

# 发送文件
await transfer.send_file(
    source="/path/to/local/file.txt",
    destination="tcp://127.0.0.1:8888/file.txt",
    encryption=True,
    compression=True
)

# 接收文件
await transfer.receive_file(
    source="tcp://127.0.0.1:8888/file.txt",
    destination="/path/to/save/file.txt"
)
```

### 2. 数据存储
```python
from mindvault.storage import get_storage

# 获取JSON存储实例
storage = get_storage("json", "/path/to/data.json")

# 存储数据
storage.set("user:1", {"name": "Alice", "age": 25})
storage.set("user:2", {"name": "Bob", "age": 30})

# 查询数据
users = storage.query("user:*")
young_users = storage.query("user:*", filters={"age": {"$lt": 30}})

# 更新数据
storage.update("user:1", {"age": 26})

# 删除数据
storage.delete("user:2")
```

### 3. 数据同步
```python
from mindvault.sync import SyncManager

# 创建同步管理器
sync_manager = SyncManager(
    source_storage=get_storage("json", "/path/to/source.json"),
    target_storage=get_storage("yaml", "/path/to/target.yaml"),
    sync_strategy="bidirectional"
)

# 开始同步
await sync_manager.start()

# 手动触发同步
await sync_manager.sync()

# 获取同步状态
status = sync_manager.get_status()
print(f"同步状态: {status}")
```

## 📖 使用示例

### 命令行使用
```bash
# 传输文件
mindvault transfer send /path/to/file.txt tcp://localhost:8888/
mindvault transfer receive tcp://localhost:8888/ /path/to/save/

# 存储管理
mindvault storage set "key" "value" --format json
mindvault storage get "key" --format json
mindvault storage query "user:*" --filters '{"age": {"$gt": 20}}'

# 数据同步
mindvault sync start /path/source.json /path/target.yaml
mindvault sync status
```

### Python API
```python
import asyncio
from mindvault import MindVault

async def main():
    # 创建MindVault实例
    mv = MindVault()
    
    # 文件传输
    await mv.transfer_file(
        source="local.txt",
        destination="remote.txt",
        protocol="tcp"
    )
    
    # 数据管理
    storage = mv.get_storage("json", "data.json")
    await storage.batch_set({
        "item:1": {"name": "Item 1"},
        "item:2": {"name": "Item 2"}
    })
    
    # 同步配置
    await mv.sync_folders(
        source="/path/source",
        target="/path/target",
        interval=60  # 每分钟同步一次
    )

asyncio.run(main())
```

## 🔧 配置

MindVault支持多种配置方式：

### 配置文件
```yaml
# config.yaml
logging:
  level: INFO
  format: "%(asctime)s - %(name)s - %(levelname)s - %(message)s"

transfer:
  chunk_size: 8192
  max_retries: 3
  encryption: true
  
storage:
  default_format: json
  compression: true
  
sync:
  strategy: bidirectional
  conflict_resolution: newer_wins
```

### 环境变量
```bash
export MINDPORT_LOG_LEVEL=INFO
export MINDPORT_TRANSFER_CHUNK_SIZE=8192
export MINDPORT_STORAGE_COMPRESSION=true
```

## 📁 项目结构

```
mindvault/
├── src/mindvault/
│   ├── core/          # 核心模块
│   ├── net/           # 网络传输
│   ├── storage/       # 数据存储
│   ├── sync/          # 数据同步
│   ├── cli/           # 命令行接口
│   ├── gui/           # 图形界面
│   ├── web/           # Web接口
│   ├── plugins/       # 插件系统
│   ├── data/          # 数据文件
│   └── tools/         # 工具脚本
├── tests/             # 测试套件
├── docs/              # 文档
├── examples/          # 示例代码
└── scripts/           # 辅助脚本
```

## 🧪 测试

运行测试套件：

```bash
# 安装测试依赖
pip install -e ".[dev]"

# 运行所有测试
pytest

# 运行特定测试
pytest tests/unit/
pytest tests/integration/

# 带覆盖率的测试
pytest --cov=mindvault tests/

# 运行性能测试
pytest tests/benchmarks/ -m performance
```

## 🤝 贡献

我们欢迎任何形式的贡献！请查看以下指南：

### 开发环境设置
```bash
# 1. Fork 并克隆仓库
git clone https://github.com/leo774-ux/mindvault.git
cd mindvault

# 2. 创建虚拟环境
python -m venv venv
source venv/bin/activate  # Linux/macOS
# 或
venv\Scripts\activate  # Windows

# 3. 安装开发依赖
pip install -e ".[dev]"

# 4. 安装预提交钩子
pre-commit install
```

### 提交规范
- 使用 https://www.conventionalcommits.org/ 规范
- 每个提交应该只做一件事
- 提交前运行测试确保通过

### Pull Request 流程
1. Fork 本仓库
2. 创建特性分支 (`git checkout -b feature/amazing-feature`)
3. 提交更改 (`git commit -m 'feat: add amazing feature'`)
4. 推送到分支 (`git push origin feature/amazing-feature`)
5. 开启 Pull Request

## 📄 许可证

本项目采用 MIT 许可证 - 查看 LICENSE 文件了解详情。

## 🆘 支持

- 📖 https://mindvault.readthedocs.io
- 🐛 https://github.com/leo774-ux/mindvault/issues
- 💬 https://github.com/leo774-ux/mindvault/discussions
- 💡 https://github.com/leo774-ux/mindvault/issues/new?template=feature_request.md

## 🎯 路线图

- [ ] 1.0.0 版本发布
- [ ] 支持更多存储后端 (MongoDB, PostgreSQL)
- [ ] 添加分布式存储支持
- [ ] 实现增量备份功能
- [ ] 添加机器学习数据管理模块
- [ ] 开发移动端应用

## 🙏 特别鸣谢

特别感谢 **腾讯元宝** 在项目开发过程中提供的技术支持与帮助。

---

**MindVault** © 2024 https://github.com/leo774-ux | 基于 LICENSE 发布

<p align="center">
  <sub>用 ❤️ 编写 | 开源创造价值</sub>
</p>
