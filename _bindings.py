import ctypes

# 加载动态链接库
lib = ctypes.CDLL('./lib/libmindvault.so')

# 定义结构体
class Record(ctypes.Structure):
    _fields_ = [
        ("id", ctypes.c_int),
        ("data", ctypes.c_char * 256)
    ]

class Database(ctypes.Structure):
    _fields_ = [
        ("permission_level", ctypes.c_int),
        ("records", Record * 100),
        ("record_count", ctypes.c_int)
    ]

# 定义函数原型
lib.mv_init.restype = ctypes.c_int
lib.mv_open.argtypes = [ctypes.c_char_p]
lib.mv_open.restype = ctypes.c_int
lib.mv_insert.argtypes = [ctypes.c_int, ctypes.c_char_p]
lib.mv_insert.restype = ctypes.c_int
lib.mv_query.argtypes = [ctypes.c_int]
lib.mv_query.restype = ctypes.POINTER(Record)
lib.mv_close.restype = None
lib.mv_status.restype = None

class MindVault:
    def __init__(self):
        self._db = Database()  # 创建数据库实例

    def init(self):
        return lib.mv_init()

    def open(self, path):
        return lib.mv_open(path.encode('utf-8'))

    def insert(self, id, data):
        return lib.mv_insert(id, data.encode('utf-8'))

    def query(self, id):
        rec_ptr = lib.mv_query(id)
        if rec_ptr:
            rec = rec_ptr.contents
            return {"id": rec.id, "data": rec.data.decode('utf-8')}
        return None

    def close(self):
        lib.mv_close()

    def status(self):
        lib.mv_status()

# 暴露 MindVault 类
__all__ = ["MindVault"]
