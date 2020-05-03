#!/usr/bin/python3
# 文件名：client.py

import stun
nat_type, external_ip, external_port = stun.get_ip_info(stun_host='stun.ekiga.net', stun_port=3478)

# 设置端口
port = 19302

# 免费的STUN服务器
sip = 'stun2.l.google.com'

print(nat_type, external_ip, external_port)