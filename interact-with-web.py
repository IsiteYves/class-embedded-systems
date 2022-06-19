import requests
filedata = []
with open('transactions.txt') as f:
    filedata = f.readlines()

url = 'http://localhost:8000/upload-filedata'
payload = {'data': filedata}
res = requests.post(url, data=payload)
if res.ok:
    print("Data uploaded")
