# MindVault

!https://img.shields.io/badge/python-3.10%2B-blue
!https://img.shields.io/badge/license-MIT-green
!https://img.shields.io/badge/build-passing-brightgreen
!https://img.shields.io/badge/coverage-95%25-brightgreen

**MindVault** 是一个安全、高效的数据存储与传输工具包，专为现代数据管理需求设计。它提供了文件传输、数据存储、数据同步等多种功能，支持命令行、图形界面和Web API三种使用方式。

## ✨ 特性

### 🚀 核心功能
- **多协议文件传输**：支持TCP、UDP、WebSocket等多种传输协议
- **安全传输**：端到端加密、完整性校验、压缩传输
- **高性能存储**：支持JSON、YAML、CSV、TXT、JSON Lines等多种格式
- **智能同步**：双向/单向同步、冲突检测与解决、增量同步
- **版本控制**：自动版本管理、历史记录、回滚功能

### 🎯 技术亮点
- **现代Python**：基于Python 3.10+，充分利用类型提示和异步特性
- **模块化设计**：插件化架构，易于扩展和维护
- **异步I/O**：基于asyncio的高性能异步处理
- **类型安全**：完整的类型提示，支持mypy静态检查
- **多种接口**：CLI命令行、GUI图形界面、Web API

### 🔒 安全特性
- 传输层加密（TLS/SSL支持）
- 端到端数据加密
- 完整性校验（SHA-256/MD5）
- 安全的密钥管理
- 访问控制和权限管理

## 📦 安装

### 系统要求
- Python 3.10 或更高版本
- 操作系统：Windows 10+/macOS 10.15+/Linux

### 快速安装

#### 基础安装（仅核心功能）
```bash
pip install mindvault
```

#### 安装完整功能
```bash
pip install "mindvault[full]"
```

#### 安装特定功能
```bash
# 仅安装GUI功能
pip install "mindvault[gui]"

# 仅安装Web功能
pip install "mindvault[web]"

# 安装开发版本
pip install "mindvault[dev]"
```

#### 从源码安装
```bash
git clone https://github.com/mindvault-team/mindvault.git
cd mindvault
pip install -e ".[full]"
```

## 🚀 快速开始

### 基本使用

#### 文件传输
```python
from mindvault.net.transfer import FileTransfer

# 发送文件
transfer = FileTransfer(host="127.0.0.1", port=8888)
await transfer.send_file("local_file.txt", "remote_file.txt")

# 接收文件
await transfer.receive_file("remote_file.txt", "local_file.txt")
```

#### 数据存储
```python
from mindvault.storage.kv import JSONStore

# 创建存储实例
store = JSONStore("data.json")

# 存储数据
store.set("user:1", {"name": "Alice", "age": 30})
store.set("user:2", {"name": "Bob", "age": 25})

# 查询数据
user = store.get("user:1")
users = store.query(lambda x: x["age"] > 25)

# 保存到文件
store.save()
```

#### 数据同步
```python
from mindvault.sync import SyncManager

# 创建同步管理器
sync = SyncManager()

# 配置同步规则
config = {
    "source": "/path/to/source",
    "target": "/path/to/target",
    "strategy": "bidirectional",  # 双向同步
    "interval": 60,  # 60秒同步一次
}

# 开始同步
await sync.start(config)
```

### 命令行使用

#### 文件传输
```bash
# 发送文件
mv-transfer send --host 127.0.0.1 --port 8888 local_file.txt remote_file.txt

# 接收文件
mv-transfer receive --host 127.0.0.1 --port 8888 remote_file.txt local_file.txt

# 列出传输任务
mv-transfer list
```

#### 数据存储
```bash
# 设置键值
mv-storage set --store data.json user:1 '{"name": "Alice", "age": 30}'

# 获取键值
mv-storage get --store data.json user:1

# 查询数据
mv-storage query --store data.json 'age > 25'

# 导出数据
mv-storage export --store data.json --format jsonl output.jsonl
```

#### 数据同步
```bash
# 配置同步
mv-sync config add my-sync \
  --source /path/to/source \
  --target /path/to/target \
  --strategy bidirectional

# 启动同步
mv-sync start my-sync

# 查看同步状态
mv-sync status

# 解析冲突
mv-sync resolve --all
```

## 📁 项目结构

```
mindvault/
├── src/
│   └── mindvault/           # 主包
│       ├── core/            # 核心模块
│       ├── net/             # 网络传输
│       ├── storage/         # 数据存储
│       ├── sync/            # 数据同步
│       ├── cli/             # 命令行接口
│       ├── gui/             # 图形界面
│       ├── web/             # Web接口
│       ├── plugins/         # 插件系统
│       ├── data/            # 默认数据
│       └── tools/           # 工具脚本
├── tests/                   # 测试套件
├── examples/                # 使用示例
├── docs/                    # 项目文档
└── scripts/                 # 辅助脚本
```

## ⚙️ 配置

MindVault 支持多种配置方式：

### 配置文件
配置文件位于 `~/.mindvault/config.yaml` 或项目根目录的 `mindvault.yaml`。

```yaml
# mindvault.yaml
logging:
  level: INFO
  format: "[%(asctime)s] %(levelname)s - %(name)s - %(message)s"

transfer:
  default_host: 127.0.0.1
  default_port: 8888
  chunk_size: 8192
  timeout: 30

storage:
  default_format: json
  compression: true
  encryption: true

sync:
  default_strategy: bidirectional
  conflict_resolution: newer
  max_history: 100
```

### 环境变量
```bash
export MINDFAULT_LOG_LEVEL=DEBUG
export MINDFAULT_TRANSFER_PORT=8888
export MINDFAULT_STORAGE_PATH=/data
```

### 命令行参数
```bash
mindvault --config /path/to/config.yaml
mv-transfer --host 192.168.1.100 --port 9999
```

## 🔌 插件系统

MindVault 支持插件扩展，可以通过插件添加：

### 添加自定义传输协议
```python
from mindvault.net.protocols import TransferProtocol

class MyProtocol(TransferProtocol):
    async def send(self, data, **kwargs):
        # 自定义发送逻辑
        pass
    
    async def receive(self, **kwargs):
        # 自定义接收逻辑
        pass
```

### 添加自定义存储后端
```python
from mindvault.storage.base import StorageBackend

class MyStorage(StorageBackend):
    def __init__(self, config):
        self.config = config
    
    async def save(self, data):
        # 自定义保存逻辑
        pass
    
    async def load(self):
        # 自定义加载逻辑
        pass
```

### 插件注册
```python
# setup.py
entry_points={
    "mindvault.plugins": [
        "my_protocol = my_package.plugins:MyProtocol",
        "my_storage = my_package.plugins:MyStorage",
    ]
}
```

## 🧪 测试

### 运行测试
```bash
# 运行所有测试
pytest

# 运行特定模块测试
pytest tests/test_net/

# 运行特定测试
pytest tests/test_net/test_transfer.py::TestFileTransfer

# 运行测试并生成覆盖率报告
pytest --cov=mindvault --cov-report=html
```

### 代码质量检查
```bash
# 代码格式化
black src/
isort src/

# 类型检查
mypy src/

# 代码检查
ruff check src/

# 运行所有检查
./scripts/dev/check_all.sh
```

## 📖 文档

### 在线文档
访问 https://mindvault.readthedocs.io 获取完整文档。

### 本地构建文档
```bash
# 安装文档依赖
pip install -e ".[docs]"

# 构建文档
cd docs
make html

# 查看文档
open _build/html/index.html
```

### 文档结构
```
docs/
├── index.md              # 首页
├── getting_started.md    # 快速开始
├── installation.md       # 安装指南
├── configuration.md     # 配置指南
├── guides/              # 使用指南
│   ├── file_transfer.md
│   ├── data_storage.md
│   ├── data_sync.md
│   ├── cli_usage.md
│   ├── web_dashboard.md
│   └── gui_usage.md
├── api/                  # API文档
├── tutorials/           # 教程
├── reference/           # 参考文档
└── faq.md              # 常见问题
```

## 🤝 贡献

我们欢迎任何形式的贡献！请查看 CONTRIBUTING.md 了解如何参与项目。

### 开发流程
1. Fork 项目
2. 创建功能分支 (`git checkout -b feature/amazing-feature`)
3. 提交更改 (`git commit -m 'Add some amazing feature'`)
4. 推送到分支 (`git push origin feature/amazing-feature`)
5. 开启 Pull Request

### 开发环境设置
```bash
# 克隆项目
git clone https://github.com/mindvault-team/mindvault.git
cd mindvault

# 创建虚拟环境
python -m venv venv
source venv/bin/activate  # Linux/macOS
# 或
venv\Scripts\activate  # Windows

# 安装开发依赖
pip install -e ".[dev]"

# 安装预提交钩子
pre-commit install
```

### 代码规范
- 遵循 https://www.python.org/dev/peps/pep-0008/ 代码风格
- 使用类型提示
- 编写单元测试
- 保持文档与代码同步
- 提交信息遵循 https://www.conventionalcommits.org/

## 📄 许可证

本项目基于 MIT 许可证开源 - 查看 LICENSE 文件了解详情。

## 📞 支持

### 问题反馈
- https://github.com/mindvault-team/mindvault/issues - 报告Bug或请求功能
- https://github.com/mindvault-team/mindvault/discussions - 讨论和交流

### 社区
- 邮箱：team@mindvault.ai
- Discord：https://discord.gg/mindvault
- Twitter：https://twitter.com/mindvault_ai

### 版本历史
查看 CHANGELOG.md 了解版本更新历史。

## 🌟 星星历史

https://api.star-history.com/svg?repos=mindvault-team/mindvault&type=Date](https://star-history.com/#mindvault-team/mindvault&Date)

## 🙏 致谢

感谢所有为这个项目做出贡献的人！

### 主要贡献者
- https://github.com/your-username - 项目创建者和维护者
- https://github.com/contributor1 - 核心开发者
- https://github.com/contributor2 - 文档维护

### 使用的开源项目
- https://github.com/pyca/cryptography - 加密功能
- https://github.com/pydantic/pydantic - 数据验证
- https://github.com/Textualize/rich - 终端美化
- https://github.com/tiangolo/fastapi - Web框架
- 以及其他所有依赖的开源项目

---

**MindVault** - 为您的数据管理提供专业、安全的解决方案。
