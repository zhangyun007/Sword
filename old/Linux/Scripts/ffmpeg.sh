vlc -vvv /home/ubuntu/shendiao.mp3 --sout "#transcode{vcodec=h264,vb=0,scale=0,acodec=mpga,ab=128,channels=2,samplerate=44100}:rtp{sdp=rtsp://:8554/test}"


# 播放视频
gst-launch-1.0 filesrc location=haizeiwang.mp4 ! decodebin ! videoconvert ! autovideosink

# 视频水平旋转播放
gst-launch-1.0 filesrc location=haizeiwang.mp4 ! decodebin ! videoflip method=horizontal-flip !videoconvert ! autovideosink

# 播放音频
gst-launch-1.0 filesrc location=haizeiwang.mp4 ! decodebin ! audioconvert ! autoaudiosink

# 播放音视频
gst-launch-1.0 playbin uri=file:///haizeiwang.mp4

# 推送测试视频到rtmp服务器
gst-launch-1.0 -e videotestsrc ! queue ! videoconvert ! x264enc ! flvmux streamable=true ! queue ! rtmpsink location='rtmp://deque.me/live/test01 live=true'

# 推送文件到rtmp服务器
gst-launch-1.0 filesrc location=haizeiwang.mp4 ! decodebin !  x264enc ! flvmux streamable=true ! queue ! rtmpsink location='rtmp://deque.me/live/test01 live=true'

# 发送rtp流到UDP 5000端口
gst-launch-1.0 -v filesrc location = haizeiwang.mp4 ! decodebin ! x264enc ! rtph264pay ! udpsink host=192.168.1.101 port=5000

# 从udp 5000端口播放rtp流
gst-launch-1.0 -v udpsrc port=5000 caps="application/x-rtp, media=video, clock-rate=90000, encoding-name=H264, payload=96, ssrc=3394826012, timestamp-offset=2215812541, seqnum-offset=46353" ! rtph264depay ! decodebin ! videoconvert ! autovideosink sync=false

# 将UDP 5000端口的rtp流推送至rtmp服务器 
gst-launch-1.0 -v udpsrc port=5000 ! application/x-rtp,payload=100,encoding-name=H264 ! rtph264depay ! video/x-h264, framerate=30/1 ! h264parse ! avdec_h264 ! videoscale ! video/x-raw, width=854, height=480 ! queue ! videoconvert ! queue ! x264enc bitrate=1000 key-int-max=60 bframes=0 byte-stream=false aud=true tune=zerolatency ! h264parse ! video/x-h264,level=(string)4.1,profile=main ! queue ! flvmux streamable=true name=mux ! queue ! rtmpsink location=rtmp://deque.me/live/test01

gst-launch-1.5 -v udpsrc port=5000 ! application/x-rtp,payload=100,encoding-name=H264 ! rtph264depay ! video/x-h264, framerate=30/1 ! h264parse ! avdec_h264 ! videoscale ! video/x-raw, width=854, height=480 ! queue ! videoconvert ! queue ! x264enc bitrate=1000 key-int-max=60 bframes=0 byte-stream=false aud=true tune=zerolatency ! h264parse ! video/x-h264,profile=main ! queue ! flvmux streamable=true name=mux ! queue ! rtmpsink location=rtmp://deque.me/live/test01



# 推流到rtmp服务器，譬如crtmpserver
ffmpeg -re -i /home/ubuntu/shendiao.mp3 -vcodec copy -acodec copy -f flv "rtmp://deque.me/live/test01 live=1"

# 客户端播放rtmp流
ffplay  "rtmp://deque.me/live/test01 live=1"



# 列设备
ffmpeg -list_devices true -f dshow -i dummy  

# 播放摄像头采集到的视频，"USB Camera"为Windows设备管理器里"图像设备"下显示的摄像头名称。
ffplay -f dshow -i video="USB Camera"
ffplay -f vfwcap -i 0  

# 查看设备选项
ffmpeg -list_options true -f dshow -i video="USB Camera"

# 设置摄像头分辨率
ffplay -video_size 640x480 -f dshow -i video="USB Camera"
ffplay -video_size 160x120 -f dshow -i video="USB Camera"

ffmpeg -f dshow -i video="USB Camera" -vcodec libx264 -preset:v ultrafast -tune:v zerolatency -f h264 udp://localhost:1111
ffplay -f h264 udp://localhost:1111
