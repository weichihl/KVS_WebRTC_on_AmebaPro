# $1 is project path (PROJ_DIR = GCC-RELEASE) ??
inc_path=$1/../inc
ispfw_path=$1/../../../component/soc/realtek/8195b/misc/bsp/image

sensor_generate(){
	if [ -f $ispfw_path/sensor_config.h ] ; then
	echo "rempve the $FILE_LIST"
    rm $ispfw_path/sensor_config.h 
	fi
	while read LINE; do
	result=$(echo $LINE | grep "#define SENSOR_")
	if [ "$result" != "" ]; then
	sensor=$(echo $LINE | awk '{print $2}' | sed 's/[ /\r\n].*//g')
	sensor_index=$(echo $LINE | awk '{print $3}' | sed 's/[ /\r\n].*//g')
	sensor=$(echo $sensor | tr '[:upper:]' '[:lower:]')
	echo "$sensor,$sensor_index"
	if [ "$sensor" = "SENSOR_ALL" ]; then
	break
	fi;
	echo $sensor_index,$sensor >> $ispfw_path/sensor_config.h
	fi
	done < $inc_path/sensor.h
}

#OS=$(echo $(uname))
#echo $OS

os_version=$(echo $(uname) | grep "CYGWIN")
if [ "$os_version" != "" ]; then
	echo "CYGWIN"
	os_version="CYGWIN"
else
	os_version="LINUX"
	echo "NON-CYGWIN"
fi

if [ -z "$1" ]; then
	echo NEED PROJ_DIR
	exit
else
	#;*****************************************************************************#
	#;                      Auto Select ISP firmware by Sensor                     #
	#;*****************************************************************************#
	sensor=$(grep "define SENSOR_USE" 	"$inc_path/sensor.h" | gawk '{print $3}' | sed 's/SENSOR_//g' | sed 's/[ /\r\n].*//g')
	sensor=$(echo $sensor | tr '[:upper:]' '[:lower:]')
	if [ "$sensor" = "ALL" ]; then
	sensor_generate
	echo "ALL"
	if [ "$os_version" = "CYGWIN" ]; then
	chmod +x "$ispfw_path/ISP_COMBINE_CYGWIN.exe"
	cygstart "$ispfw_path/ISP_COMBINE_CYGWIN.exe" "$ispfw_path/sensor_config.h" "$ispfw_path/"
	fi
	if [ "$os_version" = "LINUX" ]; then
	chmod u+x "$ispfw_path/ISP_COMBINE_LINUX"
	"$ispfw_path/ISP_COMBINE_LINUX" "$ispfw_path/sensor_config.h" "$ispfw_path/"
	fi
	else
	echo "$sensor" is selected
	cp "$ispfw_path/isp_$sensor.bin" "$ispfw_path/isp.bin"
	fi
fi




