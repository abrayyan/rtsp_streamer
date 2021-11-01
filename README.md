# RTSP Stream Producer
A simple executable runner that streams a v4l2 camera feed via rtsp. Default parametes are:

### Installation
```
mkdir build && \
cd build && \
cmake .. && \
make -j`nproc`
```

### Run

* `./rtsp_streamer` which would capture the stream and run under default configurations:
    
    * device : `-v` : `/dev/video0`
    * port : `-p` : 8554
    * height : `-h` : 1080
    * width : `-w` : 1920
    * stream name : `-n` : stream
          
* To run under different configs:
    ```
    ./rtsp_streamer -p 8554 -h 1080 -w 1920 -v 1
    ```

To view the stream, open a network stream in vlc and type in the url ex: `rtsp://127.0.0.1:8554/stream`
