import requests
try:
    # 如果在 WSL 里访问本机，用 localhost 即可
    res = requests.get('http://localhost:8080/hello') 
    print("Status Code:", res.status_code)
    print("Response Body:", res.text)
except Exception as e:
    print("Connection failed:", e)
