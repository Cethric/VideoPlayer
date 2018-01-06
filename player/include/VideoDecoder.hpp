//
// Created by rogan on 6/01/2018.
//

#ifndef VIDEOPLAYER_VIDEODECODER_HPP
#define VIDEOPLAYER_VIDEODECODER_HPP

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP

#include "wx/wx.h"

#endif

extern "C" {
#include <libavformat/avformat.h>

#include <libavcodec/avcodec.h>

#include <libavfilter/avfilter.h>

#include <libavutil/avutil.h>
#include <libavutil/imgutils.h>
#include <libavutil/opt.h>
#include <libavutil/parseutils.h>
#include <libavutil/hwcontext_d3d11va.h>

#include <libswresample/swresample.h>

#include <libswscale/swscale.h>

#include <libavdevice/avdevice.h>
}

#include <OpenGL.h>


namespace VP {
    class VideoDecoder {
    private:
        bool finished;
        bool playing;

        AVFormatContext *formatContext = nullptr;
        AVCodecContext *codecContext;
        AVCodec *codec;
        AVBufferRef *hwDeviceContext;

        int videoStreamIndex = -1;

        AVPixelFormat outputFormat = AV_PIX_FMT_RGB24;

        AVFrame *yuvFrame = nullptr;
        AVFrame *swFrame = nullptr;

        AVPacket *packet = nullptr;
//                    AVPacket packet{};
        struct SwsContext *swsContext = nullptr;
        int numBytes;
        int ret;

        uint8_t *rgbBuffer[AV_NUM_DATA_POINTERS];
        int rgbLines[AV_NUM_DATA_POINTERS];

        int last_frame_decoded;

    public:
        explicit VideoDecoder(wxString path);

        ~VideoDecoder();

        bool LoadVideo(wxString path);

        void Play();

        void Pause();

        void Stop();

        bool IsPlaying();

        bool IsFinished();

        bool HasFrame();

        void NextFrame(GLuint *rgb);
    };
}


#endif //VIDEOPLAYER_VIDEODECODER_HPP
