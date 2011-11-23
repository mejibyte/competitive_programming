# Intended for use with AMI ami-a7f539ce

sudo apt-get install make sudo php5-cli php5-mysql ntp xsltproc procps sharutils gcc g++ openjdk-6-jre-headless openjdk-6-jdk fp-compiler libcurl4-gnutls-dev libboost-regex-dev

# Download and install
cd ~
wget  "http://downloads.sourceforge.net/project/domjudge/domjudge/3.2.1/domjudge-3.2.1.tar.gz" -O domjudge-3.2.1.tar.gz
tar zxvf domjudge-3.2.1.tar.gz
cd domjudge-3.2.1
./configure --prefix=$HOME/domjudge
sudo make install-judgehost

# Build chroot (for Java)
cd ~/domjudge/judgehost
sudo bin/dj_make_chroot /chroot/domjudge i386

sudo useradd -d /nonexistent -g nogroup -s /bin/false domjudge-run

# Default settings
cd ~/domjudge/judgehost/etc
sudo sed -e "s/define('CHROOT_SCRIPT', '')/\/\/ define('CHROOT_SCRIPT', '')/g" \
         -e "s/\/\/ define('CHROOT_SCRIPT', 'chroot-startstop.sh');/define('CHROOT_SCRIPT', 'chroot-startstop.sh');/g" \
         -e "s/define('FILELIMIT', 4096);/define('FILELIMIT', 40960);/g" \
         -e "s/'presentation-error' => 'wrong-answer',/\/\/ 'presentation-error' => 'wrong-answer',/g" \
         -i.original judgehost-config.php
 
if [ $? -ne 0 ] ; then
    echo "Something went wrong while replacing settings in judgehost-config.php. Reverting to original."
    mv judgehost-config.php.original judgehost-config.php
else
    echo "Replaced settings in judgehost-config.php."
fi