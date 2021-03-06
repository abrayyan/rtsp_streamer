#include <gst/gst.h>

#include <gst/rtsp-server/rtsp-server.h>
#include <algorithm>


#define DEFAULT_RTSP_PORT "8554"
#define DEFAULT_DISABLE_RTCP FALSE
#define DEFAULT_STREAM_NAME "stream"
#define DEFAULT_VIDEO_SOURCE 0
#define DEFAULT_WIDTH 1920
#define DEFAULT_HEIGHT 1080


static char *stream_name = (char *) DEFAULT_STREAM_NAME;
static char *port = (char *) DEFAULT_RTSP_PORT;
static gboolean disable_rtcp = DEFAULT_DISABLE_RTCP;


char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}


int
main (int argc, char *argv[])
{

    gst_init(&argc, &argv);

    GMainLoop *loop;
    GstRTSPServer *server;
    GstRTSPMountPoints *mounts;
    GstRTSPMediaFactory *factory;


    char pipeline[250];
    int ret, video_reference = DEFAULT_VIDEO_SOURCE, width = DEFAULT_WIDTH, height = DEFAULT_HEIGHT;

    char * portc = getCmdOption(argv, argv + argc, "-p");
    if (portc)
    {
        port = portc;
    }

    char * heightc = getCmdOption(argv, argv + argc, "-h");
    if (heightc)
    {
        height = atoi(heightc);
    }

    char * widthc = getCmdOption(argv, argv + argc, "-w");
    if (widthc)
    {
        width = atoi(widthc);
    }

    char * video_referencec = getCmdOption(argv, argv + argc, "-v");
    if (widthc)
    {
        video_reference = atoi(video_referencec);
    }

    ret = sprintf(pipeline, "( v4l2src device=\"/dev/video%d\" ! videoconvert ! videoscale ! video/x-raw,format=I420,width=%d,height=%d ! x265enc speed-preset=ultrafast tune=zerolatency ! rtph265pay name=pay0 pt=96 )", video_reference, width, height);

    //"( v4l2src device="/dev/video0" ! videoconvert ! video/x-raw,format=I420 ! x265enc ! rtph265pay name=pay0 pt=96 )"
    //char *pipeline_char = "( v4l2src device=\"/dev/video4\" ! video/x-raw,width=1280,height=720 ! videoconvert ! video/x-raw,format=I420 ! x265enc speed-preset=ultrafast tune=zerolatency ! rtph265pay name=pay0 pt=96 )";

    loop = g_main_loop_new (NULL, FALSE);

    /* create a server instance */
    server = gst_rtsp_server_new ();
    g_object_set (server, "service", port, NULL);


    /* get the mount points for this server, every server has a default object
     * that be used to map uri mount points to media factories */
    mounts = gst_rtsp_server_get_mount_points (server);


    /* make a media factory for a test stream. The default media factory can use
     * gst-launch syntax to create pipelines.
     * any launch line works as long as it contains elements named pay%d. Each
     * element with pay%d names will be a stream */
    factory = gst_rtsp_media_factory_new ();

    //TODO ; add option to read form cl
    gst_rtsp_media_factory_set_launch (factory, pipeline);

    //gst_rtsp_media_factory_set_launch (factory, pipeline_char);
    gst_rtsp_media_factory_set_shared (factory, TRUE);
    //gst_rtsp_media_factory_set_enable_rtcp (factory, !disable_rtcp);


    /* attach the test factory to the /test url */
    char stream_source[64];
    sprintf(stream_source, "/%s", stream_name);
    gst_rtsp_mount_points_add_factory (mounts, stream_source, GST_RTSP_MEDIA_FACTORY(factory));

    /* don't need the ref to the mapper anymore */
    g_object_unref (mounts);

    /* attach the server to the default maincontext */
    if (gst_rtsp_server_attach(server, NULL) == 0)
        return 1;

    /* start serving */
    g_print ("stream ready at rtsp://127.0.0.1:%s/%s\n", port, stream_name);
    g_main_loop_run (loop);

    return 0;
}
