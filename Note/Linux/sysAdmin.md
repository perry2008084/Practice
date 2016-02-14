
* NTP
 * check timezone 'date -R'
 * change timezone 'tzselect'
 * write env variable to /etc/profile 
  * add 'export TZ='Asia/Shang'',and add the TZ to path
 * update PATH 'source /etc/profile'
 * confiure NTP server (pool.ntp.org)
 * sudo dpkg-reconfigure tzdata
