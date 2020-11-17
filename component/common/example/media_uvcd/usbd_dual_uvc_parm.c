#include "core/inc/usb_config.h"
#include "core/inc/usb_composite.h"
#include "osdep_service.h"

#include "uvc_os_wrap_via_osdep_api.h"
#include "usb.h"
#include "basic_types.h"
#include "video.h"
#include "dual_uvc/inc/usbd_uvc_desc.h"
#include "example_media_dual_uvcd.h"

#if LIB_UVCD_DUAL

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(H264_JPEG)
struct UVC_INPUT_HEADER_DESCRIPTOR(1, 4) uvc_input_header = { 
.bLength = UVC_DT_INPUT_HEADER_SIZE(1,2),
.bDescriptorType = USB_DT_CS_INTERFACE,
.bDescriptorSubType = UVC_VS_INPUT_HEADER,
.bNumFormats  = 1,
.wTotalLength  = 0,
.bEndpointAddress  = 0,
.bmInfo  = 0,
.bTerminalLink  = 4,
.bStillCaptureMethod  = 0,
.bTriggerSupport  = 0,
.bTriggerUsage  = 0,
.bControlSize  = 1,
.bmaControls[0][0]  = 0,
.bmaControls[1][0]  = 0,
.bmaControls[2][0]  = 0,
.bmaControls[3][0]  = 0,
};
struct UVC_INPUT_HEADER_DESCRIPTOR(1, 4) uvc_input_two_header = { 
.bLength = UVC_DT_INPUT_HEADER_SIZE(1,2),
.bDescriptorType = USB_DT_CS_INTERFACE,
.bDescriptorSubType = UVC_VS_INPUT_HEADER,
.bNumFormats  = 1,
.wTotalLength  = 0,
.bEndpointAddress  = 0,
.bmInfo  = 0,
.bTerminalLink  = 5,
.bStillCaptureMethod  = 0,
.bTriggerSupport  = 0,
.bTriggerUsage  = 0,
.bControlSize  = 1,
.bmaControls[0][0]  = 0,
.bmaControls[1][0]  = 0,
.bmaControls[2][0]  = 0,
.bmaControls[3][0]  = 0,
};
struct UVC_INPUT_HEADER_DESCRIPTOR(1, 4) uvc_input_header_ext = { 
.bLength = UVC_DT_INPUT_HEADER_SIZE(1,2),
.bDescriptorType = USB_DT_CS_INTERFACE,
.bDescriptorSubType = UVC_VS_INPUT_HEADER,
.bNumFormats  = 1,
.wTotalLength  = 0,
.bEndpointAddress  = 0,
.bmInfo  = 0,
.bTerminalLink  = 4,
.bStillCaptureMethod  = 0,
.bTriggerSupport  = 0,
.bTriggerUsage  = 0,
.bControlSize  = 1,
.bmaControls[0][0]  = 0,
.bmaControls[1][0]  = 0,
.bmaControls[2][0]  = 0,
.bmaControls[3][0]  = 0,
};
struct uvc_format_framebased uvc_format_h264 = { 
.bLength = UVC_DT_FORMAT_FRAMEBASED_SIZE,
.bDescriptorType = USB_DT_CS_INTERFACE,
.bDescriptorSubType = UVC_VS_FORMAT_FRAME_BASED,
.bFormatIndex  = 1,
.bNumFrameDescriptors  = 1,
.guidFormat  = { 'H',  '2',  '6',  '4', 0x00, 0x00, 0x10, 0x00,0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71},
.bBitsPerPixel  = 12,
.bDefaultFrameIndex  = 1,
.bAspectRatioX  = 1,
.bAspectRatioY  = 0,
.bmInterfaceFlags  = 0,
.bCopyProtect  = 0,
.bVariableSize  = 1,
};
struct uvc_format_mjpeg uvc_format_mjpg = { 
.bLength = UVC_DT_FORMAT_MJPEG_SIZE,
.bDescriptorType = USB_DT_CS_INTERFACE,
.bDescriptorSubType = UVC_VS_FORMAT_MJPEG,
.bFormatIndex  = 1,//Devin
.bNumFrameDescriptors  = 1,
.bmFlags  = 1,
.bDefaultFrameIndex  = 1,
.bAspectRatioX  = 0,
.bAspectRatioY  = 0,
.bmInterfaceFlags  = 0,
.bCopyProtect  = 0,
};
struct UVC_FRAME_FRAMEBASED(3) uvc_frame_h264_1080p = {
.bLength = UVC_DT_FRAME_FRAMEBASED_SIZE(3),
.bDescriptorType = USB_DT_CS_INTERFACE,
.bDescriptorSubType = UVC_VS_FRAME_FRAME_BASED,
.bFrameIndex  = 1,
.bmCapabilities  = 0,
.wWidth  = cpu_to_le16(1920),
.wHeight  = cpu_to_le16(1080),
.dwMinBitRate  = cpu_to_le32(18432000),
.dwMaxBitRate  = cpu_to_le32(55296000),
.dwDefaultFrameInterval  = cpu_to_le32(333333),
.bFrameIntervalType  = 3,
.dwBytesPerLine  = 0,
.dwFrameInterval[0]  = cpu_to_le32(333333),
.dwFrameInterval[1]  = cpu_to_le32(666666),
.dwFrameInterval[2]  = cpu_to_le32(1000000),
};
struct UVC_FRAME_MJPEG(3) uvc_frame_mjpg_360p = {
.bLength = UVC_DT_FRAME_MJPEG_SIZE(3),
.bDescriptorType = USB_DT_CS_INTERFACE,
.bDescriptorSubType = UVC_VS_FRAME_MJPEG,
.bFrameIndex  = 1,
.bmCapabilities  = 0,
.wWidth  = cpu_to_le16(640),
.wHeight  = cpu_to_le16(360),
.dwMinBitRate  = cpu_to_le32(18432000),
.dwMaxBitRate  = cpu_to_le32(55296000),
.dwMaxVideoFrameBufferSize  = cpu_to_le32(460800),
.dwDefaultFrameInterval  = cpu_to_le32(333333),
.bFrameIntervalType  = 3,
.dwFrameInterval[0]  = cpu_to_le32(333333),
.dwFrameInterval[1]  = cpu_to_le32(666666),
.dwFrameInterval[2]  = cpu_to_le32(1000000),
};
struct uvc_descriptor_header *uvc_fs_streaming_cls[] = { 
(struct uvc_descriptor_header *) &uvc_input_header, 
(struct uvc_descriptor_header *)  &uvc_format_h264,
(struct uvc_descriptor_header *)  &uvc_frame_h264_1080p,
(struct uvc_descriptor_header *) &uvc_color_matching, 
NULL,
};
struct uvc_descriptor_header *uvc_fs_streaming_cls_ext[] = { 
(struct uvc_descriptor_header *) &uvc_input_header_ext,
(struct uvc_descriptor_header *)  &uvc_format_h264,
(struct uvc_descriptor_header *)  &uvc_frame_h264_1080p,
(struct uvc_descriptor_header *) &uvc_color_matching, 
NULL,
};
struct uvc_descriptor_header *uvc_hs_streaming_cls[] = { 
(struct uvc_descriptor_header *) &uvc_input_header, 
(struct uvc_descriptor_header *)  &uvc_format_h264,
(struct uvc_descriptor_header *)  &uvc_frame_h264_1080p,
(struct uvc_descriptor_header *) &uvc_color_matching, 
NULL,
};
struct uvc_descriptor_header *uvc_hs_streaming_cls_ext[] = { 
(struct uvc_descriptor_header *) &uvc_input_header_ext,
(struct uvc_descriptor_header *)  &uvc_format_h264,
(struct uvc_descriptor_header *)  &uvc_frame_h264_1080p,
(struct uvc_descriptor_header *) &uvc_color_matching, 
NULL,
};

struct usb_descriptor_header *usbd_uvc_descriptors_FS[] = { 
(struct usb_descriptor_header *) &uvc_iad, 
(struct usb_descriptor_header *) &uvc_control_intf, 
(struct usb_descriptor_header *) &uvc_control_header, 
(struct usb_descriptor_header *) &uvc_camera_terminal, 
(struct usb_descriptor_header *) &uvc_processing, 
(struct usb_descriptor_header *) &uvc_extension_unit, 
(struct usb_descriptor_header *) &uvc_output_terminal, 
(struct usb_descriptor_header *) &uvc_output_ext_terminal, 
(struct usb_descriptor_header *) &uvc_control_ep, 
(struct usb_descriptor_header *) &uvc_control_cs_ep, 
(struct usb_descriptor_header *) &uvc_streaming_intf_alt0, 

(struct usb_descriptor_header *) &uvc_input_header, 
(struct usb_descriptor_header *)  &uvc_format_mjpg,
(struct usb_descriptor_header *) &uvc_color_matching, 
(struct usb_descriptor_header *) &uvc_hs_streaming_ep,
(struct usb_descriptor_header *) &uvc_streaming_intf_two_alt0,
(struct usb_descriptor_header *) &uvc_input_two_header,
(struct usb_descriptor_header *)  &uvc_format_h264,
(struct usb_descriptor_header *)  &uvc_frame_h264_1080p,
(struct usb_descriptor_header *) &uvc_color_matching, 
(struct usb_descriptor_header *) &uvc_hs_streaming_ep_ext,
NULL,

};
struct usb_descriptor_header *usbd_uvc_descriptors_HS[] = { 
(struct usb_descriptor_header *) &uvc_iad, 
(struct usb_descriptor_header *) &uvc_control_intf, 
(struct usb_descriptor_header *) &uvc_control_header, 
(struct usb_descriptor_header *) &uvc_camera_terminal, 
(struct usb_descriptor_header *) &uvc_processing, 
(struct usb_descriptor_header *) &uvc_extension_unit, 
(struct usb_descriptor_header *) &uvc_output_terminal, 
(struct usb_descriptor_header *) &uvc_output_ext_terminal,
(struct usb_descriptor_header *) &uvc_control_ep, 
(struct usb_descriptor_header *) &uvc_control_cs_ep, 
(struct usb_descriptor_header *) &uvc_streaming_intf_alt0, 
(struct usb_descriptor_header *) &uvc_input_header, 
(struct usb_descriptor_header *)  &uvc_format_mjpg,
(struct usb_descriptor_header *)  &uvc_frame_mjpg_360p, 
(struct usb_descriptor_header *) &uvc_color_matching, 
(struct usb_descriptor_header *) &uvc_hs_streaming_ep,
(struct usb_descriptor_header *) &uvc_streaming_intf_two_alt0,
(struct usb_descriptor_header *) &uvc_input_two_header,
(struct usb_descriptor_header *)  &uvc_format_h264,
(struct usb_descriptor_header *)  &uvc_frame_h264_1080p,
(struct usb_descriptor_header *) &uvc_color_matching,  
(struct usb_descriptor_header *) &uvc_hs_streaming_ep_ext,
NULL,
};

struct uvc_frame_info uvc_frames_h264[] = {
{ 1920 ,1080, { VALUE_FPS(30), VALUE_FPS(15), VALUE_FPS(10), 0 },},
{ 0, 0, { 0, }, },
};
struct uvc_frame_info uvc_frames_mjpg[] = {
{ 640 ,360, { VALUE_FPS(30), VALUE_FPS(15), VALUE_FPS(10), 0 },},
{ 0, 0, { 0, }, },
};

struct uvc_format_info uvc_formats_ext[] = {
{ FORMAT_TYPE_H264, uvc_frames_h264 },
};
struct uvc_format_info uvc_formats[] = {
{ FORMAT_TYPE_MJPEG, uvc_frames_mjpg },
};
#elif defined(H264_NV12)
struct UVC_INPUT_HEADER_DESCRIPTOR(1, 4) uvc_input_header = { 
.bLength = UVC_DT_INPUT_HEADER_SIZE(1,2),
.bDescriptorType = USB_DT_CS_INTERFACE,
.bDescriptorSubType = UVC_VS_INPUT_HEADER,
.bNumFormats  = 1,
.wTotalLength  = 0,
.bEndpointAddress  = 0,
.bmInfo  = 0,
.bTerminalLink  = 4,
.bStillCaptureMethod  = 0,
.bTriggerSupport  = 0,
.bTriggerUsage  = 0,
.bControlSize  = 1,
.bmaControls[0][0]  = 0,
.bmaControls[1][0]  = 0,
.bmaControls[2][0]  = 0,
.bmaControls[3][0]  = 0,
};
struct UVC_INPUT_HEADER_DESCRIPTOR(1, 4) uvc_input_two_header = { 
.bLength = UVC_DT_INPUT_HEADER_SIZE(1,2),
.bDescriptorType = USB_DT_CS_INTERFACE,
.bDescriptorSubType = UVC_VS_INPUT_HEADER,
.bNumFormats  = 1,
.wTotalLength  = 0,
.bEndpointAddress  = 0,
.bmInfo  = 0,
.bTerminalLink  = 5,
.bStillCaptureMethod  = 0,
.bTriggerSupport  = 0,
.bTriggerUsage  = 0,
.bControlSize  = 1,
.bmaControls[0][0]  = 0,
.bmaControls[1][0]  = 0,
.bmaControls[2][0]  = 0,
.bmaControls[3][0]  = 0,
};
struct UVC_INPUT_HEADER_DESCRIPTOR(1, 4) uvc_input_header_ext = { 
.bLength = UVC_DT_INPUT_HEADER_SIZE(1,2),
.bDescriptorType = USB_DT_CS_INTERFACE,
.bDescriptorSubType = UVC_VS_INPUT_HEADER,
.bNumFormats  = 1,
.wTotalLength  = 0,
.bEndpointAddress  = 0,
.bmInfo  = 0,
.bTerminalLink  = 4,
.bStillCaptureMethod  = 0,
.bTriggerSupport  = 0,
.bTriggerUsage  = 0,
.bControlSize  = 1,
.bmaControls[0][0]  = 0,
.bmaControls[1][0]  = 0,
.bmaControls[2][0]  = 0,
.bmaControls[3][0]  = 0,
};
struct uvc_format_framebased uvc_format_h264 = { 
.bLength = UVC_DT_FORMAT_FRAMEBASED_SIZE,
.bDescriptorType = USB_DT_CS_INTERFACE,
.bDescriptorSubType = UVC_VS_FORMAT_FRAME_BASED,
.bFormatIndex  = 1,
.bNumFrameDescriptors  = 1,
.guidFormat  = { 'H',  '2',  '6',  '4', 0x00, 0x00, 0x10, 0x00,0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71},
.bBitsPerPixel  = 12,
.bDefaultFrameIndex  = 1,
.bAspectRatioX  = 1,
.bAspectRatioY  = 0,
.bmInterfaceFlags  = 0,
.bCopyProtect  = 0,
.bVariableSize  = 1,
};
struct uvc_format_uncompressed uvc_format_nv12 = {
.bLength		= UVC_DT_FORMAT_UNCOMPRESSED_SIZE,
.bDescriptorType	= USB_DT_CS_INTERFACE,
.bDescriptorSubType	= UVC_VS_FORMAT_UNCOMPRESSED,
.bFormatIndex		= 1,
.bNumFrameDescriptors	= 1,
.guidFormat		=
{ 'N',  'V',  '1',  '2', 0x00, 0x00, 0x10, 0x00,
0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71},
.bBitsPerPixel		= 12,
.bDefaultFrameIndex	= 1,
.bAspectRatioX		= 0,
.bAspectRatioY		= 0,
.bmInterfaceFlags	= 0,
.bCopyProtect		= 0,
};
struct UVC_FRAME_FRAMEBASED(3) uvc_frame_h264_1080p = {
.bLength = UVC_DT_FRAME_FRAMEBASED_SIZE(3),
.bDescriptorType = USB_DT_CS_INTERFACE,
.bDescriptorSubType = UVC_VS_FRAME_FRAME_BASED,
.bFrameIndex  = 1,
.bmCapabilities  = 0,
.wWidth  = cpu_to_le16(1920),
.wHeight  = cpu_to_le16(1080),
.dwMinBitRate  = cpu_to_le32(18432000),
.dwMaxBitRate  = cpu_to_le32(55296000),
.dwDefaultFrameInterval  = cpu_to_le32(333333),
.bFrameIntervalType  = 3,
.dwBytesPerLine  = 0,
.dwFrameInterval[0]  = cpu_to_le32(333333),
.dwFrameInterval[1]  = cpu_to_le32(666666),
.dwFrameInterval[2]  = cpu_to_le32(1000000),
};
struct UVC_FRAME_UNCOMPRESSED(3) uvc_frame_yuv_360p = {
.bLength		= UVC_DT_FRAME_UNCOMPRESSED_SIZE(3),
.bDescriptorType	= USB_DT_CS_INTERFACE,
.bDescriptorSubType	= UVC_VS_FRAME_UNCOMPRESSED,
.bFrameIndex		= 1,
.bmCapabilities		= 0,
.wWidth			= cpu_to_le16(640),
.wHeight		= cpu_to_le16(360),
.dwMinBitRate		= cpu_to_le32(7372800),
.dwMaxBitRate		= cpu_to_le32(55296000),
.dwMaxVideoFrameBufferSize	= cpu_to_le32(460800),
.dwDefaultFrameInterval	= cpu_to_le32(666666),
.bFrameIntervalType	= 3,
.dwFrameInterval[0]	= cpu_to_le32(666666),
.dwFrameInterval[1]	= cpu_to_le32(1000000),
.dwFrameInterval[2]	= cpu_to_le32(5000000),
};
struct uvc_descriptor_header *uvc_fs_streaming_cls[] = { 
(struct uvc_descriptor_header *) &uvc_input_header, 
(struct uvc_descriptor_header *)  &uvc_format_nv12,
(struct uvc_descriptor_header *)  &uvc_frame_yuv_360p,
(struct uvc_descriptor_header *) &uvc_color_matching, 
NULL,
};
struct uvc_descriptor_header *uvc_fs_streaming_cls_ext[] = { 
(struct uvc_descriptor_header *) &uvc_input_header_ext,
(struct uvc_descriptor_header *)  &uvc_format_h264,
(struct uvc_descriptor_header *)  &uvc_frame_h264_1080p,
(struct uvc_descriptor_header *) &uvc_color_matching, 
NULL,
};
struct uvc_descriptor_header *uvc_hs_streaming_cls[] = { 
(struct uvc_descriptor_header *) &uvc_input_header, 
(struct uvc_descriptor_header *)  &uvc_format_nv12,
(struct uvc_descriptor_header *)  &uvc_frame_yuv_360p,
(struct uvc_descriptor_header *) &uvc_color_matching, 
NULL,
};
struct uvc_descriptor_header *uvc_hs_streaming_cls_ext[] = { 
(struct uvc_descriptor_header *) &uvc_input_header_ext,
(struct uvc_descriptor_header *)  &uvc_format_h264,
(struct uvc_descriptor_header *)  &uvc_frame_h264_1080p,
(struct uvc_descriptor_header *) &uvc_color_matching, 
NULL,
};
struct usb_descriptor_header *usbd_uvc_descriptors_FS[] = { 
(struct usb_descriptor_header *) &uvc_iad, 
(struct usb_descriptor_header *) &uvc_control_intf, 
(struct usb_descriptor_header *) &uvc_control_header, 
(struct usb_descriptor_header *) &uvc_camera_terminal, 
(struct usb_descriptor_header *) &uvc_processing, 
(struct usb_descriptor_header *) &uvc_extension_unit, 
(struct usb_descriptor_header *) &uvc_output_terminal, 
(struct usb_descriptor_header *) &uvc_output_ext_terminal, 
(struct usb_descriptor_header *) &uvc_control_ep, 
(struct usb_descriptor_header *) &uvc_control_cs_ep, 
(struct usb_descriptor_header *) &uvc_streaming_intf_alt0, 

(struct usb_descriptor_header *) &uvc_input_header, 
(struct usb_descriptor_header *)  &uvc_format_nv12,
(struct usb_descriptor_header *)  &uvc_frame_yuv_360p, 
(struct usb_descriptor_header *) &uvc_color_matching, 
(struct usb_descriptor_header *) &uvc_hs_streaming_ep,
(struct usb_descriptor_header *) &uvc_streaming_intf_two_alt0,

(struct usb_descriptor_header *) &uvc_input_two_header,
(struct usb_descriptor_header *)  &uvc_format_h264,
(struct usb_descriptor_header *)  &uvc_frame_h264_1080p,
(struct usb_descriptor_header *) &uvc_color_matching, 
(struct usb_descriptor_header *) &uvc_hs_streaming_ep_ext,
NULL,

};
struct usb_descriptor_header *usbd_uvc_descriptors_HS[] = { 
(struct usb_descriptor_header *) &uvc_iad, 
(struct usb_descriptor_header *) &uvc_control_intf, 
(struct usb_descriptor_header *) &uvc_control_header, 
(struct usb_descriptor_header *) &uvc_camera_terminal, 
(struct usb_descriptor_header *) &uvc_processing, 
(struct usb_descriptor_header *) &uvc_extension_unit, 
(struct usb_descriptor_header *) &uvc_output_terminal, 
(struct usb_descriptor_header *) &uvc_output_ext_terminal,
(struct usb_descriptor_header *) &uvc_control_ep, 
(struct usb_descriptor_header *) &uvc_control_cs_ep, 
(struct usb_descriptor_header *) &uvc_streaming_intf_alt0, 

(struct usb_descriptor_header *) &uvc_input_header, 
(struct usb_descriptor_header *)  &uvc_format_nv12,
(struct usb_descriptor_header *)  &uvc_frame_yuv_360p, 
(struct usb_descriptor_header *) &uvc_color_matching, 
(struct usb_descriptor_header *) &uvc_hs_streaming_ep,
(struct usb_descriptor_header *) &uvc_streaming_intf_two_alt0,
(struct usb_descriptor_header *) &uvc_input_two_header,
(struct usb_descriptor_header *)  &uvc_format_h264,
(struct usb_descriptor_header *)  &uvc_frame_h264_1080p,
(struct usb_descriptor_header *) &uvc_color_matching,  
(struct usb_descriptor_header *) &uvc_hs_streaming_ep_ext,
NULL,
};
struct uvc_frame_info uvc_frames_h264[] = {
{ 1920 ,1080, { VALUE_FPS(30), VALUE_FPS(15), VALUE_FPS(10), 0 },},
{ 0, 0, { 0, }, },
};
struct uvc_frame_info uvc_frames_nv12[] = {
{ 640, 360, { VALUE_FPS(15), VALUE_FPS(10), VALUE_FPS(2), 0 }, },
{ 0, 0, { 0, }, },
};
struct uvc_format_info uvc_formats[] = {
{ FORMAT_TYPE_NV12, uvc_frames_nv12 },
};
struct uvc_format_info uvc_formats_ext[] = {
{ FORMAT_TYPE_H264, uvc_frames_h264 },
};
#endif

#endif //LIB_UVCD_DUAL
