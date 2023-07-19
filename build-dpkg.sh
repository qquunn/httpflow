DIR=`pwd`
rm -f httpflow_1.0.0_amd64.deb
rm -rf .tmp \
&& mkdir .tmp \
&& cd .tmp \
&& cp -r ../dpkgdata/DEBIAN . \
&& mkdir -p usr/local/lib \
&& mkdir -p usr/bin \
&& cp -f $DIR/httpflow usr/bin \
&& cp -f /usr/local/lib/libpcap.so.1  usr/local/lib \
&& cp -f /usr/local/lib/librdkafka.so.1 usr/local/lib \
&& cd .. \
&& dpkg -b .tmp httpflow_1.0.0_amd64.deb
