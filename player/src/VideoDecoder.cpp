//
// Created by rogan on 6/01/2018.
//

#include "VideoDecoder.hpp"

VP::VideoDecoder::VideoDecoder(wxString path) {
    this->finished = false;
    this->playing = false;

    static bool setup;

    if (!setup) {
        av_log_set_flags(AV_LOG_PRINT_LEVEL);
//        av_log_set_level(AV_LOG_TRACE);

        avcodec_register_all();
        avdevice_register_all();
        avfilter_register_all();
        av_register_all();

//        AVOutputFormat *outputFormat = nullptr;
//        AVCodec *codecs = nullptr;
//        AVHWDeviceType hwDeviceType = AV_HWDEVICE_TYPE_NONE;
//        const AVFilter *filter = nullptr;
//
//        wxLogInfo("Available Codecs:");
//        while ((codecs = av_codec_next(codecs)) != nullptr) {
//            wxLogInfo("    %s: %s (%s, %s)", codecs->name, codecs->long_name, codecs->wrapper_name, codecs->bsfs);
//        }
//
//        wxLogInfo("Available Output Devices:");
//        while ((outputFormat = av_output_video_device_next(outputFormat)) != nullptr) {
//            wxLogInfo(
//                        "    %s: %s <%s> (%s)",
//                        outputFormat->name,
//                        outputFormat->long_name,
//                        outputFormat->mime_type,
//                        outputFormat->extensions
//                );
//        }
//
//        wxLogInfo("Available Hardware Decoders: ");
//        while ((hwDeviceType = av_hwdevice_iterate_types(hwDeviceType)) != AV_HWDEVICE_TYPE_NONE) {
//            wxLogInfo("    %s", av_hwdevice_get_type_name(hwDeviceType));
//        }
//
//        wxLogInfo("Available Filters: ");
//        while ((filter = avfilter_next(filter)) != nullptr) {
//            wxLogInfo("    %s: %s", filter->name, filter->description);
//        }

        setup = true;
    }

    if (!LoadVideo(path)) {
        wxLogError("Failed to load video: '%s'", path);
    }
}

VP::VideoDecoder::~VideoDecoder() {
    this->finished = true;
    this->playing = false;

    av_frame_free(&yuvFrame);
    av_frame_free(&swFrame);
    av_packet_unref(packet);
    av_packet_free(&packet);
    sws_freeContext(swsContext);
    av_free(rgbBuffer[0]);

    av_buffer_unref(&this->codecContext->hw_frames_ctx);
    av_buffer_unref(&this->codecContext->hw_device_ctx);
    avcodec_free_context(&this->codecContext);
    av_buffer_unref(&hwDeviceContext);
    av_free(hwDeviceContext);
    avformat_free_context(this->formatContext);
    wxLogInfo("Video Decoder destroyed");
}

static wxString pixelFormatToString(AVPixelFormat format) {
    switch (format) {
        case AV_PIX_FMT_NONE:
            return "AV_PIX_FMT_NONE";
        case AV_PIX_FMT_YUV420P:
            return "AV_PIX_FMT_YUV420P";
        case AV_PIX_FMT_YUYV422:
            return "AV_PIX_FMT_YUYV422";
        case AV_PIX_FMT_RGB24:
            return "AV_PIX_FMT_RGB24";
        case AV_PIX_FMT_BGR24:
            return "AV_PIX_FMT_BGR24";
        case AV_PIX_FMT_YUV422P:
            return "AV_PIX_FMT_YUV422P";
        case AV_PIX_FMT_YUV444P:
            return "AV_PIX_FMT_YUV444P";
        case AV_PIX_FMT_YUV410P:
            return "AV_PIX_FMT_YUV410P";
        case AV_PIX_FMT_YUV411P:
            return "AV_PIX_FMT_YUV411P";
        case AV_PIX_FMT_GRAY8:
            return "AV_PIX_FMT_GRAY8";
        case AV_PIX_FMT_MONOWHITE:
            return "AV_PIX_FMT_MONOWHITE";
        case AV_PIX_FMT_MONOBLACK:
            return "AV_PIX_FMT_MONOBLACK";
        case AV_PIX_FMT_PAL8:
            return "AV_PIX_FMT_PAL8";
        case AV_PIX_FMT_YUVJ420P:
            return "AV_PIX_FMT_YUVJ420P";
        case AV_PIX_FMT_YUVJ422P:
            return "AV_PIX_FMT_YUVJ422P";
        case AV_PIX_FMT_YUVJ444P:
            return "AV_PIX_FMT_YUVJ444P";
        case AV_PIX_FMT_UYVY422:
            return "AV_PIX_FMT_UYVY422";
        case AV_PIX_FMT_UYYVYY411:
            return "AV_PIX_FMT_UYYVYY411";
        case AV_PIX_FMT_BGR8:
            return "AV_PIX_FMT_BGR8";
        case AV_PIX_FMT_BGR4:
            return "AV_PIX_FMT_BGR4";
        case AV_PIX_FMT_BGR4_BYTE:
            return "AV_PIX_FMT_BGR4_BYTE";
        case AV_PIX_FMT_RGB8:
            return "AV_PIX_FMT_RGB8";
        case AV_PIX_FMT_RGB4:
            return "AV_PIX_FMT_RGB4";
        case AV_PIX_FMT_RGB4_BYTE:
            return "AV_PIX_FMT_RGB4_BYTE";
        case AV_PIX_FMT_NV12:
            return "AV_PIX_FMT_NV12";
        case AV_PIX_FMT_NV21:
            return "AV_PIX_FMT_NV21";
        case AV_PIX_FMT_ARGB:
            return "AV_PIX_FMT_ARGB";
        case AV_PIX_FMT_RGBA:
            return "AV_PIX_FMT_RGBA";
        case AV_PIX_FMT_ABGR:
            return "AV_PIX_FMT_ABGR";
        case AV_PIX_FMT_BGRA:
            return "AV_PIX_FMT_BGRA";
        case AV_PIX_FMT_GRAY16BE:
            return "AV_PIX_FMT_GRAY16BE";
        case AV_PIX_FMT_GRAY16LE:
            return "AV_PIX_FMT_GRAY16LE";
        case AV_PIX_FMT_YUV440P:
            return "AV_PIX_FMT_YUV440P";
        case AV_PIX_FMT_YUVJ440P:
            return "AV_PIX_FMT_YUVJ440P";
        case AV_PIX_FMT_YUVA420P:
            return "AV_PIX_FMT_YUVA420P";
        case AV_PIX_FMT_RGB48BE:
            return "AV_PIX_FMT_RGB48BE";
        case AV_PIX_FMT_RGB48LE:
            return "AV_PIX_FMT_RGB48LE";
        case AV_PIX_FMT_RGB565BE:
            return "AV_PIX_FMT_RGB565BE";
        case AV_PIX_FMT_RGB565LE:
            return "AV_PIX_FMT_RGB565LE";
        case AV_PIX_FMT_RGB555BE:
            return "AV_PIX_FMT_RGB555BE";
        case AV_PIX_FMT_RGB555LE:
            return "AV_PIX_FMT_RGB555LE";
        case AV_PIX_FMT_BGR565BE:
            return "AV_PIX_FMT_BGR565BE";
        case AV_PIX_FMT_BGR565LE:
            return "AV_PIX_FMT_BGR565LE";
        case AV_PIX_FMT_BGR555BE:
            return "AV_PIX_FMT_BGR555BE";
        case AV_PIX_FMT_BGR555LE:
            return "AV_PIX_FMT_BGR555LE";
        case AV_PIX_FMT_VAAPI_MOCO:
            return "AV_PIX_FMT_VAAPI_MOCO";
        case AV_PIX_FMT_VAAPI_IDCT:
            return "AV_PIX_FMT_VAAPI_IDCT";
        case AV_PIX_FMT_VAAPI_VLD:
            return "AV_PIX_FMT_VAAPI_VLD";
        case AV_PIX_FMT_YUV420P16LE:
            return "AV_PIX_FMT_YUV420P16LE";
        case AV_PIX_FMT_YUV420P16BE:
            return "AV_PIX_FMT_YUV420P16BE";
        case AV_PIX_FMT_YUV422P16LE:
            return "AV_PIX_FMT_YUV422P16LE";
        case AV_PIX_FMT_YUV422P16BE:
            return "AV_PIX_FMT_YUV422P16BE";
        case AV_PIX_FMT_YUV444P16LE:
            return "AV_PIX_FMT_YUV444P16LE";
        case AV_PIX_FMT_YUV444P16BE:
            return "AV_PIX_FMT_YUV444P16BE";
        case AV_PIX_FMT_DXVA2_VLD:
            return "AV_PIX_FMT_DXVA2_VLD";
        case AV_PIX_FMT_RGB444LE:
            return "AV_PIX_FMT_RGB444LE";
        case AV_PIX_FMT_RGB444BE:
            return "AV_PIX_FMT_RGB444BE";
        case AV_PIX_FMT_BGR444LE:
            return "AV_PIX_FMT_BGR444LE";
        case AV_PIX_FMT_BGR444BE:
            return "AV_PIX_FMT_BGR444BE";
        case AV_PIX_FMT_YA8:
            return "AV_PIX_FMT_YA8";
        case AV_PIX_FMT_BGR48BE:
            return "AV_PIX_FMT_BGR48BE";
        case AV_PIX_FMT_BGR48LE:
            return "AV_PIX_FMT_BGR48LE";
        case AV_PIX_FMT_YUV420P9BE:
            return "AV_PIX_FMT_YUV420P9BE";
        case AV_PIX_FMT_YUV420P9LE:
            return "AV_PIX_FMT_YUV420P9LE";
        case AV_PIX_FMT_YUV420P10BE:
            return "AV_PIX_FMT_YUV420P10BE";
        case AV_PIX_FMT_YUV420P10LE:
            return "AV_PIX_FMT_YUV420P10LE";
        case AV_PIX_FMT_YUV422P10BE:
            return "AV_PIX_FMT_YUV422P10BE";
        case AV_PIX_FMT_YUV422P10LE:
            return "AV_PIX_FMT_YUV422P10LE";
        case AV_PIX_FMT_YUV444P9BE:
            return "AV_PIX_FMT_YUV444P9BE";
        case AV_PIX_FMT_YUV444P9LE:
            return "AV_PIX_FMT_YUV444P9LE";
        case AV_PIX_FMT_YUV444P10BE:
            return "AV_PIX_FMT_YUV444P10BE";
        case AV_PIX_FMT_YUV444P10LE:
            return "AV_PIX_FMT_YUV444P10LE";
        case AV_PIX_FMT_YUV422P9BE:
            return "AV_PIX_FMT_YUV422P9BE";
        case AV_PIX_FMT_YUV422P9LE:
            return "AV_PIX_FMT_YUV422P9LE";
        case AV_PIX_FMT_GBRP:
            return "AV_PIX_FMT_GBRP";
        case AV_PIX_FMT_GBRP9BE:
            return "AV_PIX_FMT_GBRP9BE";
        case AV_PIX_FMT_GBRP9LE:
            return "AV_PIX_FMT_GBRP9LE";
        case AV_PIX_FMT_GBRP10BE:
            return "AV_PIX_FMT_GBRP10BE";
        case AV_PIX_FMT_GBRP10LE:
            return "AV_PIX_FMT_GBRP10LE";
        case AV_PIX_FMT_GBRP16BE:
            return "AV_PIX_FMT_GBRP16BE";
        case AV_PIX_FMT_GBRP16LE:
            return "AV_PIX_FMT_GBRP16LE";
        case AV_PIX_FMT_YUVA422P:
            return "AV_PIX_FMT_YUVA422P";
        case AV_PIX_FMT_YUVA444P:
            return "AV_PIX_FMT_YUVA444P";
        case AV_PIX_FMT_YUVA420P9BE:
            return "AV_PIX_FMT_YUVA420P9BE";
        case AV_PIX_FMT_YUVA420P9LE:
            return "AV_PIX_FMT_YUVA420P9LE";
        case AV_PIX_FMT_YUVA422P9BE:
            return "AV_PIX_FMT_YUVA422P9BE";
        case AV_PIX_FMT_YUVA422P9LE:
            return "AV_PIX_FMT_YUVA422P9LE";
        case AV_PIX_FMT_YUVA444P9BE:
            return "AV_PIX_FMT_YUVA444P9BE";
        case AV_PIX_FMT_YUVA444P9LE:
            return "AV_PIX_FMT_YUVA444P9LE";
        case AV_PIX_FMT_YUVA420P10BE:
            return "AV_PIX_FMT_YUVA420P10BE";
        case AV_PIX_FMT_YUVA420P10LE:
            return "AV_PIX_FMT_YUVA420P10LE";
        case AV_PIX_FMT_YUVA422P10BE:
            return "AV_PIX_FMT_YUVA422P10BE";
        case AV_PIX_FMT_YUVA422P10LE:
            return "AV_PIX_FMT_YUVA422P10LE";
        case AV_PIX_FMT_YUVA444P10BE:
            return "AV_PIX_FMT_YUVA444P10BE";
        case AV_PIX_FMT_YUVA444P10LE:
            return "AV_PIX_FMT_YUVA444P10LE";
        case AV_PIX_FMT_YUVA420P16BE:
            return "AV_PIX_FMT_YUVA420P16BE";
        case AV_PIX_FMT_YUVA420P16LE:
            return "AV_PIX_FMT_YUVA420P16LE";
        case AV_PIX_FMT_YUVA422P16BE:
            return "AV_PIX_FMT_YUVA422P16BE";
        case AV_PIX_FMT_YUVA422P16LE:
            return "AV_PIX_FMT_YUVA422P16LE";
        case AV_PIX_FMT_YUVA444P16BE:
            return "AV_PIX_FMT_YUVA444P16BE";
        case AV_PIX_FMT_YUVA444P16LE:
            return "AV_PIX_FMT_YUVA444P16LE";
        case AV_PIX_FMT_VDPAU:
            return "AV_PIX_FMT_VDPAU";
        case AV_PIX_FMT_XYZ12LE:
            return "AV_PIX_FMT_XYZ12LE";
        case AV_PIX_FMT_XYZ12BE:
            return "AV_PIX_FMT_XYZ12BE";
        case AV_PIX_FMT_NV16:
            return "AV_PIX_FMT_NV16";
        case AV_PIX_FMT_NV20LE:
            return "AV_PIX_FMT_NV20LE";
        case AV_PIX_FMT_NV20BE:
            return "AV_PIX_FMT_NV20BE";
        case AV_PIX_FMT_RGBA64BE:
            return "AV_PIX_FMT_RGBA64BE";
        case AV_PIX_FMT_RGBA64LE:
            return "AV_PIX_FMT_RGBA64LE";
        case AV_PIX_FMT_BGRA64BE:
            return "AV_PIX_FMT_BGRA64BE";
        case AV_PIX_FMT_BGRA64LE:
            return "AV_PIX_FMT_BGRA64LE";
        case AV_PIX_FMT_YVYU422:
            return "AV_PIX_FMT_YVYU422";
        case AV_PIX_FMT_YA16BE:
            return "AV_PIX_FMT_YA16BE";
        case AV_PIX_FMT_YA16LE:
            return "AV_PIX_FMT_YA16LE";
        case AV_PIX_FMT_GBRAP:
            return "AV_PIX_FMT_GBRAP";
        case AV_PIX_FMT_GBRAP16BE:
            return "AV_PIX_FMT_GBRAP16BE";
        case AV_PIX_FMT_GBRAP16LE:
            return "AV_PIX_FMT_GBRAP16LE";
        case AV_PIX_FMT_QSV:
            return "AV_PIX_FMT_QSV";
        case AV_PIX_FMT_MMAL:
            return "AV_PIX_FMT_MMAL";
        case AV_PIX_FMT_D3D11VA_VLD:
            return "AV_PIX_FMT_D3D11VA_VLD";
        case AV_PIX_FMT_CUDA:
            return "AV_PIX_FMT_CUDA";
        case AV_PIX_FMT_0RGB:
            return "AV_PIX_FMT_0RGB";
        case AV_PIX_FMT_RGB0:
            return "AV_PIX_FMT_RGB0";
        case AV_PIX_FMT_0BGR:
            return "AV_PIX_FMT_0BGR";
        case AV_PIX_FMT_BGR0:
            return "AV_PIX_FMT_BGR0";
        case AV_PIX_FMT_YUV420P12BE:
            return "AV_PIX_FMT_YUV420P12BE";
        case AV_PIX_FMT_YUV420P12LE:
            return "AV_PIX_FMT_YUV420P12LE";
        case AV_PIX_FMT_YUV420P14BE:
            return "AV_PIX_FMT_YUV420P14BE";
        case AV_PIX_FMT_YUV420P14LE:
            return "AV_PIX_FMT_YUV420P14LE";
        case AV_PIX_FMT_YUV422P12BE:
            return "AV_PIX_FMT_YUV422P12BE";
        case AV_PIX_FMT_YUV422P12LE:
            return "AV_PIX_FMT_YUV422P12LE";
        case AV_PIX_FMT_YUV422P14BE:
            return "AV_PIX_FMT_YUV422P14BE";
        case AV_PIX_FMT_YUV422P14LE:
            return "AV_PIX_FMT_YUV422P14LE";
        case AV_PIX_FMT_YUV444P12BE:
            return "AV_PIX_FMT_YUV444P12BE";
        case AV_PIX_FMT_YUV444P12LE:
            return "AV_PIX_FMT_YUV444P12LE";
        case AV_PIX_FMT_YUV444P14BE:
            return "AV_PIX_FMT_YUV444P14BE";
        case AV_PIX_FMT_YUV444P14LE:
            return "AV_PIX_FMT_YUV444P14LE";
        case AV_PIX_FMT_GBRP12BE:
            return "AV_PIX_FMT_GBRP12BE";
        case AV_PIX_FMT_GBRP12LE:
            return "AV_PIX_FMT_GBRP12LE";
        case AV_PIX_FMT_GBRP14BE:
            return "AV_PIX_FMT_GBRP14BE";
        case AV_PIX_FMT_GBRP14LE:
            return "AV_PIX_FMT_GBRP14LE";
        case AV_PIX_FMT_YUVJ411P:
            return "AV_PIX_FMT_YUVJ411P";
        case AV_PIX_FMT_BAYER_BGGR8:
            return "AV_PIX_FMT_BAYER_BGGR8";
        case AV_PIX_FMT_BAYER_RGGB8:
            return "AV_PIX_FMT_BAYER_RGGB8";
        case AV_PIX_FMT_BAYER_GBRG8:
            return "AV_PIX_FMT_BAYER_GBRG8";
        case AV_PIX_FMT_BAYER_GRBG8:
            return "AV_PIX_FMT_BAYER_GRBG8";
        case AV_PIX_FMT_BAYER_BGGR16LE:
            return "AV_PIX_FMT_BAYER_BGGR16LE";
        case AV_PIX_FMT_BAYER_BGGR16BE:
            return "AV_PIX_FMT_BAYER_BGGR16BE";
        case AV_PIX_FMT_BAYER_RGGB16LE:
            return "AV_PIX_FMT_BAYER_RGGB16LE";
        case AV_PIX_FMT_BAYER_RGGB16BE:
            return "AV_PIX_FMT_BAYER_RGGB16BE";
        case AV_PIX_FMT_BAYER_GBRG16LE:
            return "AV_PIX_FMT_BAYER_GBRG16LE";
        case AV_PIX_FMT_BAYER_GBRG16BE:
            return "AV_PIX_FMT_BAYER_GBRG16BE";
        case AV_PIX_FMT_BAYER_GRBG16LE:
            return "AV_PIX_FMT_BAYER_GRBG16LE";
        case AV_PIX_FMT_BAYER_GRBG16BE:
            return "AV_PIX_FMT_BAYER_GRBG16BE";
        case AV_PIX_FMT_XVMC:
            return "AV_PIX_FMT_XVMC";
        case AV_PIX_FMT_YUV440P10LE:
            return "AV_PIX_FMT_YUV440P10LE";
        case AV_PIX_FMT_YUV440P10BE:
            return "AV_PIX_FMT_YUV440P10BE";
        case AV_PIX_FMT_YUV440P12LE:
            return "AV_PIX_FMT_YUV440P12LE";
        case AV_PIX_FMT_YUV440P12BE:
            return "AV_PIX_FMT_YUV440P12BE";
        case AV_PIX_FMT_AYUV64LE:
            return "AV_PIX_FMT_AYUV64LE";
        case AV_PIX_FMT_AYUV64BE:
            return "AV_PIX_FMT_AYUV64BE";
        case AV_PIX_FMT_VIDEOTOOLBOX:
            return "AV_PIX_FMT_VIDEOTOOLBOX";
        case AV_PIX_FMT_P010LE:
            return "AV_PIX_FMT_P010LE";
        case AV_PIX_FMT_P010BE:
            return "AV_PIX_FMT_P010BE";
        case AV_PIX_FMT_GBRAP12BE:
            return "AV_PIX_FMT_GBRAP12BE";
        case AV_PIX_FMT_GBRAP12LE:
            return "AV_PIX_FMT_GBRAP12LE";
        case AV_PIX_FMT_GBRAP10BE:
            return "AV_PIX_FMT_GBRAP10BE";
        case AV_PIX_FMT_GBRAP10LE:
            return "AV_PIX_FMT_GBRAP10LE";
        case AV_PIX_FMT_MEDIACODEC:
            return "AV_PIX_FMT_MEDIACODEC";
        case AV_PIX_FMT_GRAY12BE:
            return "AV_PIX_FMT_GRAY12BE";
        case AV_PIX_FMT_GRAY12LE:
            return "AV_PIX_FMT_GRAY12LE";
        case AV_PIX_FMT_GRAY10BE:
            return "AV_PIX_FMT_GRAY10BE";
        case AV_PIX_FMT_GRAY10LE:
            return "AV_PIX_FMT_GRAY10LE";
        case AV_PIX_FMT_P016LE:
            return "AV_PIX_FMT_P016LE";
        case AV_PIX_FMT_P016BE:
            return "AV_PIX_FMT_P016BE";
        case AV_PIX_FMT_D3D11:
            return "AV_PIX_FMT_D3D11";
        case AV_PIX_FMT_GRAY9BE:
            return "AV_PIX_FMT_GRAY9BE";
        case AV_PIX_FMT_GRAY9LE:
            return "AV_PIX_FMT_GRAY9LE";
        case AV_PIX_FMT_GBRPF32BE:
            return "AV_PIX_FMT_GBRPF32BE";
        case AV_PIX_FMT_GBRPF32LE:
            return "AV_PIX_FMT_GBRPF32LE";
        case AV_PIX_FMT_GBRAPF32BE:
            return "AV_PIX_FMT_GBRAPF32BE";
        case AV_PIX_FMT_GBRAPF32LE:
            return "AV_PIX_FMT_GBRAPF32LE";
        case AV_PIX_FMT_DRM_PRIME:
            return "AV_PIX_FMT_DRM_PRIME";
        case AV_PIX_FMT_OPENCL:
            return "AV_PIX_FMT_OPENCL";
        default:
            return wxString::Format("Unknown Format %d", format);
    }
}

static enum AVPixelFormat get_hw_format(AVCodecContext *ctx, const enum AVPixelFormat *formats) {
    const enum AVPixelFormat *p;
    wxLogInfo("Available Formats: ");
    for (p = formats; *p != -1; p++) {
        wxLogInfo("    %s", pixelFormatToString(*p));
    }

    for (p = formats; *p != -1; p++) {
        if (*p == AV_PIX_FMT_D3D11) {
            wxLogInfo("Using Decoder Format %s", pixelFormatToString(*p));
            return *p;
        }
//        if (*p == ((CodecOpaqueStruct *) ctx->opaque)->hwPixexlFormat) {
//            wxLogInfo("Selected Pixel Format %s", pixelFormatToString(*p));
//            if (*p == AV_PIX_FMT_D3D11) {
//                if (ctx->hw_device_ctx != nullptr) {
//                    AVBufferRef* hwFrameCtx;
//                    if (avcodec_get_hw_frames_parameters(ctx, ctx->hw_device_ctx, *p, &hwFrameCtx) < 0) {
//                        wxLogInfo("Failed to alloc hw frame context");
//                        return *p;
//                    }
//
//                    if (av_hwframe_ctx_init(hwFrameCtx) < 0) {
//                        wxLogInfo("Failed to init hw frame context");
//                        return *p;
//                    }
//                    ctx->hw_frames_ctx = av_buffer_ref(hwFrameCtx);
//                }
//            }
//            return *p;
//        }
//        return *p;
    }
    return AV_PIX_FMT_NONE;
}

bool VP::VideoDecoder::LoadVideo(wxString path) {
    if (!wxFileExists(path)) {
        return false;
    }

    int result;
    result = avformat_open_input(&formatContext, path.c_str().AsChar(), nullptr, nullptr);
    if (result < 0) {
        char errorBuff[AV_ERROR_MAX_STRING_SIZE];
        int r = av_strerror(result, &errorBuff[0], AV_ERROR_MAX_STRING_SIZE);
        wxLogInfo("Failed to load video: %d %s", r == 0 ? result : r, &errorBuff[0]);
        return false;
    }

    result = avformat_find_stream_info(formatContext, nullptr);
    if (result < 0) {
        char errorBuff[AV_ERROR_MAX_STRING_SIZE];
        int r = av_strerror(result, &errorBuff[0], AV_ERROR_MAX_STRING_SIZE);
        wxLogInfo("Failed to open stream: %d %s", r == 0 ? result : r, &errorBuff[0]);
        return false;
    }

    int stream = av_find_best_stream(formatContext, AVMEDIA_TYPE_VIDEO, -1, -1, &codec, 0);
    if (stream < 0) {
        wxLogInfo(
                    "Failed to find video stream %s\n",
                    stream == AVERROR_DECODER_NOT_FOUND ? "Failed to find decoder" : stream == AVERROR_STREAM_NOT_FOUND
                                                                                     ? "Stream not found" : "Unknown"
            );
        return false;
    }
    videoStreamIndex = stream;

    if (!codec) {
        wxLogInfo("Failed to find codec");
        return false;
    }
    codecContext = avcodec_alloc_context3(codec);

    result = avcodec_parameters_to_context(codecContext, formatContext->streams[videoStreamIndex]->codecpar);
    if (result < 0) {
        char errorBuff[AV_ERROR_MAX_STRING_SIZE];
        int r = av_strerror(result, &errorBuff[0], AV_ERROR_MAX_STRING_SIZE);
        wxLogInfo("Failed to copy codec parameters to codec: %d %s", r == 0 ? result : r, &errorBuff[0]);
        return false;
    }

    AVPixelFormat hwPixelFormat = AV_PIX_FMT_NONE;
    AVHWDeviceType hwDeviceType = AV_HWDEVICE_TYPE_NONE;
    int methods = 0;

    for (int hwConfigIndex = 0;; hwConfigIndex++) {
        const AVCodecHWConfig *config = avcodec_get_hw_config(codec, hwConfigIndex);
        if (!config) {
            break;
        }
        if (config->methods & AV_CODEC_HW_CONFIG_METHOD_AD_HOC) {
            continue;
        }
        if (!(config->methods & AV_CODEC_HW_CONFIG_METHOD_INTERNAL)) {
            // Second Options
            methods = config->methods;
            hwPixelFormat = config->pix_fmt;
            hwDeviceType = config->device_type;
            break;
        }
    }
//    auto *opaqueStruct = new CodecOpaqueStruct();
//    codecContext->opaque = opaqueStruct;
//    opaqueStruct->hwPixexlFormat = hwPixelFormat;
//    codecContext->pix_fmt = hwPixelFormat;
    av_opt_set_int(codecContext, "refcounted_frames", 1, AV_OPT_SEARCH_CHILDREN);
    av_opt_set_int(codecContext, "thread_safe_callbacks", 0, AV_OPT_SEARCH_CHILDREN);

    if (hwDeviceType != AV_HWDEVICE_TYPE_NONE) {
        if (methods & AV_CODEC_HW_CONFIG_METHOD_HW_FRAMES_CTX) {
            codecContext->get_format = get_hw_format;
        }
        if (methods & AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX) {
            if (av_hwdevice_ctx_create(&hwDeviceContext, hwDeviceType, nullptr, nullptr, 0) < 0) {
                wxLogInfo("Failed to create hardware context");
                return false;
            }

            wxLogInfo("Using Hardware Decoder %s", av_hwdevice_get_type_name(hwDeviceType));
            wxLogInfo("Using Pixel Format %s", pixelFormatToString(hwPixelFormat));
            if (av_hwdevice_ctx_init(hwDeviceContext) < 0) {
                wxLogInfo("Failed to initialise Hardware context");
                return false;
            }
            codecContext->hw_device_ctx = av_buffer_ref(hwDeviceContext);
        }
    }

    this->codecContext->hwaccel_flags = AV_HWACCEL_FLAG_IGNORE_LEVEL/* | AV_HWACCEL_FLAG_ALLOW_PROFILE_MISMATCH*/;


    this->codecContext->thread_count = wxThread::GetCPUCount() * 2;
    this->codecContext->thread_type = FF_THREAD_SLICE;

//    codecContext->lowres = 1;

    result = avcodec_open2(codecContext, codec, nullptr);
    if (result < 0) {
        char errorBuff[AV_ERROR_MAX_STRING_SIZE];
        int r = av_strerror(result, &errorBuff[0], AV_ERROR_MAX_STRING_SIZE);
        wxLogInfo("Failed to open codec: %d %s", r == 0 ? result : r, &errorBuff[0]);
        return false;
    }


    numBytes = 0;
    ret = 0;

    for (auto &i : rgbLines) {
        i = 0;
    }
    for (auto &i : rgbBuffer) {
        i = nullptr;
    }

    numBytes = av_image_get_buffer_size(
            outputFormat, codecContext->width,
            codecContext->height, 1
    );
//    swsContext = sws_getContext(
//            codecContext->width, codecContext->height,
//            codecContext->pix_fmt, codecContext->width,
//            codecContext->height, outputFormat, SWS_BICUBLIN, nullptr,
//            nullptr, nullptr
//    );

    rgbLines[0] = 1920 * 3;
    rgbBuffer[0] = (uint8_t *) av_malloc(numBytes + 16 + sizeof(uint8_t));

    if ((packet = av_packet_alloc()) == nullptr) {
        return false;
    }

//    if (av_new_packet(&packet, 0) < 0) {
//        return false;
//    }

    if ((yuvFrame = av_frame_alloc()) == nullptr) {
        return false;
    }

    if ((swFrame = av_frame_alloc()) == nullptr) {
        return false;
    }

    last_frame_decoded = -1;

    return true;
}

void VP::VideoDecoder::Play() {
    this->playing = true;
}

void VP::VideoDecoder::Pause() {
    this->playing = false;
}

void VP::VideoDecoder::Stop() {
    this->playing = false;
    avcodec_flush_buffers(codecContext);
    avformat_flush(formatContext);
    av_seek_frame(formatContext, videoStreamIndex, 0, AVSEEK_FLAG_FRAME);
}

bool VP::VideoDecoder::IsPlaying() {
    return playing;
}

bool VP::VideoDecoder::IsFinished() {
    return finished;
}

bool VP::VideoDecoder::HasFrame() {
    if (this->playing) {
        AVFrame *hwFrame = nullptr;
        int r;
        while ((r = av_read_frame(formatContext, packet)) >= 0) {
            if (packet->stream_index == videoStreamIndex) {
                ret = avcodec_send_packet(codecContext, packet);
                av_packet_unref(packet);
                if (ret < 0) {
                    char errorBuff[AV_ERROR_MAX_STRING_SIZE];
                    int e = av_strerror(ret, &errorBuff[0], AV_ERROR_MAX_STRING_SIZE);
                    wxLogMessage("Failed to send packet: %d %s", e == 0 ? ret : e, &errorBuff[0]);
                    playing = false;
                    finished = true;
                    return false;
                }

                while (ret >= 0) {

                    av_frame_unref(yuvFrame);
                    av_frame_unref(swFrame);

                    ret = avcodec_receive_frame(codecContext, yuvFrame);

                    if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                        break;
                    } else if (ret < 0) {
                        playing = false;
                        finished = true;
                        return false;
                    } else {
                        if (yuvFrame->format == AV_PIX_FMT_D3D11) {
                            if (av_hwframe_transfer_data(swFrame, yuvFrame, 0) < 0) {
                                wxLogMessage("Failed hw decode");
                                hwFrame = yuvFrame;
                            } else {
                                if (av_frame_copy_props(swFrame, yuvFrame) < 0) {
                                    wxLogMessage("Could not copy properties");
                                }
                                hwFrame = swFrame;
                            }
                        } else {
                            hwFrame = yuvFrame;
                        }

                        // copy frame
                        if (hwFrame->coded_picture_number != last_frame_decoded) {
                            swsContext = sws_getCachedContext(swsContext, hwFrame->width, hwFrame->height,
                                                              static_cast<AVPixelFormat>(hwFrame->format),
                                                              codecContext->width,
                                                              codecContext->height, outputFormat,
                                                              SWS_FAST_BILINEAR, nullptr,
                                                              nullptr, nullptr);

                            sws_scale(
                                    swsContext, reinterpret_cast<const uint8_t *const *>(hwFrame->data),
                                    hwFrame->linesize, 0, codecContext->height,
                                    rgbBuffer, rgbLines
                            );
                        }
                        last_frame_decoded = hwFrame->coded_picture_number;

                        av_frame_unref(hwFrame);
                        return true;
                    }
                }
            }
            av_packet_unref(packet);
        }

        if (r < 0) {
            playing = false;
            finished = true;
        }

        return false;
    }
    return false;
}

void VP::VideoDecoder::NextFrame(GLuint *rgb) {
// move data to texture;;
    GLenum imageFormat = GL_RGB;

    if (*rgb <= 0) {
        glGenTextures(1, rgb);
        wxLogMessage("RGBA Video texture id %d", *rgb);
        glCheckError();
        glBindTexture(GL_TEXTURE_2D, *rgb);
        glCheckError();
//            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glCheckError();

        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                imageFormat,
                codecContext->width,
                codecContext->height,
                0,
                imageFormat,
                GL_UNSIGNED_BYTE,
                rgbBuffer[0]
        );
        glCheckError();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glCheckError();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glCheckError();

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glCheckError();
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glCheckError();
    } else {
        glBindTexture(GL_TEXTURE_2D, *rgb);
        glTexSubImage2D(
                GL_TEXTURE_2D,
                0,
                0,
                0,
                codecContext->width,
                codecContext->height,
                imageFormat,
                GL_UNSIGNED_BYTE,
                rgbBuffer[0]
        );
    }
}
