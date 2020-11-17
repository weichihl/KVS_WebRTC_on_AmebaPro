#include "log_service.h"
#include "mmf2_dbg.h"
#include "jpeg_snapshot.h"
#include "FreeRTOS.h"
#include "task.h"
#include "platform_opts.h"
#include "snapshot_tftp_handler.h"
#include "platform_stdlib.h"

extern void set_rtp_drop_threshold(u32 drop_ms);
extern u32 get_rtp_drop_threshold();
extern void set_show_timestamp_diff(u8 action);
extern u32 get_show_timestamp_diff();

void fATMD(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	
	if(!arg){
		AT_PRINTK("[ATMD]: _AT_MEDIA_DEBUG_");
		AT_PRINTK("[ATMD] Usage: ATMD=[s/g],[type,level,1/0]");
		AT_PRINTK("       type: ISP/RTP/RTSP/ENC");
		AT_PRINTK("       level: E/W/I");
		AT_PRINTK("              # E: ERROR");
		AT_PRINTK("              # W: WARNING");
		AT_PRINTK("              # I: INFO");
		return;
	}
	else{
		argc = parse_param(arg, argv);
		printf("[ATMD]: _AT_MEDIA_DEBUG_[");
		for(int i=1; i<(argc); i++) {
			if (i==(argc-1))
				printf("%s]\n\r",argv[argc-1]);
			else
				printf("%s,",argv[i]);
		}
	}
	
	if ((strcmp(argv[1],"g") == 0) || (strcmp(argv[1],"G") == 0)) {
		printf("[ATMD]: _AT_MEDIA_DEBUG_[get MMF debug message status]\n\r");
		printf("ConfigDebugMmfErr=%x\n\r",ConfigDebugMmfErr);
		printf("ConfigDebugMmfWarn=%x\n\r",ConfigDebugMmfWarn);
		printf("ConfigDebugMmfInfo=%x\n\r",ConfigDebugMmfInfo);	
	}
	else if ((strcmp(argv[1],"s") == 0) || (strcmp(argv[1],"S") == 0)) {
		u32 type;
		if(strcmp(argv[2], "RTSP") == 0)
			type = _MMF_DBG_RTSP_;
		else if(strcmp(argv[2], "RTP") == 0)
			type = _MMF_DBG_RTP_;
		else if(strcmp(argv[2], "ISP") == 0)
			type = _MMF_DBG_ISP_;
		else if(strcmp(argv[2], "ENC") == 0)
			type = _MMF_DBG_ENCODER_;
		else {
			printf("Error: unknown type %s\n\r",argv[2]);
			return;
		}
		int action = atoi((const char *)(argv[4]));
		
		if (strcmp(argv[3],"E") == 0) {
			if (action)
				DBG_MMF_ERR_MSG_ON(type);
			else
				DBG_MMF_ERR_MSG_OFF(type);
		}
		else if (strcmp(argv[3],"W") == 0) {
			if (action)
				DBG_MMF_WARN_MSG_ON(type);
			else
				DBG_MMF_WARN_MSG_OFF(type);
		}
		else if (strcmp(argv[3],"I") == 0) {
			if (action)
				DBG_MMF_INFO_MSG_ON(type);
			else
				DBG_MMF_INFO_MSG_OFF(type);
		}
		else {
			printf("Error: unknown level [%s]\n\r",argv[3]);
			return;
		}	
		AT_PRINTK("[ATMD]: _AT_MEDIA_DEBUG_[set MMF debug message status]");
	}
}

unsigned int media_str_to_value(const unsigned char *str){
	if(str[0]=='0'&&(str[1]=='x' || str[1]=='X'))
		return strtol((char const*)str,NULL,16);
	else
		return atoi((char const*)str);
}

void fATME(void *arg)
{
#if 0
	int argc = 0;
	unsigned int width ,height ,streamid, fps, bps = 0;
	char *argv[MAX_ARGC] = {0};
	
	argc = parse_param(arg, argv);//ATME=H264,RES,STREAMID,WIDTH,HEIGHT
	if(argc < 2){
		AT_PRINTK("ATME=H264,RES,STREAMID,WIDTH,HEIGHT\r\n");
		AT_PRINTK("ATME=H264,FPS,STREAMID,VALUE\r\n");
		AT_PRINTK("ATME=H264,BPS,STREAMID,VALUE\r\n");
		AT_PRINTK("ATME=H264,IFRAME,STREAMID\r\n");
	}else{
		if(strcmp(argv[1], "H264") == 0 || strcmp(argv[1], "h264") == 0){
			if(strcmp(argv[2], "RES") == 0 || strcmp(argv[2], "res") == 0){
				streamid = media_str_to_value(argv[3]);
				width = media_str_to_value(argv[4]);
				height = media_str_to_value(argv[5]);
				if(argc != 6){
					AT_PRINTK("The command error reference ATME=H264,RES,STREAMID,WIDTH,HEIGHT\r\n");
				}else{
					AT_PRINTK("streamid = %d width = %d height = %d\r\n",streamid,width,height);
					mmf_video_h264_change_resolution(streamid,width,height);
				}
			}else if(strcmp(argv[2], "FPS") == 0 || strcmp(argv[2], "fps") == 0){
				streamid = media_str_to_value(argv[3]);
				fps = media_str_to_value(argv[4]);
				if(argc != 5){
					AT_PRINTK("The command error reference ATME=H264,FPS,STREAMID,VALUE\r\n");
				}else{
					AT_PRINTK("streamid = %d fps = %d\r\n",streamid,fps);
					mmf_video_h264_change_fps(streamid,fps);
				}
			}else if(strcmp(argv[2], "BPS") == 0 || strcmp(argv[2], "bps") == 0){
				streamid = media_str_to_value(argv[3]);
				bps = media_str_to_value(argv[4]);
				if(argc != 5){
					AT_PRINTK("The command error reference ATME=H264,BPS,STREAMID,VALUE\r\n");
				}else{
					AT_PRINTK("ATME=H264,BPS,STREAMID,VALUE\r\n\n");
					mmf_video_h264_change_bps(streamid,bps);
				}
			}else if(strcmp(argv[2], "IFRAME") == 0 || strcmp(argv[2], "iframe") == 0){
				streamid = media_str_to_value(argv[3]);
				if(argc != 4){
					AT_PRINTK("The command error reference ATME=H264,IFRAME,STREAMID\r\n");
				}else{
					AT_PRINTK("ATME=H264,BPS,STREAMID,VALUE\r\n\n");
					mmf_video_h264_force_iframe(streamid);
				}
			}
		}
		
	}
#endif
}

void fATMR(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	
	if(!arg){
		AT_PRINTK("[ATMR]: _AT_MEDIA_RTSP_");
		AT_PRINTK("[ATMR] Usage: ATMR=[type],[s/g],[options]");
		AT_PRINTK("       type: ");
		AT_PRINTK("             d  # drop old data (ms)");
		AT_PRINTK("             t  # show RTP timestamp diff (1/0)");
		return;
	}
	else{
		argc = parse_param(arg, argv);
		printf("[ATMR]: _AT_MEDIA_RTSP_[");
		for(int i=1; i<(argc); i++) {
			if (i==(argc-1))
				printf("%s]\n\r",argv[argc-1]);
			else
				printf("%s,",argv[i]);
		}
	}
	
	if (strcmp(argv[1],"d") == 0) {
		if (strcmp(argv[2],"s") == 0) {
			u32 drop_ms = atoi((const char *)(argv[3]));
			set_rtp_drop_threshold(drop_ms);
		}
		AT_PRINTK("[ATMR]: _AT_MEDIA_RTSP_[drop old data =%d (ms)]",get_rtp_drop_threshold());
	}
	else if (strcmp(argv[1],"t") == 0) {
		if (strcmp(argv[2],"s") == 0) {
			u8 action = atoi((const char *)(argv[3]));
			set_show_timestamp_diff(action);
		}
		AT_PRINTK("[ATMR]: _AT_MEDIA_RTSP_[show RTP timestamp diff =%d]",get_show_timestamp_diff());
	}
}

#if CONFIG_EXAMPLE_MEDIA_MULTIPLE_RTSP
extern void	jpeg_snapshot_set_tftp_host_ip(u8* addr_string);
extern u8*	jpeg_snapshot_get_tftp_host_ip();
extern void	jpeg_snapshot_set_filename(u8* file_name);
extern u8*	jpeg_snapshot_get_filename();
#endif

void fATMS(void *arg)
{
	int argc = 0;
	char *argv[MAX_ARGC] = {0};
	if(!arg){
		AT_PRINTK("[ATMS]: _AT_MEDIA_SNAPSHOT_");
		AT_PRINTK("[ATMS] Usage: ATMS=[type],[s/g],[options]");
		AT_PRINTK("       type: ");
		AT_PRINTK("             ip     # tftp host ip");
		AT_PRINTK("             f      # snapshot filename");
		AT_PRINTK("             ts     # take snapshot (during streaming)");
		AT_PRINTK("             ti     # take snapshot (from isp)");
		AT_PRINTK("             tis    # setup width and height(from isp)");
		return;
	}
	else{
		argc = parse_param(arg, argv);
		printf("[ATMS]: _AT_MEDIA_SNAPSHOT_[");
		for(int i=1; i<(argc); i++) {
			if (i==(argc-1))
				printf("%s]\n\r",argv[argc-1]);
			else
				printf("%s,",argv[i]);
		}
	}
	if (strcmp(argv[1],"ip") == 0) {
		if (strcmp(argv[2],"s") == 0) {
			jpeg_snapshot_set_tftp_host_ip(argv[3]);
		}
		AT_PRINTK("[ATMS]: _AT_MEDIA_SNAPSHOT_[tftp host ip=%s]",jpeg_snapshot_get_tftp_host_ip());
	}
	else if (strcmp(argv[1],"f") == 0) {
		if (strcmp(argv[2],"s") == 0) {
			jpeg_snapshot_set_filename(argv[3]);
		}
		AT_PRINTK("[ATMS]: _AT_MEDIA_SNAPSHOT_[snapshot filename=%s]",jpeg_snapshot_get_filename());
	}
	else if (strcmp(argv[1],"ts") == 0) {
		AT_PRINTK("[ATMS]: _AT_MEDIA_SNAPSHOT_[take snapshot (during streaming)]");
		jpeg_snapshot_stream();
	}
	else if (strcmp(argv[1],"ti") == 0) {
		AT_PRINTK("[ATMS]: _AT_MEDIA_SNAPSHOT_[take snapshot (from isp)]");
		if ( jpeg_snapshot_isp() < 0)
			printf("take snapshot (from isp) FAIL\n\r");
	}
	else if (strcmp(argv[1],"tis") == 0) {
		int width = atoi(argv[2]);
		int height = atoi(argv[3]);
		printf("set width = %d height = %d(from isp)\r\n",width,height);
		jpeg_snapshot_isp_change_resolution(width,height);
	}
}

void fATMt(void *arg)
{
	AT_PRINTK("[ATM#]: _AT_MEDIA_TEST_");
}

void fATMx(void *arg)
{
	AT_PRINTK("[ATM?]: _AT_MEDIA_INFO_");
	AT_PRINTK("[ATMD]: _AT_MEDIA_DEBUG_");
	AT_PRINTK("[ATME]: _AT_MEDIA_ENCODER_");
	AT_PRINTK("[ATMR]: _AT_MEDIA_RTSP_");
	AT_PRINTK("[ATMS]: _AT_MEDIA_SNAPSHOT_");
	AT_PRINTK("[ATM#]: _AT_MEDIA_TEST_");
}

log_item_t at_media_items[ ] = {
	{"ATMD", fATMD,}, // Debug message
	{"ATME", fATME,}, // Encoder
	{"ATMR", fATMR,}, // RTP/RTSP
	{"ATMS", fATMS,}, // Snapshot
	{"ATM#", fATMt,}, // Test command
	{"ATM?", fATMx,}, // Test command
};

void at_media_init(void)
{
	log_service_add_table(at_media_items, sizeof(at_media_items)/sizeof(at_media_items[0]));
}

#if SUPPORT_LOG_SERVICE
log_module_init(at_media_init);
#endif
